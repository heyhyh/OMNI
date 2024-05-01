//
// Created by 86189 on 2024/4/9.
//
#include "ATTACK.h"
#include "can.h"
#include "main.h"
#include "MOTOR.h"
#include "PID.h"
#include "define.h"
#include "MATH.h"
#include "GIMBAL.h"

YUN_TYPEDEF_MOTOR ATTACK[4]= { };
YUN_TYPEDEF_TOP TEST_1{ };
////0：拨弹 1：摩擦轮左 2：摩擦轮右

////退弹标志位
const float PID_P[5] = {4,0.001,0,3000,3000};
const float PID_S[5] = {4,0.001,0,3000,3000};

int jam_time = 0;
int flag = 0;
int single_lock = 0;


int YUN_F_JAM( )
{
    YUN_F_CAN_RECEIVE(ATTACK,&TEST_1,YUN_D_CAN_2);
    if (jam_time > 3000 && ATTACK[0].DATA.SPEED_NOW <= 200 && ATTACK[0].DATA.ANGLE_NOW - ATTACK[0].DATA.ANGLE_LAST<=200 &&flag == -1 )
    {
        ATTACK[0].DATA.AIM += 200;
        YUN_F_MOTOR_PID_GIMBAL(&ATTACK[0],ATTACK[0].DATA.ANGLE_NOW,ATTACK[0].DATA.SPEED_NOW);
        flag = 0;
        return false;
    }

    if (jam_time > 3000 && ATTACK[0].DATA.SPEED_NOW <= 200 && ATTACK[0].DATA.ANGLE_NOW - ATTACK[0].DATA.ANGLE_LAST<=200 && flag == 0)
    {
        ATTACK[0].DATA.AIM -= 200;
        YUN_F_MOTOR_PID_GIMBAL(&ATTACK[0],ATTACK[0].DATA.ANGLE_NOW,ATTACK[0].DATA.SPEED_NOW);
        flag = 1;
        return false;
    }

    else
    {
        return true;
    }
}

void YUN_F_SIGLE()
{


}



[[noreturn]] void YUN_F_ATTACK_THREAD( )
{
    while (1)
    {
        YUN_F_PID_INIT(&ATTACK[0].PID_P,PID_P,1000,3000);
        YUN_F_PID_INIT(&ATTACK[0].PID_P,PID_P,1000,3000);
        if (YUN_F_JAM())//没堵弹
        {
            if(dbus_data.REMOTE.s1_u8 == 2 && single_lock == 0)//单发不上锁
            {
                ATTACK[0].DATA.AIM = ATTACK[0].DATA.ANGLE_INFINITE + 200;
                YUN_F_MOTOR_PID_GIMBAL(&ATTACK[0],ATTACK[0].DATA.ANGLE_NOW,ATTACK[0].DATA.SPEED_NOW);
                jam_time = 0;
                single_lock = 1;
            }
            else if(dbus_data.REMOTE.s1_u8 == 2 && single_lock == 1)//单发上锁
            {

            }

            else if (dbus_data.REMOTE.s1_u8 == 1)//连发
            {
                ATTACK[0].DATA.AIM = ATTACK[0].DATA.AIM = ATTACK[0].DATA.ANGLE_INFINITE + 200;
                YUN_F_MOTOR_PID_GIMBAL(&ATTACK[0],ATTACK[0].DATA.ANGLE_NOW,ATTACK[0].DATA.SPEED_NOW);

            }

        }

        //卡弹时间积累：排除不发弹清空和单发上锁情况
        if((ATTACK[0].DATA.SPEED_NOW < 200 && dbus_data.REMOTE.s1_u8 != 3) ||(ATTACK[0].DATA.SPEED_NOW < 200 && dbus_data.REMOTE.s1_u8 == 2 && single_lock == 1) )
        {
            jam_time ++;
            ATTACK[0].DATA.ANGLE_LAST = ATTACK[0].DATA.ANGLE_INFINITE;
        }

        YUN_F_CAN_SEND(YUN_D_CAN_2,0x200,0,0,ATTACK[0].PID_S.out.ALL_OUT,0);

        if (dbus_data.REMOTE.s1_u8 == 3)//单发解锁
        {
            single_lock = 0;
        }
    }

}