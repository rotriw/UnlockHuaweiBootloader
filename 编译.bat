@echo off
set /p a="small file? [y/n]:"
if "%a%"=="y" (
    set /p a="random? [y/n]:"
    if "%a%"=="y" (
        mingw64\bin\gcc.exe -s -O3 -o main.exe main.c
    ) else if "%a%"=="n" (
        mingw64\bin\gcc.exe -s -O3 -o main.exe norandom.c
    ) else (
        echo input error
    )
) else if "%a%"=="n" (
    set /p a="random? [y/n]:"
    if "%a%"=="y" (
        mingw64\bin\gcc.exe -O3 -o main.exe main.c
    ) else if "%a%"=="n" (
        mingw64\bin\gcc.exe -O3 -o main.exe norandom.c
    ) else (
        echo input error
    )
) else (
    echo input error
)
pause