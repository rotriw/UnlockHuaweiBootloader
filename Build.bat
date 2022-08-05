@echo off
set temp_path=output\temp
set tcc_output=output\tcc
set clang_output=output\clang
set gcc_output=output\gcc
mkdir "%temp_path%"
mkdir "%tcc_output%"
mkdir "%clang_output%"
mkdir "%gcc_output%"
::-nostdlib -Wl,-stack=<stack_size>
::tcc
set tcc_option=-l"kernel32" -O3 -x c -m64
tcc "code.c" -o "%temp_path%\code.dll" %tcc_option% -shared
tcc "unlockhwbl.c" -o "%temp_path%\unlockhwbl.exe" %tcc_option% -L"%temp_path%" -l"code" -Wl,--subsystem=console
strip -o "%tcc_output%\code.dll" -s -R .pdata "%temp_path%\code.dll"
strip -o "%tcc_output%\unlockhwbl.exe" -s -R .pdata "%temp_path%\unlockhwbl.exe"
::mingw clang llvm
set clang_option=-l"kernel32" -O3 -x c -m64 -ffunction-sections -fdata-sections -Wl,--gc-sections,--strip-all,-O3,--icf=all
"%clang_path%\clang" "code.c" -o "%clang_output%\code.dll" %clang_option% -shared -Wl,--out-implib,"%temp_path%\code.lib",--output-def,"%temp_path%\code.def"
"%clang_path%\clang" "unlockhwbl.c" -o "%clang_output%\unlockhwbl.exe" %clang_option% -Wl,--subsystem=console -L"%temp_path%" -l"code"
::mingw gcc
set gcc_option=-l"kernel32" -O3 -x c -m64 -fwhole-program -flto -ffunction-sections -fdata-sections -Wl,--gc-sections,--strip-all,--discard-all,-O3
gcc "code.c" -o "%gcc_output%\code.dll" %gcc_option% -shared -Wl,--out-implib,"%temp_path%\code.lib",--output-def,"%temp_path%\code.def"
gcc "unlockhwbl.c" -o "%gcc_output%\unlockhwbl.exe" %gcc_option% -Wl,--subsystem=console -L"%temp_path%" -l"code"
pause