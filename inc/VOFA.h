//
// Created by 86189 on 2024/3/22.
//

#ifndef DEMO_VOFA_H
#define DEMO_VOFA_H
// VOFA 数据包
#include "MOTOR.h"
#include "UART.h"
#include "TOP.h"
typedef struct YUN_TYPEDEF_DEBUG
{
    struct
    {
        float ANGLE;
        float SPEED;
        float CURRENT;
        float ANGLE_INFINITE;
        float LAPS;
        float AIM;
    }MOTOR_DATA;
//    struct
//    {
//        float MECANUM[4];
//        float GIMBAL[2];
//    }TARGET;
    YUN_MOTOR_PID_Typedef PID_A;
    YUN_MOTOR_PID_Typedef PID_S;
    YUN_MOTOR_PID_Typedef PID_C;
}YUN_TYPEDEF_DEBUG_;

typedef union
{
    struct
    {
        YUN_TYPEDEF_DEBUG_ YUN_V_MOTOR_DEBUG;
        char TAIL[4];
    } DATA;
    char ALL[160];
}YUN_TYPEDEF_SEND_UNION;
typedef union
{
    struct
    {
        char NAME[12];
        float PARAM;
    } DATA;
    char ALL[16];
}YUN_TYPEDEF_RECV_UNION;



void YUN_F_VOFA_PARSE(YUN_TYPEDEF_RECV_UNION *RECV);
void YUN_F_VOFA_DEBUG_CAL(YUN_TYPEDEF_DEBUG *DEBUG, YUN_TYPEDEF_MOTOR *MOTOR);
void YUN_F_VOFA_DEBUG();
void YUN_F_VOFA_ASSIGN(YUN_TYPEDEF_RECV_UNION *RECV);


[[noreturn]] void YUN_F_THREAD_VOFA();
#endif //DEMO_VOFA_H
