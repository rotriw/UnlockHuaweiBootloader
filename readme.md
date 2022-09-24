# 这是什么

用于解锁华为bootloader,枚举法(实际上是根据code.dll的行为来决定)

## 基础要求

windows xp及以上,小端序,32位

## 额外要求

推荐64位,32位会导致数据溢出

# build.bat

用于构建unlockhwbl.exe和code.dll,输出到output\

提供了tcc,mingw gcc,mingw clang llvm的命令行,需要配置路径

默认构建64位的,构建32位可能报错,需要自己调命令行和代码

# platform-tools

安卓提供的工具包

https://dl.google.com/android/repository/platform-tools-latest-windows.zip

# unlockhwbl.exe;unlockhwbl_upx.exe

## 说明

解锁程序,在程序所在目录打开命令行运行

没有打印信息的时候说明正在解锁,不要关闭,从fastboot获取到解锁成功的信息后才会打印信息,等待这一次的fastboot运行结束后退出程序

## 命令格式

unlockhwbl.exe [[0123456789:;<=>?]*8 (管道缓冲区大小,DWORD,用48-63这16个字符表示的十六进制)]

ps:只要最后8字符是这个16进制表示的DWORD值就行

例如0x0fff1234(268374580)管道缓冲区大小(当然不建议实际用这么大的缓冲区):

unlockhwbl NoneNull0 hg56th56gd6g qweqweqwertyuiop[][][]":<DFS"0???1234

或者:

unlockhwbl.exe 0???1234

为什么:

第一个参数是可执行文件路径,由cmd解析,解锁程序会从右往左找8字符

# code.dll

## 说明

是给unlockhwbl.exe提供更新命令行中解锁码函数的dll

默认code.dll的更新行为是从0000000000000000从左到右加到9999999999999999

可以自定义

## 编写说明

需要提供3个函数

解锁码采用小端序宽字符储存(32字节长,但只有偶数下标有效,奇数下标总是0)

### 1.

```c_cpp
(void *) WINAPI CodeInit(void *);
```

用于初始化一个code对象

输入:指向要更新的16个宽字符长的解锁码

返回值:成功则不为0,否则为0

典型的例子是CodeInit初始化一个储存状态的结构体,在UpdateCode里根据结构体的内容来更新解锁码

发挥想象,可以在里面加入从命令行读取选项等

注意:CodeInit需要进行第一次的解锁码初始化,因为解锁码初始是0x00

### 2.

```c_cpp
(uint8_t) WINAPI UpdateCode(void *);
```

用于更新解锁码

输入:是CodeInit的返回值

返回值:成功则不为0,否则为0

ps:不成功也包括没有可用于更新的解锁码了,例如已经加到9999999999999999

发挥想象,比如可以在失败时将当前状态写入磁盘等

### 3.

```c_cpp
(void) WINAPI CodeExit(void *);
```

在退出(错误或完成等)时调用,可用于销毁储存状态的结构体等(发挥想象)

输入是CodeInit的返回值

只要CodeInit成功并且unlockhwbl.exe进程正常退出(包括报错等,只要没有被强制杀死)就一定会调用CodeExit
