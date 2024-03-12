//
// Created by 86189 on 2024/1/19.
//

//#include "MOTOR.h"
#include <cstdint>
#include "../inc/define.h"
#include "../inc/MOTOR.h"

void YUN_F_MOTOR_CAN_RX(YUN_TYPEDEF_MOTOR *MOTOR,const uint8_t *CAN_DATA,uint8_t TYPE, uint8_t STATUS_ID)
{
    MOTOR->DATA.ANGLE_LAST = MOTOR->DATA.ANGLE_NOW;

    MOTOR->DATA.ANGLE_NOW = (int16_t)(((CAN_DATA[0] << 8) | CAN_DATA[1]) & 0xFFFF);

    MOTOR->DATA.SPEED_LAST = MOTOR->DATA.SPEED_NOW;

    MOTOR->DATA.SPEED_NOW = (int16_t)(((CAN_DATA[2] << 8) | CAN_DATA[3]) &0xFFFF);

    MOTOR->DATA.CURRENT = (int16_t)(((CAN_DATA[4] << 8) | CAN_DATA[5]) &0xFFFF);



    YUN_V_MONITOR.TIME[STATUS_ID] = YUN_D_STATUS_JUDGE_TIME_MOTOR;

    switch (TYPE)
    {
//        case YUN_D_MOTOR_TYPE_3508: break;
//        case YUN_D_MOTOR_TYPE_2006:;
        case YUN_D_MOTOR_TYPE_6020:
    {
        auto ANGLE_ERRO_INIT = (int16_t) (MOTOR->DATA.ANGLE_NOW - MOTOR -> DATA.ANGLE_INIT);
        auto ANGLE_ERROR_NOW_LAST = (int16_t) (MOTOR -> DATA.ANGLE_NOW - MOTOR->DATA.ANGLE_LAST);

        if(ANGLE_ERROR_NOW_LAST < -4096)
        {
            MOTOR ->DATA.LAPS++;
        }else if (ANGLE_ERROR_NOW_LAST > 4096)
        {
            MOTOR->DATA.LAPS--;
        }
        if((MOTOR ->DATA.LAPS >32) | (MOTOR->DATA.LAPS < -32))
        {
            MOTOR->DATA.LAPS = 0;
            MOTOR->DATA.AIM = MOTOR->DATA.ANGLE_NOW;
        }
        if (ANGLE_ERRO_INIT <-4000)
        {
            ANGLE_ERRO_INIT -= 8192;
        }else if(ANGLE_ERRO_INIT > 4096)
        {
            MOTOR->DATA.ANGLE_RELATIVE = ANGLE_ERRO_INIT;
            MOTOR->DATA.ANGLE_INFINITE = (int32_t)((MOTOR->DATA.LAPS << 13) + MOTOR->DATA.ANGLE_NOW);
        }
            break;

    }

    }
}


//电机清空函数
void YUN_F_MOTOR_CLEAR(YUN_TYPEDEF_MOTOR *MOTOR,uint8_t TYPE)
{
    MOTOR->DATA.LAPS = 0;
    MOTOR->PID_P.out.I_OUT = 0.0f;
    MOTOR->PID_S.out.I_OUT = 0.0f;
switch (TYPE)
{
    case YUN_D_MOTOR_TYPE_6020:
    {
        break;
    };
    case YUN_D_MOTOR_TYPE_2006:
    {
        // MOTOR->DATA.AIM = MOTOR->DATA.ANGLE_INFINITE;
            break;
    }
    default:break;
}
}