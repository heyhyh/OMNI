//
// Created by 86189 on 2024/1/30.
//

#ifndef DEMO_DEBUG_H
#define DEMO_DEBUG_H

#include "MOTOR.h"
#include "define.h"
struct  YUN_MOTOR_DATA_DEBUG_Typedef
{
    float ANGLE;
    float SPEED;
    float CURRENT;
    float ANGLE_INFINITE;
    float LAPS;
    float AIM;
};

struct YUN_TYPEDEF_DEBUG
{
    struct YUN_MOTOR_DATA_DEBUG_Typedef DATA;
    struct YUN_MOTOR_PID_Typedef PID_P;
    struct YUN_MOTOR_PID_Typedef PID_S;
    struct YUN_MOTOR_PID_Typedef PID_C;//电流环

};

extern struct YUN_TYPEDEF_DEBUG YUN_V_DEBUG[10];
[[noreturn]] void YUN_F_DEBUG_THREAD();
#endif //DEMO_DEBUG_H
