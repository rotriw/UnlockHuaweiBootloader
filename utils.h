#include <windows.h>
#include <stdint.h>
//从code.dll导入的CodeInit,UpdateCode,CodeExit
__declspec(dllimport) void* __fastcall CodeInit(void *);
__declspec(dllimport) uint8_t __fastcall UpdateCode(void *);
__declspec(dllimport) void __fastcall CodeExit(void *);
LPSTR fcmd,code;
HANDLE stdout,stat;

//获取字符串长度
DWORD GetStringLengthA(LPSTR str){
    DWORD len=0;
    while(str[len])
        len++;
    return len;
}

//将字符串复制到缓冲区,不包括空字节
void CopyStringA(
    LPSTR str,
    LPSTR buf
){
    DWORD len=GetStringLengthA(str);
    while(len){
        len--;
        buf[len]=str[len];
    }
}

//打印字符串
void Print(LPSTR str){
    DWORD len=0;
    while(str[len])
        len++;
    WriteFile(stdout,str,len,0,0);
}

//(CodeExit)和挂起线程等待退出
void Exit(void){
    SuspendThread(GetCurrentThread());
    //这里不需要ExitProcess,因为当所有的线程自然死亡时进程也会退出
}
void Ends(void){
    CodeExit(stat);
    Print("\nExit");
    Exit();
}

//打印字符串Error并Ends
void Error(LPSTR str){
    Print(str);
    Print("Err");
    /*
    LPSTR lpMsgBuf;
    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,0,GetLastError(),0,(LPSTR)&lpMsgBuf,0,0);
    MessageBox(0,lpMsgBuf,0,0);
    LocalFree(lpMsgBuf);
    */
    Ends();
}

//分配一块初始化为0的内存
void *AllocMemory(DWORD len){
    void *result=LocalAlloc(LPTR,(SIZE_T)len);
    if(result==0)
        Error("LocalAlloc");
    return result;
}

//释放分配的内存
void FreeMemory(void *buf){
    LocalFree(buf);
}

//获取环境变量指定键的值,返回以0结尾的字符串,使用FreeMemory释放它,没有键返回默认值
LPSTR EnvGetA(
    LPSTR lpKey,
    LPSTR lpDefault
){
    DWORD length=GetEnvironmentVariableA(lpKey,0,0);
    if(length==0)
        return lpDefault;
    LPSTR result=AllocMemory(length);
    if(GetEnvironmentVariableA(lpKey,result,length)==0){
        FreeMemory(result);
        Error("GetEnv");
    }
    return result;
}

//将环境变量的指定键作为十进制数解析成DWORD,当遇到[0-9]之外的所有字符时会结束解析,没有键返回默认值
DWORD ParseDecimalEnvToDwordA(
    LPSTR lpKey,   //环境变量的键
    DWORD nDefault  //默认值
){
    LPSTR data=EnvGetA(lpKey,0);
    if(data==0)
        return nDefault;
    DWORD result=0;
    while('0'<=(*data) && (*data)<='9')
        result=result*10 + ((*data)++)-'0';
    return result;
}

//初始化stdout和code对象,以及组装命令格式,返回命令的长度(不包括空字节)
DWORD UtilsInit(void){
    #define DEFAULT_PRE "oem unlock "
    #define DEFAULT_END ""
    stdout=GetStdHandle(STD_OUTPUT_HANDLE);
    if(stdout==INVALID_HANDLE_VALUE)
        Exit();
    Print("unlockhwbl By hg56th56gd6g\n");
    LPSTR pres=EnvGetA("PRE_STRING",DEFAULT_PRE);
    LPSTR ends=EnvGetA("END_STRING",DEFAULT_END);
    DWORD lenp=GetStringLengthA(pres);
    DWORD lene=GetStringLengthA(ends);
    DWORD len=lenp+16+lene+1;
    fcmd=AllocMemory(len);
    code=fcmd+lenp;
    CopyStringA(pres,fcmd);
    CopyStringA(ends,code+16);
    //需要编译器开启字符串池优化
    if(pres!=DEFAULT_PRE)
        FreeMemory(pres);
    if(ends!=DEFAULT_END)
        FreeMemory(ends);
    #undef DEFAULT_PRE
    #undef DEFAULT_END
    stat=CodeInit(code);
    if(stat==0)
        Error("CodeInit");
    return len;
}