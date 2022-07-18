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
    uint16_t dgt0;
    uint16_t dgt1;
    uint16_t dgt2;
    uint16_t dgt3;
    uint16_t dgt4;
    uint16_t dgt5;
    uint16_t dgt6;
    uint16_t dgt7;
    uint16_t dgt8;
    uint16_t dgt9;
    uint16_t dgta;
    uint16_t dgtb;
    uint16_t dgtc;
    uint16_t dgtd;
    uint16_t dgte;
    uint16_t dgtf;
    uint16_t zero;
}CmdLine;