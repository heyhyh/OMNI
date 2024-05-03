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

YUN_TYPEDEF_MOTOR ATTACK[4]= {0};
YUN_TYPEDEF_TOP TEST_1{ };
////0：拨弹 1：摩擦轮左 2：摩擦轮右

////退弹标志位
const float PID_P[5] = {1,0,0,3000,1000};
const float PID_S[5] = {5,0,0,3000,3000};

int jam_time = 0;
int flag = 0;
int single_lock = 0;
int32_t jam_angle = 0;

int YUN_F_JAM( )
{

//    && (ATTACK[0].DATA.ANGLE_INFINITE - jam_angle<=50000)
    if ((jam_time > 300) && (ATTACK[0].DATA.SPEED_NOW <= 200)  &&(flag == 1) )
    {
//        printf("flag:%d",-1);
        ATTACK[0].DATA.AIM =(float )ATTACK[0].DATA.ANGLE_INFINITE + 3600000.0f;
        flag = 0;
        jam_time = 0;
        return false;
    }

    if ((jam_time > 300) && (ATTACK[0].DATA.SPEED_NOW <= 200) && (flag == 0))
    {
//        printf("flag:%d",0);
        ATTACK[0].DATA.AIM = (float )ATTACK[0].DATA.ANGLE_INFINITE - 3600000.0f;
        flag = 1;
        jam_time = 0;
        return false;
    }

    else
    {
        return true;
    }
}



//有空把单发封装一下，有点多了
[[noreturn]] void YUN_F_ATTACK_THREAD( ) {
    YUN_F_PID_INIT(&ATTACK[0].PID_P, PID_P, 1000, 3000);
    YUN_F_PID_INIT(&ATTACK[0].PID_S, PID_S, 1000, 3000);
    jam_time = 0;
//    printf("PID %f %f %f\n",ATTACK[0].PID_S.IN.P,ATTACK[0].PID_S.IN.I_LIT,ATTACK[0].PID_S.IN.ALL_LIT);
    while (1)
    {
        YUN_F_CAN_RECEIVE(ATTACK, &TEST_1, YUN_D_CAN_2);
//        &&(ATTACK[0].DATA.ANGLE_INFINITE - jam_angle<=20000)
        if ((ATTACK[0].DATA.SPEED_NOW < 2000) && (dbus_data.REMOTE.s1_u8 == 1) )
        {
            jam_time ++ ;
//            jam_angle = ATTACK[0].DATA.ANGLE_INFINITE;
        }
        if ((ATTACK[0].DATA.SPEED_NOW < 2000) && (dbus_data.REMOTE.s1_u8 ==2))
        {
            jam_time ++ ;
//            jam_angle = ATTACK[0].DATA.ANGLE_INFINITE;
        }
//        jam_angle = ATTACK[0].DATA.ANGLE_INFINITE;
        if (YUN_F_JAM())//没堵弹
        {
            if (dbus_data.REMOTE.s1_u8 == 3)//单发解锁
            {
                single_lock = 0;
//                ATTACK[0].DATA.AIM = ATTACK[0].DATA.ANGLE_INFINITE;//存疑，我觉得目标值下降是因为这句话，电机还没转到目标值程序就运行到这，然后把目标值更新为中途的角度
                //单发感觉不需要上边这句话，连发为了方便随时停止才需要
            }
//        if (dbus_data.REMOTE.s1_u8 == )

            if ((dbus_data.REMOTE.s1_u8 == 1)&&(jam_time < 500))//单发不上锁
            {

                if (single_lock == 0)
                {
                    ATTACK[0].DATA.AIM = (float) ATTACK[0].DATA.ANGLE_INFINITE + 3600050.0f;
                    single_lock = 1;
                }

            }
//3600050.0f;
//            if(dbus_data.REMOTE.s1_u8 == 3)
//            {
//            ATTACK[0].DATA.AIM = ATTACK[0].DATA.ANGLE_INFINITE;
//            }
//            && (jam_time < 500)
            else if ((dbus_data.REMOTE.s1_u8 == 2)&&(jam_time < 500))//连发
            {

                ATTACK[0].DATA.AIM = (float) ATTACK[0].DATA.ANGLE_INFINITE + 36000.0f;

            }

            //卡弹时间积累：排除不发弹情况和单发上锁情况

//            if ((ATTACK[0].DATA.SPEED_NOW < 200) && (dbus_data.REMOTE.s1_u8 == 1) && (single_lock != 1)) {
//                jam_time += 20;
//                jam_angle = ATTACK[0].DATA.ANGLE_INFINITE;
//            }
        }
            YUN_F_MOTOR_PID_GIMBAL(&ATTACK[0], ATTACK[0].DATA.ANGLE_INFINITE, ATTACK[0].DATA.SPEED_NOW);
            YUN_F_CAN_SEND(YUN_D_CAN_2, 0x200, 0, 0, (int16_t) ATTACK[0].PID_S.out.ALL_OUT, 0);

//        printf("MOD %d LOCK %d ANGLE %d AIM %f\n",dbus_data.REMOTE.s1_u8,single_lock,ATTACK[0].DATA.ANGLE_INFINITE,ATTACK[0].DATA.AIM);
        printf("%d\n",jam_time);
//        printf("%d\n",ATTACK[0].DATA.ANGLE_INFINITE);

//        }

    }
}