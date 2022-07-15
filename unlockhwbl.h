//windows.h
#include <windows.h>
//stdint.h
#include <stdint.h>
//从code.dll导入的CodeInit,UpdateCode
typedef void *(WINAPI*CodeInit)(void *);
typedef uint8_t(WINAPI*UpdateCode)(void *);
typedef void(WINAPI*CodeExit)(void *);
//命令行
typedef struct{
    uint8_t head[22];
    uint8_t dgt0[2];
    uint8_t dgt1[2];
    uint8_t dgt2[2];
    uint8_t dgt3[2];
    uint8_t dgt4[2];
    uint8_t dgt5[2];
    uint8_t dgt6[2];
    uint8_t dgt7[2];
    uint8_t dgt8[2];
    uint8_t dgt9[2];
    uint8_t dgta[2];
    uint8_t dgtb[2];
    uint8_t dgtc[2];
    uint8_t dgtd[2];
    uint8_t dgte[2];
    uint8_t dgtf[2];
    uint16_t zero;
}CmdLine;