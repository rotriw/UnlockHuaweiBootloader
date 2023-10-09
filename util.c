/*
这里是解锁程序可共用的代码部分,有些指示可能仅适用于clang
除了CodeUpdate函数,其他函数都是仅初始化/退出程序时使用
所以指示它们(不内联,是不经常使用的,应该以最小尺寸为目标编译)
CodeUpdate函数是核心循环中每次都要调用的函数,应该以最高性能为目标编译
*/
#include <windows.h>
#include <stdint.h>
//标准输出句柄,log文件句柄
static HANDLE stdo,idxl;
//一些局部变量的浅拷贝
static uint8_t *__cidx,*__cmax,*__fcmd,*__clen,*__work;

//终止程序的函数,尝试优雅的退出程序
__attribute__((cold))
__attribute__((minsize))
static BOOL WINAPI Stop(DWORD dwCtrlType){
    (*__work)=0;
    return TRUE;
}

//Read/WriteFile的简易同步包装
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
DWORD Read(HANDLE file,void *data,DWORD len){
    //Write/ReadFile在执行错误检查之前将len设置为0,而原始函数的错误返回也是0
    ReadFile(file,data,len,&len,0);
    return len;
}

__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
DWORD Write(HANDLE file,void *data,DWORD len){
    //所以这样只是不能进行null写入了,可以选择判断返回值==0为错误,或忽略
    WriteFile(file,data,len,&len,0);
    return len;
}

//打印字符串
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
void Print(LPSTR str){
    while(*str){
        Write(stdo,str,1);
        str++;
    }
    Write(stdo,"\n",1);
}

//退出程序
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
__attribute__((noreturn))
void Exit(void){
    //执行附加的结束操作
    #ifdef __ExitEx
        __ExitEx;
    #endif
    //把索引表写入log文件
    SetFilePointer(idxl,0,0,0);
    Write(idxl,__cidx,16);
    //清理资源
    CloseHandle(idxl);
    Print("Exit");
    //结束程序
    ExitProcess(0);
}

//程序的异常退出
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
__attribute__((noreturn))
void Error(LPSTR str){
    Print(str);
    Print("Error");
    /*
    //弹出一个错误窗口,调试用
    LPSTR lpMsgBuf;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,0,GetLastError(),0,&lpMsgBuf,0,0);
    MessageBoxA(0,lpMsgBuf,0,0);
    */
    Exit();
}

//将环境变量的值拷贝到缓冲区(包括0),失败则拷贝默认值(不检查长度),返回内容长度(不包括0)
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
DWORD EnvGetA(LPSTR lpKey,LPSTR lpDefault,LPSTR lpBuffer,DWORD dwSize){
    dwSize=GetEnvironmentVariableA(lpKey,lpBuffer,dwSize);
    if(dwSize==0){
        do{
            lpBuffer[dwSize]=lpDefault[dwSize];
        }while(lpDefault[dwSize++]);
    }
    return dwSize-1;
}

//公用的初始化
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
void UtilInit(LPSTR *__cseq,uint8_t *__cord){
    #define cord (__cord)
    #define cseq (__cseq)
    #define fcmd (__fcmd)
    #define cidx (__cidx)
    #define cmax (*__cmax)
    #define clen (*__clen)
    DWORD temp;
    LPSTR code;
    //收到控制台信号时调用Stop函数
    SetConsoleCtrlHandler(Stop,TRUE);
    //初始化标准输出句柄
    stdo=GetStdHandle(STD_OUTPUT_HANDLE);
    //从环境变量获取自定义命令格式
    {
    DWORD lenp=EnvGetA("PRE_STRING","oem unlock ",fcmd,241);
    code=fcmd+lenp;
    DWORD lene=EnvGetA("END_STRING","",code+16,241-lenp);
    clen=lenp+16+lene;
    }
    //从环境变量获取自定义枚举行为
    {
    uint8_t env_cseq[17];
    EnvGetA("CODE_ORDER","abcdefghijklmnop",env_cseq,17);
    Print(env_cseq);
    for(temp=0;temp<16;temp++)
        //储存code每一位的指针
        cseq[temp] = code+(env_cseq[temp]-'a');
    }
    cmax=EnvGetA("CHAR_ORDER","0123456789",cord,256)-1;
    Print(cord);
    //打开储存索引表的文件
    idxl=CreateFileA(
        "code.log",
        FILE_READ_DATA|FILE_WRITE_DATA,
        FILE_SHARE_READ,0,OPEN_ALWAYS,
        FILE_FLAG_WRITE_THROUGH,0
    );
    if(
        //文件是新建的(而不是已存在的),或者打开失败也算
        (GetLastError()!=ERROR_ALREADY_EXISTS)||
        //或者读取失败,读取字节数不对也算
        (Read(idxl,cidx,16)!=16)
    ){
        //将索引表全部归0(从头开始)
        for(temp=0;temp<16;temp++)
            cidx[temp]=0;
    }
    //把索引对应到解锁码
    for(temp=0;temp<16;temp++)
        *(cseq[temp]) = cord[cidx[temp]];
    Print(fcmd);
    #undef cord
    #undef cseq
    #undef fcmd
    #undef cidx
    #undef cmax
    #undef clen
    //设置当前目录到platform-tools,一个是便于加载,另一个它的性能也比较好
    if(SetCurrentDirectoryA("platform-tools\\")==0)
        Error("SetCurrentDirectory");
}

//更新解锁码,这个循环被展开会导致性能大幅下降,必须显示声明#pragma nounroll
#define CodeUpdate()    /*循环结束后不判断进位溢出*/\
    for(cup_temp=0;cup_temp<16;cup_temp++){\
        /*需要进位,这一位归0后继续处理下一位*/\
        if(cidx[cup_temp]==cmax){\
            cidx[cup_temp]=0;\
            *(cseq[cup_temp]) = cord[0];\
        /*不需要进位,这一位++后不再处理下一位*/\
        }else{\
            cidx[cup_temp]++;\
            *(cseq[cup_temp]) = cord[cidx[cup_temp]];\
            break;\
        }\
    }

//使用UtilInit
#define Init() \
/*CODE_ORDER*/\
LPSTR cseq[16];\
/*解锁码索引表,每个索引的最大值,CHAR_ORDER,fastboot命令和长度,temp,运行标识*/\
uint8_t cidx[16],cmax,cord[256],fcmd[257],clen,cup_temp,work=1;\
__cidx=cidx;\
__cmax=&cmax;\
__fcmd=fcmd;\
__clen=&clen;\
__work=&work;\
UtilInit(cseq,cord);