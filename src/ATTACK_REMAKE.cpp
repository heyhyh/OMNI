//
// Created by 86189 on 2024/4/26.
//
#include "ATTACK.h"
#include "ATTACK.h"
#include "can.h"
#include "main.h"
#include "MOTOR.h"
#include "PID.h"

//YUN_TYPEDEF_MOTOR ATTACK_MOTOR[3];
////0：拨弹 1：摩擦轮左 2：摩擦轮右
//[[noreturn]] void YUN_F_ATTACK_THREAD()
//{int accum = 0;
//    int ATTACK[2] = { };
//    while(1)
//    {
//        switch (ATTACK[0])
//        {
//            case YUN_D_ATTACK_NOR:
//                {
//                    ATTACK_MOTOR[0].DATA.ANGLE_LAST = ATTACK_MOTOR[0].DATA.ANGLE_NOW;
//                    ATTACK_MOTOR[0].DATA.AIM += 2r;//弹丸直径待 测量
//
//                    if (ATTACK_MOTOR[0].DATA.ANGLE_NOW - ATTACK_MOTOR[0].DATA.ANGLE_LAST < 2r)//检测卡弹
//                        accum ++;
//                    else
//                    {
//                        accum= 0;
//                        ATTACK[0] = YUN_D_ATTACK_NOR;
//                    }
//
//                    YUN_F_CAN_SEND()
//                }
//            case YUN_D_ATTACK_JAM_NEG:   //卡弹反退
//                {   ATTACK[YUN_D_NOW] = ATTACK[YUN_D_LAST];
//                    ATTACK_MOTOR[0].DATA.AIM -= 2r;
//                    YUN_F_MOTOR_PID_GIMBAL(&ATTACK_MOTOR[1],ATTACK_MOTOR[1].DATA.ANGLE_NOW,ATTACK_MOTOR[1].DATA.SPEED_NOW);
//                    YUN_F_CAN_SEND();
//                }
//                if(accum >=3])
//                    ATTACK[YUN_D_NOW] ++;
//                break;
//            case
//        }
//    }


//}
