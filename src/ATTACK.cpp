//
// Created by 86189 on 2024/4/9.
//
#include "ATTACK.h"
#include "can.h"
#include "main.h"
#include "MOTOR.h"
#include "PID.h"

YUN_TYPEDEF_MOTOR ATTACK[3];
//0：拨弹 1：摩擦轮左 2：摩擦轮右
int accum = 0;
//退弹标志位
[[noreturn]] void YUN_F_ATTACK_THREAD()
{
    ATTACK[2].DATA.AIM = 3000;
    ATTACK[3].DATA.AIM = -3000;
    int flag = 0;
    //先写单发模式拨弹
    while(1)
    {
        YUN_F_MOTOR_PID_SC(&ATTACK[2]);
        YUN_F_MOTOR_PID_SC(&ATTACK[3]);

        if (accum >= 3)//卡弹检测(有空用函数封装一下)
        {
            if (flag == 1)
            {
                ATTACK[0].DATA.AIM -= 2r;
                YUN_F_MOTOR_PID_GIMBAL(&ATTACK[1],ATTACK[1].DATA.ANGLE_NOW,ATTACK[1].DATA.SPEED_NOW);

                flag = 0;
                accum = 0;
            }

            if(flag == 0)
            {
                ATTACK[0].DATA.AIM += 2r;
                YUN_F_MOTOR_PID_GIMBAL(&ATTACK[1],ATTACK[1].DATA.ANGLE_NOW,ATTACK[1].DATA.SPEED_NOW);

                flag = 1;
                accum = 0;
            }
        }

        if (dbus_data.REMOTE.s1_u8 == 1)
        {
            while(1)
            if (dbus_data.REMOTE.s1_u8 == 3)
            {
                    ATTACK[0].DATA.ANGLE_LAST = ATTACK[0].DATA.ANGLE_NOW;
                    ATTACK[0].DATA.AIM += 2r;//弹丸直径待 测量

                if (ATTACK[0].DATA.ANGLE_NOW - ATTACK[0].DATA.ANGLE_LAST < 2r)//检测卡弹
                    accum++;
                YUN_F_MOTOR_PID_GIMBAL(&ATTACK[1],ATTACK[1].DATA.ANGLE_NOW,ATTACK[1].DATA.SPEED_NOW);
                YUN_F_CAN_SEND();

                break;
            }



        }
        else
            break;
        YUN_F_CAN_SEND( );

    }


}
