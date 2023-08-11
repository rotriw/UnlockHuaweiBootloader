# 重要

新版本尚未完成

# 这是什么

用于解锁华为bootloader,它需要向fastboot输入`oem unlock <16位解锁码>`这条命令,你也可以自定义命令格式

此工具帮助你高效的用枚举法(实际上是根据code.dll的行为来决定)来不断的尝试16位解锁码

在之前的版本(称为老版本),它使用CreateProcess来运行命令行解锁,这引入了非常大的开销,但是它作为纯c写的,依然比py/sh脚本性能高(现在重命名为unlockhwbl_cmdline)

(称为新版本)现在则直接使用fastboot协议通信,避免一些创建/销毁进程,连接/断开的开销(现在叫unlockhwbl_protocol)

(选择设备部分完全照抄fastboot源码,可以参考adb和fastboot的-s和devices参数,还有ANDROID_SERIAL环境变量)

参考:

https://github.com/google/python-adb

https://github.com/aosp-mirror/platform_system_core

ps:我没有可供测试的设备,有问题欢迎反馈

# 运行要求

windows xp及以上

但是推荐win10 x64

# platform-tools

安卓提供的工具包

https://dl.google.com/android/repository/platform-tools-latest-windows.zip

# build.bat

用于构建unlockhwbl.exe和code.dll,输出到build\

提供了mingw clang llvm的命令,需要配置路径

同时构建适用于多个平台的可执行文件

脚本很短,只是为我自己写的! :)

# unlockhwbl.exe

解锁程序,双击运行即可,程序结尾会把线程挂起,你可以直接退出或把程序恢复运行


没有打印信息的时候说明正在解锁,不要关闭,有几种情况会打印信息:

1. 错误

2. 解锁成功,打印正确的解锁码(已经解锁,不需要再次输入命令)

会打印一段开头告诉你程序是活的

但是如果没打印开头就没动静了,这应该是出错了

(当打印正确的解锁码之后再出现错误,说明依然解锁成功了,只是后续的释放资源步骤出错了)

## 命令行格式

现在已经不需要命令行参数,直接运行即可,现在使用环境变量作为参数传递

如果没有设置某个环境变量,则此参数使用默认值

### 新老版本都有的变量

是为了自定义命令而来,我们将命令视为四个部分:

`<前置字符串><16位解锁码><后置字符串>\x00`

其中16位解锁码由code.dll修改,结尾的空字节由程序填充

整条命令中有且只有结尾的一个空字节,正好符合windows环境变量的特点(以空字节结尾)

用户想要自定义命令只需要修改前置字节和后置字节即可

1. "PRE_STRING"

前置字符串,默认"oem unlock "

2. "END_STRING"

后置字符串,默认""

是的,就是空字符串!因为默认的命令是`oem unlock <16位解锁码>`

### 老版本的变量

(由于老版本的读管道部分为了减小开销不再使用忙轮询(不断的读管道,观察fastboot是否运行完毕),所以引入了这两个参数)

1. "PIPE_SIZE"

fastboot的输出管道大小(字节),fastboot应最多向自己的stderr和stdout写入这么多字节(参考CreatePipe的nSize参数和Read/WriteFile阻塞机制)

DWORD,以十进制字符串形式表示,默认"65536"

(推荐设置为内存页大小(通常为4096)的倍数)

2. "FASTBOOT_TIMEOUT"

每个fastboot进程最多运行多久(毫秒),如果超时了则视为错误

DWORD,以十进制字符串形式表示,默认"10000"

(当你的PIPE_SIZE不足以容纳fastboot输出时,fastboot进程会被阻塞,直到timeout错误)

### 新版本的变量

1. "ANDROID_SERIAL"

fastboot设备字符串,选择设备部分完全照抄fastboot源码,可以参考adb和fastboot的-s和devices参数,还有ANDROID_SERIAL环境变量

默认没有(match_fastboot:1,使用最后连接的usb设备;2,使用最后连接的网络设备;3,回到1直到有设备连接)

注:支持usb,tcp,udp设备

2. "RESPONSE_SIZE"

一次最多接收多少数据(字节),fastboot(好像)没有明确说明设备返回的包最大是多少,有64字节的也有256字节的

DWORD,以十进制字符串形式表示,默认"256"

(建议至少64字节)

# code.dll

是给unlockhwbl.exe提供更新命令行中解锁码函数的dll

默认code.dll的更新行为是从0000000000000000从左到右加到9999999999999999

可以自定义

## 编写说明

需要提供3个函数

解锁码用16字节储存
示例:{'9','8','7','6','5','4','3','2','1','0','9','8','7','6','5','4'}

### 1.

```c_cpp
(void *) __fastcall CodeInit(void *);
```

用于初始化一个code对象

输入:指向解锁码的指针

返回值:成功则不为0,否则为0

典型的例子是CodeInit初始化一个储存状态的结构体,然后返回这个结构体指针,在UpdateCode里根据结构体的内容来更新解锁码

发挥想象,可以在里面加入从命令行读取选项等

注意:CodeInit需要进行第一次的解锁码初始化,因为解锁码的每一位初始是随机值而不是'0'

### 2.

```c_cpp
(uint8_t) __fastcall UpdateCode(void *);
```

用于更新解锁码

输入:是CodeInit的返回值

返回值:成功则不为0,否则为0

ps:不成功也包括没有可用于更新的解锁码了,例如已经加到9999999999999999

发挥想象,比如可以在失败时将当前状态写入磁盘等

### 3.

```c_cpp
(void) __fastcall CodeExit(void *);
```

在退出(错误或完成等)时调用,可用于销毁储存状态的结构体等(发挥想象)

输入是CodeInit的返回值

只要unlockhwbl.exe进程正常退出(不包括信号退出,但包括错误)就一定会调用CodeExit

应该将输入值0的行为写成什么都不做