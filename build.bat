@echo off
rmdir build\ /s /q
::https://github.com/mstorsjo/llvm-mingw/releases/tag/20230919
set CLANG_OPTION=-Xlinker /SECTION:.all,ERW -Xlinker /MERGE:.text=.all -Xlinker /MERGE:.rdata=.all -Xlinker /MERGE:.data=.all -Xlinker /STACK:0x40000,0x40000 -Wl,--entry=Main,-O3,-icf=all,-s,--strip-all,--gc-sections,--disable-dynamicbase,--disable-high-entropy-va,--disable-nxcompat,--disable-reloc-section,--disable-runtime-pseudo-reloc,--no-guard-cf,--no-guard-longjmp,--no-insert-timestamp,--no-seh -fno-addrsig -fno-split-stack -fno-stack-clash-protection -fno-stack-protector -mno-stack-arg-probe -nostartfiles -nodefaultlibs -lkernel32 -O3 -flto=full -ffunction-sections -fdata-sections -fno-exceptions -fdwarf-exceptions -fno-asynchronous-unwind-tables -fno-unwind-tables
::-Xlinker /SECTION:.all,ERW -Xlinker /MERGE:.text=.all -Xlinker /MERGE:.rdata=.all -Xlinker /MERGE:.data=.all 
::native
set CLANG_TARGET=-march=native
set BUILD_DIR=build\native
mkdir %BUILD_DIR%
clang unlockhwbl_cmdline.c -o %BUILD_DIR%\unlockhwbl_cmdline.exe %CLANG_TARGET% %CLANG_OPTION%
clang test_speed.c -o %BUILD_DIR%\test_speed.exe %CLANG_TARGET% %CLANG_OPTION%
clang unlockhwbl_protocol.c platform-tools\AdbWinApi.dll -o %BUILD_DIR%\unlockhwbl_protocol.exe %CLANG_TARGET% %CLANG_OPTION%
::x86_64
set CLANG_TARGET=-m64 -target x86_64-windows-gnu
set BUILD_DIR=build\x86_64
mkdir %BUILD_DIR%
clang unlockhwbl_cmdline.c -o %BUILD_DIR%\unlockhwbl_cmdline.exe %CLANG_TARGET% %CLANG_OPTION%
clang test_speed.c -o %BUILD_DIR%\test_speed.exe %CLANG_TARGET% %CLANG_OPTION%
clang unlockhwbl_protocol.c platform-tools\AdbWinApi.dll -o %BUILD_DIR%\unlockhwbl_protocol.exe %CLANG_TARGET% %CLANG_OPTION%
::i686(x86)
set CLANG_TARGET=-m32 -target i686-windows-gnu
set BUILD_DIR=build\i686
mkdir %BUILD_DIR%
clang unlockhwbl_cmdline.c -o %BUILD_DIR%\unlockhwbl_cmdline.exe %CLANG_TARGET% %CLANG_OPTION%
clang test_speed.c -o %BUILD_DIR%\test_speed.exe %CLANG_TARGET% %CLANG_OPTION%
clang unlockhwbl_protocol.c platform-tools\AdbWinApi.dll -o %BUILD_DIR%\unlockhwbl_protocol.exe %CLANG_TARGET% %CLANG_OPTION%
pause