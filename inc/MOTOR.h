//
// Created by 86189 on 2024/1/19.
//

#ifndef DEMO_MOTOR_H
#define DEMO_MOTOR_H
#include <cstdint>

#include "cstdint"
#include "define.h"
#include "ROOT_INIT.h"
uint8_t can1_data[8];


struct YUN_MOTOR_DATA_Typedef
{
    int8_t  ONLINE_JUDGE_TIME;
    int16_t ANGLE_LAST;
    int16_t ANGLE_NOW;
    int16_t SPEED_LAST;
    int16_t SPEED_NOW;
    int32_t CURRENT;
    int32_t ANGLE_INFINITE;
    int32_t ANGLE_INIT;
    int16_t ANGLE_RELATIVE;
    uint16_t  STUCK_TIME;
    int16_t LAPS;
    float AIM;
    float AIM_LAST;
};

struct  YUN_MOTOR_PID_Typedef
{
    struct
    {
        float P;
        float I;
        float D;
        float I_LIT;
        float ALL_LIT;

    }IN;
    struct
    {
        float ERROR[2];
        float P_OUT;
        float I_OUT;
        float D_OUT;
                float ALL_OUT;

    }out;
};
typedef struct YUN_TYPEDEF_MOTOR
{
    uint8_t PID_INIT;
    struct YUN_MOTOR_DATA_Typedef DATA;
    struct YUN_MOTOR_PID_Typedef PID_P;
    struct YUN_MOTOR_PID_Typedef PID_S;
    struct YUN_MOTOR_PID_Typedef PID_C;//电流环
}YUN_TYPEDEF_MOTOR;

YUN_TYPEDEF_MOTOR MOTOR6020;
void YUN_F_MOTOR_CAN_RX(YUN_TYPEDEF_MOTOR *MOTOR, const uint8_t *CAN_DATA, uint8_t TYPE, uint8_t STATUS_ID);
//头部电机清空函数
void YUN_F_MOTOR_CLEAR(YUN_TYPEDEF_MOTOR *MOTOR, uint8_t TYPE);
void *YUN_F_MOTOR_CAN_RX_NEW(void *MOTOR, const uint8_t *DATA);
#endif //DEMO_MOTOR_H
