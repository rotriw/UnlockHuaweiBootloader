#include <windows.h>
#include <stdint.h>
#define Digit0 (pCmdLine[0])
#define Digit1 (pCmdLine[1])
#define Digit2 (pCmdLine[2])
#define Digit3 (pCmdLine[3])
#define Digit4 (pCmdLine[4])
#define Digit5 (pCmdLine[5])
#define Digit6 (pCmdLine[6])
#define Digit7 (pCmdLine[7])
#define Digit8 (pCmdLine[8])
#define Digit9 (pCmdLine[9])
#define Digita (pCmdLine[10])
#define Digitb (pCmdLine[11])
#define Digitc (pCmdLine[12])
#define Digitd (pCmdLine[13])
#define Digite (pCmdLine[14])
#define Digitf (pCmdLine[15])
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved){
    return TRUE;
}
__declspec(dllexport) uint8_t* __fastcall CodeInit(uint8_t *pCmdLine){
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
    return pCmdLine;
}
__declspec(dllexport) uint8_t __fastcall UpdateCode(uint8_t *pCmdLine){
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
    return 0;
}
__declspec(dllexport) void __fastcall CodeExit(uint8_t *pCmdLine){
}