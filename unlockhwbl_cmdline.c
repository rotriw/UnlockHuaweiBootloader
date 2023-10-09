#include "util.c"
#define PIPE_SIZE (65536)
#define TIMEOUT (10000)
void Main(void){
    Init();
    //读管道的句柄
    HANDLE wrrd;
    //状态,用于判断已经读完"OKAY"的哪个字符了;缓冲区,由基地址,当前地址,最大地址组成
    uint8_t data,base[PIPE_SIZE],*pnow,*pmax;
    //CreateProcess用
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    DWORD temp;

    //创建管道用于fastboot的输出,2个句柄,一读(自己留着)一写(继承给fastboot的输出)
    if(CreatePipe(&wrrd,&si.hStdOutput,0,PIPE_SIZE)==0)
        Error("CreatePipe");
    //设置管道写端的句柄可以继承
    if(SetHandleInformation(si.hStdOutput,HANDLE_FLAG_INHERIT,HANDLE_FLAG_INHERIT)==0)
        Error("SetHandleInformation");
    //填充startupinfo(stdin的问题不是致命错误)
    si.cb=sizeof(si);
    si.dwFlags=STARTF_USESTDHANDLES;
    si.hStdError=si.hStdOutput;
    si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);

    //核心循环
    while(work){
        //创建进程
        if(CreateProcessA(
            "fastboot.exe",fcmd,
            0,0,TRUE,0,0,0,
            &si,&pi
        )==0)Error("CreateProcess");
        //这里先做一些不用等fastboot运行结束也可以做的事情
        CloseHandle(pi.hThread);//关闭子进程的主线程句柄
        pnow=base;              //重置缓冲区的当前地址

        //等待fastboot运行结束(10s超时和失败都算错误)
        if(WaitForSingleObject(pi.hProcess,TIMEOUT)!=WAIT_OBJECT_0)
            Error("Wait");
        //fastboot运行结束,关闭子进程的进程句柄
        CloseHandle(pi.hProcess);
        //读取管道所有内容
        temp=Read(wrrd,base,PIPE_SIZE);
        if(temp==0)
            Error("ReadPipe");
        //设置缓冲区的最大地址
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
            //找到了"OKAY",打印刚才发送的命令
            Print(fcmd);
            goto ends;
        }
        //没找到"OKAY",更新解锁码
        #pragma nounroll
        CodeUpdate();
    }
    //退出程序
    ends:
    Exit();
}