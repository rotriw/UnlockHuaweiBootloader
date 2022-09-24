#include <windows.h>
#include <stdint.h>
#define DLLImport __declspec(dllimport)
#define DLLExport __declspec(dllexport)
//从code.dll导入的CodeInit,UpdateCode,CodeExit
DLLImport void * WINAPI CodeInit(void *);
DLLImport uint8_t WINAPI UpdateCode(void *);
DLLImport void WINAPI CodeExit(void *);
void main(void){
    struct{
        uint8_t head[22];
        uint16_t code[16];
        uint16_t zero;
    }line={
        //"oem unlock "
        {'o',0,'e',0,'m',0,' ',0,'u',0,'n',0,'l',0,'o',0,'c',0,'k',0,' ',0},
        //16位解锁码
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        //unicode结尾两个NULL
        0
    };
    HANDLE stdo,wrrd;
    DWORD temp;
    void *stat,*fpas,*dpas;
    STARTUPINFOW StartUpInfo;
    PROCESS_INFORMATION ProcessInformation;
    //状态,用于判断已经读完"OKAY"的哪个字符了;缓冲区,由基地址,当前指针,最大地址组成
    uint8_t data=0,*base,*pnow,*pmax;
    //获取stdout句柄
    if((stdo=GetStdHandle(STD_OUTPUT_HANDLE))==INVALID_HANDLE_VALUE){goto exit;}
    //hg56th56gd6g
    WriteFile(stdo,"BuildBy hg56th56gd6g\n",21,&temp,0);
    //获取进程默认堆,获取platform-tools和platform-tools\fastboot.exe完整路径,这是为了加快CreateProcessW处理参数
    if(!(
        (wrrd=GetProcessHeap())&&
        (temp=GetFullPathNameW(L"platform-tools",0,0,0))&&
        (dpas=HeapAlloc(wrrd,0,(SIZE_T)(temp<<1)))&&
        (GetFullPathNameW(L"platform-tools",temp,dpas,0))&&
        (temp=GetFullPathNameW(L"platform-tools\\fastboot.exe",0,0,0))&&
        (fpas=HeapAlloc(wrrd,0,(SIZE_T)(temp<<1)))&&
        (GetFullPathNameW(L"platform-tools\\fastboot.exe",temp,fpas,0))
    )){
        WriteFile(stdo,"GetFullPathErr",14,&temp,0);
        goto exit;
    }
    //解析命令行获取管道缓冲区大小
    base=GetCommandLineA();
    while(*base){
        base++;
    }
    temp=((*(--base))-48);
    temp+=(((*(--base))-48)<<4);
    temp+=(((*(--base))-48)<<8);
    temp+=(((*(--base))-48)<<12);
    temp+=(((*(--base))-48)<<16);
    temp+=(((*(--base))-48)<<20);
    temp+=(((*(--base))-48)<<24);
    temp+=(((*(--base))-48)<<28);
    //分配缓冲区并创建管道用于fastboot.exe的stdo,2个句柄(stdo的io句柄),设置子进程可以继承stdout句柄,且被调用CloseHandle时不关闭对象句柄
    if(!(
        (base=HeapAlloc(wrrd,0,(SIZE_T)temp))&&
        (CreatePipe(&wrrd,&(StartUpInfo.hStdOutput),0,temp))&&
        (SetHandleInformation(StartUpInfo.hStdOutput,HANDLE_FLAG_INHERIT|HANDLE_FLAG_PROTECT_FROM_CLOSE,HANDLE_FLAG_INHERIT|HANDLE_FLAG_PROTECT_FROM_CLOSE))
    )){
        WriteFile(stdo,"PipeHandleErr",13,&temp,0);
        goto exit;
    }
    //填充startupinfo
    StartUpInfo.cb=sizeof(STARTUPINFOW);
    //10个null
    StartUpInfo.lpReserved=0;
    StartUpInfo.lpDesktop=0;
    StartUpInfo.lpTitle=0;
    StartUpInfo.dwX=0;
    StartUpInfo.dwY=0;
    StartUpInfo.dwXSize=0;
    StartUpInfo.dwYSize=0;
    StartUpInfo.dwXCountChars=0;
    StartUpInfo.dwYCountChars=0;
    StartUpInfo.dwFillAttribute=0;
    //dwFlags
    StartUpInfo.dwFlags=STARTF_USESTDHANDLES;
    //3个null
    StartUpInfo.wShowWindow=0;
    StartUpInfo.cbReserved2=0;
    StartUpInfo.lpReserved2=0;
    //stdi
    StartUpInfo.hStdInput=0;
    //stdo
    StartUpInfo.hStdError=StartUpInfo.hStdOutput;
    //调用CodeInit
    if(!(stat=CodeInit(&(line.code)))){
        WriteFile(stdo,"CodeInitErr",11,&temp,0);
        goto exit;
    }
    //循环调用CreateProcessW直到管道里读到"OKAY"
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
                //没数据
                if(!temp){break;}
                //读管道所有数据
                read:
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
                                    WriteFile(stdo,"Unlocked,Now WaitFor fastboot Exit...",37,&temp,0);
                                    //读管道数据直到子进程死亡,这是为了防止子进程因为管道缓冲区满了而阻塞
                                    for(;;){
                                        temp=WaitForSingleObject(ProcessInformation.hProcess,0);
                                        if(temp==WAIT_TIMEOUT){
                                            if(!PeekNamedPipe(wrrd,0,0,0,&temp,0)){goto rder;}
                                            if(temp){
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
    exit:
    ExitProcess(0);
}