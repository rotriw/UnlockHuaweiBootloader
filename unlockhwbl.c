#include "unlockhwbl.h"
PROCESS_INFORMATION ProcessInformation;
HANDLE heap,wrrd;
DWORD temp;
uint8_t data;
//缓冲区,优先被读取,由基地址,当前指针,缓冲区长度,剩余长度组成
uint8_t *buff,*crnt;
DWORD blen=0,nlen=0;
//子进程存活:阻塞直到子进程死亡或管道有数据;子进程死亡但管道有数据:将剩余数据读完;子进程死亡且管道没数据:设置flag为没数据,主函数跳出读取循环去开新的子进程;
uint8_t ReadFromPipe(void){
    //读缓冲区
    if(nlen){
        data=*(crnt++);
        nlen--;
        temp=1;
        return 1;
    }
    //阻塞直到子进程死亡或管道有数据
    for(;;){
        //判断子进程是否结束
        temp=WaitForSingleObject(ProcessInformation.hProcess,0);
        //子进程存活
        if(temp==WAIT_TIMEOUT){
            //获取管道剩余可读取字节数
            if(!PeekNamedPipe(wrrd,0,0,0,&temp,0)){return 0;}
            //有数据
            if(temp){goto read;}
            //没数据
            continue;
        }
        //子进程死亡
        if(temp==WAIT_OBJECT_0){
            //获取管道剩余可读取字节数
            if(!PeekNamedPipe(wrrd,0,0,0,&temp,0)){return 0;}
            //有数据
            if(temp){
                read:
                //分配缓冲区
                if(blen<temp){
                    blen=temp;
                    HeapFree(heap,0,buff);
                    if(!(buff=HeapAlloc(heap,0,blen))){return 0;}
                }
                //读管道所有数据
                if(!ReadFile(wrrd,buff,temp,&nlen,0)){return 0;}
                //读缓冲区
                data=*buff;
                crnt=buff+1;
                nlen--;
            }
            return 1;
        }
        //啥也不是
        return 0;
    }
}
void main(void){
    CmdLine line={
        //"oem unlock "
        {'o',0,'e',0,'m',0,' ',0,'u',0,'n',0,'l',0,'o',0,'c',0,'k',0,' ',0},
        //16位解锁码
        {0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},
        //unicode结尾两个NULL
        0
    };
    //获取stdout句柄
    HANDLE stdo;
    if((stdo=GetStdHandle(STD_OUTPUT_HANDLE))==INVALID_HANDLE_VALUE){ExitProcess(0);}
    //hg56th56gd6g
    WriteFile(stdo,"BuildBy hg56th56gd6g\n",21,&temp,0);
    //获取进程默认heap
    if(!(heap=GetProcessHeap())){
        WriteFile(stdo,"GetProcessHeapErr",17,&temp,0);
        ExitProcess(0);
    }
    //创建管道用于fastboot.exe的stdo,2个句柄(stdo的io句柄)
    if(!(buff=HeapAlloc(heap,0,sizeof(SECURITY_ATTRIBUTES)))){
        WriteFile(stdo,"HeapAllocErr",12,&temp,0);
        ExitProcess(0);
    }
    blen=sizeof(SECURITY_ATTRIBUTES);
    ((SECURITY_ATTRIBUTES *)buff)->nLength=sizeof(SECURITY_ATTRIBUTES);
    ((SECURITY_ATTRIBUTES *)buff)->lpSecurityDescriptor=0;
    ((SECURITY_ATTRIBUTES *)buff)->bInheritHandle=TRUE;
    HANDLE wrwr;
    if(!(CreatePipe(&wrrd,&wrwr,(SECURITY_ATTRIBUTES *)buff,0))){
        WriteFile(stdo,"CreatePipeErr",11,&temp,0);
        ExitProcess(0);
    }
    //设置子进程可以继承stdout句柄,且被调用CloseHandle时不关闭对象句柄
    if(!SetHandleInformation(wrwr,HANDLE_FLAG_INHERIT|HANDLE_FLAG_PROTECT_FROM_CLOSE,HANDLE_FLAG_INHERIT|HANDLE_FLAG_PROTECT_FROM_CLOSE)){
        WriteFile(stdo,"SetHandleInfoErr",14,&temp,0);
        ExitProcess(0);
    }
    //获取platform-tools\fastboot.exe完整路径,这是为了加快CreateProcessW寻找可执行文件
    void *fpas,*dpas;
    if(!(
        (temp=GetFullPathNameW(L"platform-tools\\fastboot.exe",0,fpas,0))&&
        (fpas=HeapAlloc(heap,0,(SIZE_T)(temp<<1)))&&
        (GetFullPathNameW(L"platform-tools\\fastboot.exe",temp,fpas,0))
    )){
        WriteFile(stdo,"Get\"platform-tools\\fastboot.exe\"FullPathErr",43,&temp,0);
        ExitProcess(0);
    }
    //获取platform-tools完整路径作为fastboot.exe运行目录
    if(!(
        (temp=GetFullPathNameW(L"platform-tools",0,dpas,0))&&
        (dpas=HeapAlloc(heap,0,(SIZE_T)(temp<<1)))&&
        (GetFullPathNameW(L"platform-tools",temp,dpas,0))
    )){
        WriteFile(stdo,"Get\"platform-tools\"FullPathErr",30,&temp,0);
        ExitProcess(0);
    }
    //加载code.dll
    HMODULE code;
    if(!(code=LoadLibraryA("code.dll"))){
        WriteFile(stdo,"LoadDllErr",10,&temp,0);
        ExitProcess(0);
    }
    //加载并调用CodeInit
    FARPROC func;
    void *stat;
    if(!(
        (func=GetProcAddress(code,"CodeInit"))&&
        (stat=((CodeInit)func)(&(line.dgt0)))
    )){
        WriteFile(stdo,"CodeInitErr",11,&temp,0);
        ExitProcess(0);
    }
    //加载UpdateCode
    if(!(func=GetProcAddress(code,"UpdateCode"))){
        WriteFile(stdo,"GetUpdateCodeErr",16,&temp,0);
        goto ends;
    }
    //循环调用CreateProcessW直到管道里读到"OKAY"
    STARTUPINFOW StartUpInfo={
        sizeof(STARTUPINFOW),
        //10个null
        0,0,0,0,0,0,0,0,0,0,
        //dwFlags
        STARTF_USESTDHANDLES,
        //3个null
        0,0,0,
        //stdi
        0,
        //stdo
        wrwr,
        //stde
        wrwr,
    };
    for(;;){
        //创建进程
        if(!CreateProcessW(fpas,(LPWSTR)&line,0,0,TRUE,0,0,dpas,&StartUpInfo,&ProcessInformation)){
            WriteFile(stdo,"CreateProcessErr",16,&temp,0);
            goto ends;
        }
        //读管道数据
        for(;;){
            if(!ReadFromPipe()){
                rder:
                WriteFile(stdo,"ReadFromPipeErr",15,&temp,0);
                goto ends;
            }
            if(!temp){break;}
            for(;;){
                if(data=='O'){
                    if(!ReadFromPipe()){goto rder;}
                    if(!temp){break;}
                    if(data=='K'){
                        if(!ReadFromPipe()){goto rder;}
                        if(!temp){break;}
                        if(data=='A'){
                            if(!ReadFromPipe()){goto rder;}
                            if(!temp){break;}
                            if(data=='Y'){
                                //有"OKAY",等待子进程结束然后退出程序
                                WriteFile(stdo,"WaitFor fastboot Exit...",24,&temp,0);
                                WaitForSingleObject(ProcessInformation.hProcess,INFINITE);
                                WriteFile(stdo,"OK",2,&temp,0);
                                goto ends;
                            }
                        }
                    }
                    continue;
                }
                break;
            }
        }
        //关闭子进程的进程,主线程句柄
        CloseHandle(ProcessInformation.hProcess);
        CloseHandle(ProcessInformation.hThread);
        //调用UpdateCode
        if(!((UpdateCode)func)(stat)){
            WriteFile(stdo,"UpdateCodeErr",13,&temp,0);
            goto ends;
        }
    }
    //调用CodeExit
    ends:
    if(func=GetProcAddress(code,"CodeExit")){
        ((CodeExit)func)(stat);
    }
    ExitProcess(0);
}