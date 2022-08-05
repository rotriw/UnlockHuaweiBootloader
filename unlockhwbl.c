#include "other.h"
//从code.dll导入的CodeInit,UpdateCode,CodeExit
DLLImport void * WINAPI CodeInit(void *);
DLLImport uint8_t WINAPI UpdateCode(void *);
DLLImport void WINAPI CodeExit(void *);
void main(void){
    CmdLine line={
        //"oem unlock "
        {'o',0,'e',0,'m',0,' ',0,'u',0,'n',0,'l',0,'o',0,'c',0,'k',0,' ',0},
        //16位解锁码
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        //unicode结尾两个NULL
        0
    };
    //获取stdout句柄
    HANDLE stdo;
    if((stdo=GetStdHandle(STD_OUTPUT_HANDLE))==INVALID_HANDLE_VALUE){ExitProcess(0);}
    //hg56th56gd6g
    DWORD temp;
    WriteFile(stdo,"BuildBy hg56th56gd6g\n",21,&temp,0);
    //获取进程默认heap
    HANDLE heap;
    if(!(heap=GetProcessHeap())){
        WriteFile(stdo,"GetProcessHeapErr",17,&temp,0);
        ExitProcess(0);
    }
    //创建管道用于fastboot.exe的stdo,2个句柄(stdo的io句柄)
    void *stat;
    if(!(stat=HeapAlloc(heap,0,sizeof(SECURITY_ATTRIBUTES)))){
        WriteFile(stdo,"HeapAllocErr",12,&temp,0);
        ExitProcess(0);
    }
    ((SECURITY_ATTRIBUTES *)stat)->nLength=sizeof(SECURITY_ATTRIBUTES);
    ((SECURITY_ATTRIBUTES *)stat)->lpSecurityDescriptor=0;
    ((SECURITY_ATTRIBUTES *)stat)->bInheritHandle=TRUE;
    HANDLE wrrd,wrwr;
    if(!(CreatePipe(&wrrd,&wrwr,(SECURITY_ATTRIBUTES *)stat,0))){
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
    stat=CodeInit(&(line.code));
    //状态,用于判断已经读完"OKAY"的哪个字符了;缓冲区,由基地址,当前指针,最大地址,缓冲区长度组成
    uint8_t data=0,*base=0,*pnow,*pmax;
    DWORD blen=0;
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
    PROCESS_INFORMATION ProcessInformation;
    for(;;){
        //创建进程
        if(!CreateProcessW(fpas,(LPWSTR)&line,0,0,TRUE,0,0,dpas,&StartUpInfo,&ProcessInformation)){
            WriteFile(stdo,"CreateProcessErr",16,&temp,0);
            goto ends;
        }
        //读管道数据,直到子进程死亡并且管道无数据
        for(;;){
            //判断子进程是否结束
            temp=WaitForSingleObject(ProcessInformation.hProcess,0);
            //子进程存活
            if(temp==WAIT_TIMEOUT){
                if(!PeekNamedPipe(wrrd,0,0,0,&temp,0)){goto rder;}
                if(temp){goto read;}
                continue;
            }
            //子进程死亡
            if(temp==WAIT_OBJECT_0){
                //获取管道剩余可读取字节数
                if(!PeekNamedPipe(wrrd,0,0,0,&temp,0)){goto rder;}
                //有数据
                if(temp){
                    read:
                    //分配缓冲区
                    if(blen<temp){
                        blen=temp;
                        //防止内存复制消耗时间
                        HeapFree(heap,0,base);
                        if(!(base=HeapAlloc(heap,0,temp))){goto rder;}
                    }
                    //读管道所有数据
                    if(!ReadFile(wrrd,base,temp,&temp,0)){goto rder;}
                    //更新两个指针
                    pnow=base;
                    pmax=base+temp;
                    //跳转之前的状态
                    if(data=='O'){goto O;}
                    if(data=='K'){goto K;}
                    if(data=='A'){goto A;}
                    //去缓冲区寻找"OKAY"
                    for(;;){
                        if(pnow==pmax){break;}
                        data=*(pnow++);
                        if(data=='O'){
                            O:
                            if(pnow==pmax){break;}
                            data=*(pnow++);
                            if(data=='O'){goto O;}
                            if(data=='K'){
                                K:
                                if(pnow==pmax){break;}
                                data=*(pnow++);
                                if(data=='O'){goto O;}
                                if(data=='A'){
                                    A:
                                    if(pnow==pmax){break;}
                                    data=*(pnow++);
                                    if(data=='O'){goto O;}
                                    if(data=='Y'){
                                        //有"OKAY",等待子进程结束然后退出程序
                                        WriteFile(stdo,"WaitFor fastboot Exit...",24,&temp,0);
                                        //读管道数据,这是为了防止子进程因为管道缓冲区满了而阻塞,直到子进程死亡
                                        for(;;){
                                            temp=WaitForSingleObject(ProcessInformation.hProcess,0);
                                            if(temp==WAIT_TIMEOUT){
                                                if(!PeekNamedPipe(wrrd,0,0,0,&temp,0)){goto rder;}
                                                if(temp){
                                                    if(blen<temp){
                                                        blen=temp;
                                                        HeapFree(heap,0,base);
                                                        if(!(base=HeapAlloc(heap,0,blen))){goto rder;}
                                                    }
                                                    if(!ReadFile(wrrd,base,temp,&temp,0)){goto rder;}
                                                }
                                                continue;
                                            }
                                            if(temp==WAIT_OBJECT_0){
                                                WriteFile(stdo,"OK",2,&temp,0);
                                                goto ends;
                                            }
                                            goto rder;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    //缓冲区没有剩余字节
                    continue;
                }
                //没数据
                break;
            }
            //啥也不是
            rder:
            WriteFile(stdo,"ReadFromPipeErr",15,&temp,0);
            goto ends;
        }
        //关闭子进程的进程,主线程句柄
        CloseHandle(ProcessInformation.hProcess);
        CloseHandle(ProcessInformation.hThread);
        //调用UpdateCode
        if(!UpdateCode(stat)){
            WriteFile(stdo,"UpdateCodeErr",13,&temp,0);
            goto ends;
        }
    }
    //调用CodeExit
    ends:
    CodeExit(stat);
    ExitProcess(0);
}