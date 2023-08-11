#include <windows.h>
#include <stdint.h>
#include "utils.h"
void UnlockHwBl(void){
    DWORD clen=UtilsInit();
    //读管道的句柄
    HANDLE wrrd;
    DWORD temp;
    //状态,用于判断已经读完"OKAY"的哪个字符了;缓冲区,由基地址,当前地址,最大地址组成
    uint8_t data=0,*base,*pnow,*pmax;

    //从环境变量读取设置
    DWORD PIPE_SIZE=ParseDecimalEnvToDwordA("PIPE_SIZE",65536);
    DWORD FASTBOOT_TIMEOUT=ParseDecimalEnvToDwordA("FASTBOOT_TIMEOUT",10000);
    STARTUPINFOA si={0};
    PROCESS_INFORMATION pi;

    //分配缓冲区
    base=AllocMemory(PIPE_SIZE);
    //创建管道用于fastboot.exe的stdout/stderr,2个句柄,一读一写
    if(CreatePipe(&wrrd,&si.hStdOutput,0,PIPE_SIZE)==0)
        Error("CreatePipe");
    //设置管道句柄可继承,且CloseHandle不关闭
    if(SetHandleInformation(
        si.hStdOutput,
        HANDLE_FLAG_INHERIT|HANDLE_FLAG_PROTECT_FROM_CLOSE,
        HANDLE_FLAG_INHERIT|HANDLE_FLAG_PROTECT_FROM_CLOSE
    )==0)Error("SetHandleInfo");

    //填充startupinfo(stdin是0,代表继承此进程的,INVALID_HANDLE_VALUE代表错误的句柄)
    si.cb=sizeof(STARTUPINFOA);
    si.dwFlags=STARTF_USESTDHANDLES;
    si.hStdError=si.hStdOutput;
    //设置当前路径
    if(SetCurrentDirectoryA("platform-tools\\")==0)
        Error("Chdir");

    //循环调用CreateProcess直到管道里读到"OKAY"
    for(;;){
        //创建进程
        if(CreateProcessA(
            "fastboot.exe",fcmd,
            0,0,TRUE,0,0,0,
            &si,&pi
        )==0)Error("CreateProcess");
        //如果超时了,就算失败
        temp=WaitForSingleObject(pi.hProcess,FASTBOOT_TIMEOUT);
        if(temp==WAIT_TIMEOUT)
            Error("fastboot.exe");
        //报错
        if(temp!=WAIT_OBJECT_0)
            Error("Wait");

        //fastboot运行结束,读取管道所有内容
        if(ReadFile(wrrd,base,PIPE_SIZE,&temp,0)==0)
            Error("ReadFile");
        //初始化两个指针
        pnow=base;
        pmax=base+temp;

        //去缓冲区寻找"OKAY"
        for(;;){
            if(pnow==pmax)break;
            data=*(pnow++);
            if(data!='O')continue;
            O:  //如果匹配失败了,只能从substr的第一个重新匹配
            if(pnow==pmax)break;
            data=*(pnow++);
            if(data=='O')goto O;
            if(data!='K')continue;
            if(pnow==pmax)break;
            data=*(pnow++);
            if(data=='O')goto O;
            if(data!='A')continue;
            if(pnow==pmax)break;
            data=*(pnow++);
            if(data=='O')goto O;
            if(data!='Y')continue;
            //有"OKAY"
            Print((LPSTR)&code);
            Ends();
        }

        //关闭子进程的进程,主线程句柄
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        //调用UpdateCode
        if(UpdateCode(stat)==0)
            Error("UpdateCode");
    }
}