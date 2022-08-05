#include <windows.h>
#include <stdint.h>
#define DLLImport __declspec(dllimport)
#define DLLExport __declspec(dllexport)
typedef struct{
    uint8_t head[22];
    uint16_t code[16];
    uint16_t zero;
}CmdLine;