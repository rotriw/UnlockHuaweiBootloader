# 系统要求

#### 用随机模式 <u>windows x64</u>

#### 不用随机模式 <u>windows x86 或 windows x64</u>

###### ~~linux用户对这些简单的指令一定非常熟悉,自己编译一下"main.c"就好啦(~~

***

# 步骤说明

###### ~~这一段比较懒直接复制过来了~~

首先将手机连接到电脑,然后打开手机的usb调试,然后运行"检查是否已连接到手机.bat",非fastboot模式如果"List of devices attached"下面是一个空行再下面就是类似"按任意键继续"之类的了就说明手机没连上,fastboot模式下没连上是啥也没有直接"按任意键继续"
确保连接后如果不在fastboot下则运行"进入fastboot.bat"(可以再用fastboot模式检查一下是否连接),然后运行"编译.bat"来编译解锁程序,如果之前已经编译好了"main.exe"就不用了

***

# 参数说明

## mode

解锁模式

#### 0:枚举

#### 1:随机

<br/>

## order

顺序,只有枚举模式才有

#### 0:正序,0000000000000000-9999999999999999

#### 1:倒序,9999999999999999-0000000000000000

<br/>

## puk

每一位从哪个数字开始,只有枚举模式才有,需要输入16位数字,0-9


# 其他
## platform-tools更新链接
### windows:
https://dl.google.com/android/repository/platform-tools-latest-windows.zip
### linux:
https://dl.google.com/android/repository/platform-tools-latest-linux.zip
### mac:
https://dl.google.com/android/repository/platform-tools-latest-darwin.zip

## 试一下自动生成代码,目前看来还不错
