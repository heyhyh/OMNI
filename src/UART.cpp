//
// Created by 86189 on 2024/3/16.
#include "UART.h"
#include "ROOT_INIT.h"
//#include <iostream>
//#include "stdbool.h"
#include "define.h"

#define DBUS 1

[[noreturn]] void YUN_F_DBUS_THREAD(TYPEDEF_DBUS *YUN_V_DBUS)
{
    int8_t UART_FD;

    printf("串口初始化");


    struct termios2 OPTIONS{ };

    UART_FD = (int8_t) open("/dev/ttyTHS0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (UART_FD > 0) {
        printf("串口成功打开");
    } else {
        printf("串口打开失败");

    }
//    printf("UART_FD =  %d\n", UART_FD);

    OPTIONS.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    OPTIONS.c_iflag |= (INPCK | IGNPAR);
    OPTIONS.c_oflag &= ~OPOST;
    OPTIONS.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    OPTIONS.c_cflag &= ~(CSIZE | CRTSCTS | PARODD | CBAUD);
    OPTIONS.c_cflag |= (CS8 | CSTOPB | CLOCAL | PARENB | BOTHER | CREAD);
    OPTIONS.c_ispeed = 100000;
    OPTIONS.c_ospeed = 100000;
    OPTIONS.c_cc[VMIN] = 25;
    OPTIONS.c_cc[VTIME] = 0;

    if (0 != ioctl(UART_FD, TCSETS2, &OPTIONS)) {
        close(UART_FD);
//        UART_FD = -1;
        printf("串口初始化错误");
    }
    printf("成功-串口初始化");
    union TYPEDEF_DBUS_UNION YUN_V_DBUS_UNION{ };
#ifdef DBUS
    while(true)
    {
        usleep(1);
        auto FLAG = read(UART_FD,YUN_V_DBUS_UNION.GET_DATA,sizeof(YUN_V_DBUS_UNION.GET_DATA));
//        if (FLAG > 0){
//            printf(" FLAG read =  %d\n",FLAG);
//        }

        if(FLAG == 12)
        {
            YUN_V_MONITOR.TIME[YUN_D_STATUS_ID_DBUS] = 100;

            YUN_V_MONITOR.TIME[YUN_D_STATUS_ID_DBUS] = 100;

            YUN_V_DBUS->REMOTE.s1_u8 = YUN_V_DBUS_UNION.DATA_NEATEN.s1 ;
            YUN_V_DBUS->REMOTE.s2_u8 = YUN_V_DBUS_UNION.DATA_NEATEN.s2;

            YUN_V_DBUS->REMOTE.CH0_int16 = (int16_t) (YUN_V_DBUS_UNION.DATA_NEATEN.CH0 - 1024);
            YUN_V_DBUS->REMOTE.CH1_int16 = (int16_t) (YUN_V_DBUS_UNION.DATA_NEATEN.CH1 - 1024);
            YUN_V_DBUS->REMOTE.CH2_int16 = (int16_t) (YUN_V_DBUS_UNION.DATA_NEATEN.CH2 - 1024);
            YUN_V_DBUS->REMOTE.CH3_int16 = (int16_t) (YUN_V_DBUS_UNION.DATA_NEATEN.CH3 - 1024);
            YUN_V_DBUS->REMOTE.DIR_int16 = (int16_t) (YUN_V_DBUS_UNION.DATA_NEATEN.DIR - 1024);
//            printf("CH0=  %d CH1=  %d CH2=  %d CH3=  %d\n",YUN_V_DBUS->REMOTE.CH0_int16,YUN_V_DBUS->REMOTE.CH1_int16,YUN_V_DBUS->REMOTE.CH2_int16,YUN_V_DBUS->REMOTE.CH3_int16);
//            printf("s1:%d\n s2:%d",YUN_V_DBUS->REMOTE.s1_u8,YUN_V_DBUS->REMOTE.s2_u8);
        }
//        if(YUN_V_MONITOR.STATUS[YUN_D_NOW][YUN_D_STATUS_ID_DBUS] == YUN_D_STATUS_OFF)
//        {
//            memset(YUN_V_DBUS,0,sizeof (*YUN_V_DBUS));
//        }
//        printf("CH0=  %d CH1=  %d\nCH2=  %d CH3=  %d\n",YUN_V_DBUS->REMOTE.CH0_int16,YUN_V_DBUS->REMOTE.CH1_int16,YUN_V_DBUS->REMOTE.CH2_int16,YUN_V_DBUS->REMOTE.CH3_int16);
//        printf("有问题");
    }

#endif

}