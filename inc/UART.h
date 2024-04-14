//
// Created by 86189 on 2024/3/15.
//

#ifndef DEMO_UART_H
#define DEMO_UART_H
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <asm-generic/termbits.h>
#include <linux/serial.h>
#include <sys/ioctl.h>

#include "define.h"

typedef struct TYPEDEF_DBUS
{
    uint8_t R_FLAG;
    uint8_t L_FLAG;

    //遥控
    struct
    {
        int16_t CH0_int16;
        int16_t CH1_int16;
        int16_t CH2_int16;
        int16_t CH3_int16;
        int16_t DIR_int16;
        uint8_t s1_u8;
        uint8_t s2_u8;

        int8_t Error_int8;
    } REMOTE;

//    //鼠标先不写
//
} TYPEDEF_DBUS_;

union TYPEDEF_DBUS_UNION//共用体整合数据
{
    struct{
        //遥控数据
        uint64_t CH0: 11;
        uint64_t CH1: 11;
        uint64_t CH2: 11;
        uint64_t CH3: 11;
        uint64_t s1: 2;
        uint64_t s2: 2;


        // 鼠标数据
        int64_t MOUSE_X: 16;
        int64_t MOUSE_Y: 16;
        int64_t MOUSE_Z: 16;
        int64_t MOUSE_L: 8;
        int64_t MOUSE_R: 8;
        // 键盘数据
        uint64_t KEY_BOARD_W: 1;
        uint64_t KEY_BOARD_S: 1;
        uint64_t KEY_BOARD_A: 1;
        uint64_t KEY_BOARD_D: 1;
        uint64_t KEY_BOARD_SHIFT: 1;
        uint64_t KEY_BOARD_CTRL: 1;
        uint64_t KEY_BOARD_Q: 1;
        uint64_t KEY_BOARD_E: 1;
        uint64_t KEY_BOARD_R: 1;
        uint64_t KEY_BOARD_F: 1;
        uint64_t KEY_BOARD_G: 1;
        uint64_t KEY_BOARD_Z: 1;
        uint64_t KEY_BOARD_X: 1;
        uint64_t KEY_BOARD_C: 1;
        uint64_t KEY_BOARD_V: 1;
        uint64_t KEY_BOARD_B: 1;
        //遥控滑轮数据
        uint64_t DIR: 11;
        uint64_t : 0;

    } DATA_NEATEN;
    //接收到的数组
    uint8_t GET_DATA[19];
};


[[noreturn]] void YUN_F_DBUS_THREAD(TYPEDEF_DBUS *YUN_V_DBUS);

#endif //DEMO_UART_H
