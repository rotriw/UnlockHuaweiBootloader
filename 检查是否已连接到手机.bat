@echo off
cd platform-tools
set /p a="already in fastboot? [y/n]:"
if "%a%"=="y" (
    fastboot devices
) else if "%a%"=="n" (
    adb devices
) else (
    echo input error
)
pause