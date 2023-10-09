#include "util.c"
DWORD PrintNumber(int64_t i,char *data){
    DWORD a=i;
    char temp;
    uint8_t b=0;
    while(a){
        data[b]=(a%10)+'0';
        a/=10;
        b++;
    }
    uint8_t c=b;
    data[b]=0;
    for(a=0,b--;a<b;a++,b--){
        temp=data[a];
        data[a]=data[b];
        data[b]=temp;
    }
    return c;
}
void Main(void){
    DWORD temp,a,b=0,c=0;
    Init();
    COORD p0={0,3},p1={0,4};
    int64_t t0,t1;
    char data[64];
    while(work){
        c++;
        QueryPerformanceCounter((PLARGE_INTEGER)&t0);
        //每10w次计时一次
        for(a=0;a<100000;a++)
            #pragma nounroll
            CodeUpdate();
        QueryPerformanceCounter((PLARGE_INTEGER)&t1);
        //打印当前的解锁码
        WriteConsoleOutputCharacter(stdo,fcmd,clen,p0,&a);
        //将刚才的计时累加
        b+=t1-t0;
        //再除以计时次数
        a=PrintNumber(b/c,data);
        //打印计算出的10w次平均耗时
        WriteConsoleOutputCharacter(stdo,data,a,p1,&a);
        //Sleep(1000);
    }
    Sleep(2000);
    Exit();
}