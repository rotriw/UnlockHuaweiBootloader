#include <windows.h>
#include <stdio.h>
int main(void){
    HANDLE w,r;
    w=GetStdHandle(STD_OUTPUT_HANDLE);
    r=GetStdHandle(STD_INPUT_HANDLE);
    DWORD temp;
    char data[64];
    ReadFile(r,data,4,&temp,0);
    printf("%lu\n",temp);
    WriteFile(w,data,4,&temp,0);
    return 0;
}