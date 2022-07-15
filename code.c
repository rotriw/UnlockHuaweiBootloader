//windows.h
#include <windows.h>
//stdint.h
#include <stdint.h>
//宏
#define PDigit0 (PCodeInfo->dgt0)
#define PDigit1 (PCodeInfo->dgt1)
#define PDigit2 (PCodeInfo->dgt2)
#define PDigit3 (PCodeInfo->dgt3)
#define PDigit4 (PCodeInfo->dgt4)
#define PDigit5 (PCodeInfo->dgt5)
#define PDigit6 (PCodeInfo->dgt6)
#define PDigit7 (PCodeInfo->dgt7)
#define PDigit8 (PCodeInfo->dgt8)
#define PDigit9 (PCodeInfo->dgt9)
#define PDigita (PCodeInfo->dgta)
#define PDigitb (PCodeInfo->dgtb)
#define PDigitc (PCodeInfo->dgtc)
#define PDigitd (PCodeInfo->dgtd)
#define PDigite (PCodeInfo->dgte)
#define PDigitf (PCodeInfo->dgtf)
#define Digit0 (*PDigit0)
#define Digit1 (*PDigit1)
#define Digit2 (*PDigit2)
#define Digit3 (*PDigit3)
#define Digit4 (*PDigit4)
#define Digit5 (*PDigit5)
#define Digit6 (*PDigit6)
#define Digit7 (*PDigit7)
#define Digit8 (*PDigit8)
#define Digit9 (*PDigit9)
#define Digita (*PDigita)
#define Digitb (*PDigitb)
#define Digitc (*PDigitc)
#define Digitd (*PDigitd)
#define Digite (*PDigite)
#define Digitf (*PDigitf)
//code对象
typedef struct{
    //stdout句柄
    HANDLE stdo;
    //堆句柄
    HANDLE heap;
    //解锁码指针
    uint8_t *dgt0;
    uint8_t *dgt1;
    uint8_t *dgt2;
    uint8_t *dgt3;
    uint8_t *dgt4;
    uint8_t *dgt5;
    uint8_t *dgt6;
    uint8_t *dgt7;
    uint8_t *dgt8;
    uint8_t *dgt9;
    uint8_t *dgta;
    uint8_t *dgtb;
    uint8_t *dgtc;
    uint8_t *dgtd;
    uint8_t *dgte;
    uint8_t *dgtf;
}CodeInfo;
__declspec(dllexport) CodeInfo * WINAPI CodeInit(uint8_t *PCmdLine){
    //获取stdout句柄
    HANDLE stdo;
    if((stdo=GetStdHandle(STD_OUTPUT_HANDLE))==INVALID_HANDLE_VALUE){return 0;}
    //获取进程默认堆
    HANDLE heap;
    if(!(heap=GetProcessHeap())){
        WriteFile(stdo,"GetProcessHeapErr\n",18,(LPDWORD)&heap,0);
        return 0;
    }
    //给CodeInfo分配内存
    CodeInfo *PCodeInfo;
    if(!(PCodeInfo=HeapAlloc(heap,0,sizeof(CodeInfo)))){
        WriteFile(stdo,"HeapAllocErr\n",13,(LPDWORD)&heap,0);
        return 0;
    }
    //设置CodeInfo
    PCodeInfo->stdo=stdo;
    PCodeInfo->heap=heap;
    PDigit0=&(PCmdLine[0]);
    PDigit1=&(PCmdLine[2]);
    PDigit2=&(PCmdLine[4]);
    PDigit3=&(PCmdLine[6]);
    PDigit4=&(PCmdLine[8]);
    PDigit5=&(PCmdLine[10]);
    PDigit6=&(PCmdLine[12]);
    PDigit7=&(PCmdLine[14]);
    PDigit8=&(PCmdLine[16]);
    PDigit9=&(PCmdLine[18]);
    PDigita=&(PCmdLine[20]);
    PDigitb=&(PCmdLine[22]);
    PDigitc=&(PCmdLine[24]);
    PDigitd=&(PCmdLine[26]);
    PDigite=&(PCmdLine[28]);
    PDigitf=&(PCmdLine[30]);
    //初始化全'0'
    Digit0='0';
    Digit1='0';
    Digit2='0';
    Digit3='0';
    Digit4='0';
    Digit5='0';
    Digit6='0';
    Digit7='0';
    Digit8='0';
    Digit9='0';
    Digita='0';
    Digitb='0';
    Digitc='0';
    Digitd='0';
    Digite='0';
    Digitf='0';
    return PCodeInfo;
}
__declspec(dllexport) uint8_t WINAPI UpdateCode(CodeInfo *PCodeInfo){
    if(Digit0!='9'){
        Digit0++;
        return 1;
    }
    Digit0='0';
    if(Digit1!='9'){
        Digit1++;
        return 1;
    }
    Digit1='0';
    if(Digit2!='9'){
        Digit2++;
        return 1;
    }
    Digit2='0';
    if(Digit3!='9'){
        Digit3++;
        return 1;
    }
    Digit3='0';
    if(Digit4!='9'){
        Digit4++;
        return 1;
    }
    Digit4='0';
    if(Digit5!='9'){
        Digit5++;
        return 1;
    }
    Digit5='0';
    if(Digit6!='9'){
        Digit6++;
        return 1;
    }
    Digit6='0';
    if(Digit7!='9'){
        Digit7++;
        return 1;
    }
    Digit7='0';
    if(Digit8!='9'){
        Digit8++;
        return 1;
    }
    Digit8='0';
    if(Digit9!='9'){
        Digit9++;
        return 1;
    }
    Digit9='0';
    if(Digita!='9'){
        Digita++;
        return 1;
    }
    Digita='0';
    if(Digitb!='9'){
        Digitb++;
        return 1;
    }
    Digitb='0';
    if(Digitc!='9'){
        Digitc++;
        return 1;
    }
    Digitc='0';
    if(Digitd!='9'){
        Digitd++;
        return 1;
    }
    Digitd='0';
    if(Digite!='9'){
        Digite++;
        return 1;
    }
    Digite='0';
    if(Digitf!='9'){
        Digitf++;
        return 1;
    }
    WriteFile(PCodeInfo->stdo,"EndOfCode\n",10,(LPDWORD)&PCodeInfo,0);
    return 0;
}
__declspec(dllexport) void WINAPI CodeExit(CodeInfo *PCodeInfo){
    HeapFree(PCodeInfo->heap,0,PCodeInfo);
}