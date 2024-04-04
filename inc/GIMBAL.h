//
// Created by 86189 on 2024/3/31.
//

#ifndef DEMO_GIMBAL_H
#define DEMO_GIMBAL_H

#include "MOTOR.h"
#include "can.h"
#include "define.h"
#include "PID.h"
#include "UART.h"

extern void GIMBAL_CAL();
[[noreturn]] void YUN_F_GIMBAL_THREAD(TYPEDEF_DBUS *YUN_V_DBUS);
#endif //DEMO_GIMBAL_H
