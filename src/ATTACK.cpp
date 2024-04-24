//
// Created by 86189 on 2024/4/9.
//
#include "ATTACK.h"
#include "can.h"
#include "main.h"
#include "MOTOR.h"


YUN_TYPEDEF_MOTOR ATTACK[3];
//0：拨弹 1：摩擦轮左 2：摩擦轮右
int accum = 0;
//退弹标志位
[[noreturn]] void YUN_F_ATTACK_THREAD()
{
    int flag = 0;
    //先写单发模式拨弹
    while(1)
    {
        if (accum >= 3)//卡弹检测(有空用函数封装一下)
        {
            if (flag == 1)
            {
                ATTACK[0].DATA.AIM -= 2r;
                flag = 0;
                accum = 0;
            }

            if(flag == 0)
            {
                ATTACK[0].DATA.AIM += 2r;
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
                    ATTACK[0].DATA.AIM += 2r;//弹丸直径待测量

                    if (ATTACK[0].DATA.ANGLE_NOW - ATTACK[0].DATA.ANGLE_LAST < 2r)
                        accum++;
                break;
            }



        }
        else
            break;
        YUN_F_CAN_SEND( );

    }


}
