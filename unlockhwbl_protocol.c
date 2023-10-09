#include "util.c"
#include "adb_api.h"
//usb的句柄(api不需要它,仅内部使用),里面包含了三个adb的句柄(usb_windows.cpp)
typedef struct{
    /// Handle to USB interface
    ADBAPIHANDLE  adb_interface;
    /// Handle to USB read pipe (endpoint)
    ADBAPIHANDLE  adb_read_pipe;
    /// Handle to USB write pipe (endpoint)
    ADBAPIHANDLE  adb_write_pipe;
    //没用上的部分删了
}usb_handle;
//全局的usb句柄浅拷贝
usb_handle *__handle;
#define handle (*__handle)

//关闭usb设备(usb_cleanup_handle)
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
void CloseDevice(void){
    if(handle.adb_write_pipe)
        AdbCloseHandle(handle.adb_write_pipe);
    if(handle.adb_read_pipe)
        AdbCloseHandle(handle.adb_read_pipe);
    if(handle.adb_interface)
        AdbCloseHandle(handle.adb_interface);
    handle.adb_write_pipe=0;
    handle.adb_read_pipe=0;
    handle.adb_interface=0;
}

//初始化usb设备(find_usb_device,recognized_device,do_usb_open)
__attribute__((noinline))
__attribute__((cold))
__attribute__((minsize))
void MatchFastbootDevice(void){
    char entry_buffer[2048];
    unsigned long temp;
    AdbInterfaceInfo *next_interface = (AdbInterfaceInfo *)entry_buffer;
    USB_INTERFACE_DESCRIPTOR interf_desc;
    //获取环境变量的设备名,env_serial的长度(a)包括空字节,所以它成功时至少为1
    char env_serial[256],serial_number[256];
    DWORD a=GetEnvironmentVariableA("ANDROID_SERIAL",env_serial,256),b;
    //打开一个枚举句柄,GUID={F72FE0D4-CBCB-407d-8814-9ED673D0DD6B}
    #define ANDROID_USB_CLASS_ID \
    {0xf72fe0d4,0xcbcb,0x407d,{0x88,0x14,0x9e,0xd6,0x73,0xd0,0xdd,0x6b}}
    GUID usb_class_id=ANDROID_USB_CLASS_ID;
    ADBAPIHANDLE enum_handle = AdbEnumInterfaces(usb_class_id,true,true,true);
    if(enum_handle==0)
        Error("AdbEnumInterfaces");
    //枚举循环
    for(;;){
        //关闭上一次的句柄
        close_device_and_reset:
        CloseDevice();
        //枚举设备,返回0代表没有设备需要枚举了
        temp=2048;
        if(AdbNextInterface(
            enum_handle,
            next_interface,
            &temp
        )==0)break;
        Print("+ AdbNextInterface FoundDevice");
        /*
        这里有一段将((AdbInterfaceInfo *)entry_buffer)->device_name(应该是UNICODE)
        转为ANSI拷贝到栈上2kb缓冲区(和entry_buffer一样大)的代码,但这个转换并不严谨
        只是(char)wchar转换(还有个TODO:最好修改AdbWinApi.dll让它直接返回ANSI)
        这段代码在find_usb_device函数,并且转换完的内容(是interface_name吗)并没有被使用
        同时在下面(do_usb_open,打开三个句柄后)里使用了AdbGetInterfaceName(包含错误检查)
        将interface_name保存到usb_handle结尾的变长空间中,但它同样没有被使用
        我将这两段多余的都去掉了,唯一的副作用应该是去除了AdbGetInterfaceName的错误检查
        其实应该将AdbGetInterfaceName的内容保存到栈上空间,但我不知道分配多大的空间合适
        因为它使用了变长空间而不是和entry_buffer一样大的2kb空间,并且使用u32表示空间大小
        一个较为合理的猜测是同样分配2kb空间,但它毕竟是猜测,所以我还是决定把这段删掉
        */
        //打开interface,失败则枚举下一个设备
        handle.adb_interface=AdbCreateInterfaceByName(next_interface->device_name);
        if(handle.adb_interface == 0){
            Print("- AdbCreateInterfaceByName SkipDevice");
            goto close_device_and_reset;
        }
        //打开读端管道(endpoint),失败则枚举下一个设备
        handle.adb_read_pipe = AdbOpenDefaultBulkReadEndpoint(
            handle.adb_interface,
            AdbOpenAccessTypeReadWrite,
            AdbOpenSharingModeReadWrite
        );
        if(handle.adb_read_pipe == 0){
            Print("- AdbOpenDefaultBulkReadEndpoint SkipDevice");
            goto close_device_and_reset;
        }
        //打开写端管道(endpoint),失败则枚举下一个设备
        handle.adb_write_pipe = AdbOpenDefaultBulkWriteEndpoint(
            handle.adb_interface,
            AdbOpenAccessTypeReadWrite,
            AdbOpenSharingModeReadWrite
        );
        if(handle.adb_write_pipe == 0){
            Print("- AdbOpenDefaultBulkWriteEndpoint SkipDevice");
            goto close_device_and_reset;
        }
        /*没用上,但包含错误检查
        //Check vendor and product id first(获取供应商和产品id?),失败则枚举下一个设备
        USB_DEVICE_DESCRIPTOR device_desc;
        if(AdbGetUsbDeviceDescriptor(handle.adb_interface,&device_desc)==0){
            Print("- NoDeviceDescriptor");
            goto close_device_and_reset;
        }
        */
        //Then check interface properties(获取接口属性),失败则枚举下一个设备
        if(AdbGetUsbInterfaceDescriptor(handle.adb_interface,&interf_desc)==0){
            Print("- AdbGetUsbInterfaceDescriptor SkipDevice");
            goto close_device_and_reset;
        }
        //检查刚才获取的内容,不匹配则枚举下一个设备
        if(
            //必须有两个endpoint
            (interf_desc.bNumEndpoints != 2)||
            //检查类型(属性?)
            (interf_desc.bInterfaceClass != 0xff)||
            (interf_desc.bInterfaceSubClass != 0x42)||
            (interf_desc.bInterfaceProtocol != 0x03)
        ){
            Print("- InterfaceDescriptorNotMatched SkipDevice");
            goto close_device_and_reset;
        }
        //如果指定了设备名称,则需要匹配相同的usb名称(serial_number),不匹配则枚举下一个设备
        if(a){
            //获取当前usb的序列号(serial_number),获取失败则枚举下一个设备
            temp=256;
            if(AdbGetSerialNumber(
                handle.adb_interface,
                serial_number,
                &temp,
                true
            )==0){
                Print("- AdbGetSerialNumber SkipDevice");
                goto close_device_and_reset;
            }
            //比较两块储存序列号的内存(包括结尾0,即比较字符串),不相等则枚举下一个设备
            for(b=0;b<a;b++){
                if(env_serial[b]!=serial_number[b]){
                    Print("- SerialNumberNotMatched SkipDevice");
                    goto close_device_and_reset;
                }
            }
        }
        //符合要求,退出枚举设备的循环
        break;
    }
    //关闭枚举句柄
    AdbCloseHandle(enum_handle);
}

//入口函数,为了与AdbWinApi的类型匹配只好不用stdint里的类型了
#define __ExitEx CloseDevice()
#define RESPONSE_SIZE (256)
#define TIMEOUT (5000)
void Main(void){
    Init();
    //fastboot的read缓冲区,需要一个空字节
    char fbdr[RESPONSE_SIZE+1];
    //读写设备用,当前缓冲区指针,本次处理的字节数和剩余字节
    char *pnow;
    unsigned long cnow,temp;
    //初始化fastboot设备
    usb_handle fusb={0};
    __handle=&fusb;
    MatchFastbootDevice();
    if(fusb.adb_interface == 0)
        Error("NoDevice");
    else
        Print("MatchedDevice");

    //循环发送命令直到收到"OKAY"包
    while(work){
        //写入设备,5秒超时,必须完全将数据写入,一次不行就多来几次
        pnow=fcmd;
        temp=clen;
        while(temp){
            if(AdbWriteEndpointSync(
                fusb.adb_write_pipe,
                pnow,
                temp,
                &cnow,
                TIMEOUT
            )==0)Error("AdbWriteEndpointSync");
            temp-=cnow;
            pnow+=cnow;
        }

        //循环接受响应包,只有FAIL包才会导致解锁码更新
        for(;;){
            //读取设备,5秒超时,最多读取一些数量的字节,可以不足
            if(AdbReadEndpointSync(
                fusb.adb_read_pipe,
                fbdr,
                RESPONSE_SIZE,
                &cnow,
                TIMEOUT
            )==0)Error("AdbReadEndpointSync");

            //包长度不足(头部4字节)
            if(cnow<4)
                goto pkterror;
            //如果是FAIL包,则读取结束,更新解锁码
            if(fbdr[0]=='F' && fbdr[1]=='A' && fbdr[2]=='I' && fbdr[3]=='L'){
                #pragma nounroll
                CodeUpdate();
                break;
            }
            //如果是OKAY包,则解锁成功,断开连接,退出程序
            if(fbdr[0]=='O' && fbdr[1]=='K' && fbdr[2]=='A' && fbdr[3]=='Y'){
                Print(fcmd);
                goto ends;
            }

            //如果是INFO或TEXT(可能是新规定,反正抄过来就对了)包,则继续读取包
            if(
                (fbdr[0]=='I' && fbdr[1]=='N' && fbdr[2]=='F' && fbdr[3]=='O')||
                (fbdr[0]=='T' && fbdr[1]=='E' && fbdr[2]=='X' && fbdr[3]=='T')
            ){
                continue;
            }
            //不匹配上面的几个包类型,其他包类型(已知DATA,或其他未知的类型)视为错误
            pkterror:
            fbdr[cnow]=0;
            Print(fbdr);
            Error("Packet");
        }
    }
    ends:
    Exit();
}