@echo off
rmdir build\ /s /q
rmdir temp\ /s /q
mkdir build\x86_64
mkdir build\x86
mkdir temp
::mingw clang llvm
set CLANG_OPTION=-Os -nostartfiles -flto -ffunction-sections -fdata-sections -Wl,--gc-sections,--strip-all,-O3
::x86_64
set CLANG_TARGET=-m64 -arch x86_64
set BUILD_DIR=build\x86_64
"%MINGW_PATH%\clang" code.c -o %BUILD_DIR%\code.dll %CLANG_TARGET% %CLANG_OPTION% -shared -e DllMain -Wl,--out-implib,"temp\code.lib"
"%MINGW_PATH%\clang" unlockhwbl_cmdline.c -o %BUILD_DIR%\unlockhwbl_cmdline.exe %CLANG_TARGET% %CLANG_OPTION% -e UnlockHwBl -L"temp" -l"code"
"%MINGW_PATH%\clang" unlockhwbl_protocol.c -o %BUILD_DIR%\unlockhwbl_protocol.exe %CLANG_TARGET% %CLANG_OPTION% -e UnlockHwBl -L"temp" -l"code"
::x86
set CLANG_TARGET=-m32 -arch x86
set BUILD_DIR=build\x86
"%MINGW_PATH%\clang" code.c -o %BUILD_DIR%\code.dll %CLANG_TARGET% %CLANG_OPTION% -shared -e DllMain -Wl,--out-implib,"temp\code.lib"
"%MINGW_PATH%\clang" unlockhwbl_cmdline.c -o %BUILD_DIR%\unlockhwbl_cmdline.exe %CLANG_TARGET% %CLANG_OPTION% -e UnlockHwBl -L"temp" -l"code"
"%MINGW_PATH%\clang" unlockhwbl_protocol.c -o %BUILD_DIR%\unlockhwbl_protocol.exe %CLANG_TARGET% %CLANG_OPTION% -e UnlockHwBl -L"temp" -l"code"
pause