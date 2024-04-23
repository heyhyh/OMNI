//
// Created by 86189 on 2024/1/30.
//
#include "MOTOR.h"
#include <fstream>
#include <map>
#include <algorithm>
#include <cstring>
#include "define.h"
#include "MATH.h"
#include "PID.h"

//速度电流双环PID
void YUN_F_MOTOR_PID_SC(YUN_TYPEDEF_MOTOR *MOTOR)
{
    MOTOR->PID_S.out.ERROR[YUN_D_NOW] = MOTOR->DATA.AIM - (float)MOTOR->DATA.SPEED_NOW;
    //比例输出
    MOTOR->PID_S.out.P_OUT = (MOTOR->PID_S.out.ERROR[YUN_D_NOW] * MOTOR->PID_S.IN.P);
    //微分输出
    MOTOR->PID_S.out.D_OUT = (MOTOR->PID_S.out.ERROR[YUN_D_NOW] - MOTOR ->PID_S.out.ERROR[YUN_D_LAST]) * MOTOR->PID_S.IN.D;
    //积分输出
    MOTOR->PID_S.out.I_OUT += (MOTOR->PID_S.out.ERROR[YUN_D_NOW] * MOTOR->PID_S.IN.I);
    MOTOR->PID_S.out.I_OUT+=MOTOR->PID_S.out.D_OUT;

    //积分限幅
//    MOTOR->PID_S.out.I_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_S.IN.I_LIT,-MOTOR->PID_S.IN.I_LIT,MOTOR->PID_S.out.I_OUT);
    //数据迭代
    MOTOR->PID_S.out.ERROR[YUN_D_LAST] = MOTOR->PID_S.out.ERROR[YUN_D_NOW];
    //速度环总输出
    MOTOR->PID_S.out.ALL_OUT = (MOTOR->PID_S.out.P_OUT + MOTOR->PID_S.out.I_OUT);
    //总输出限幅
//    MOTOR->PID_S.out.ALL_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_S.IN.ALL_LIT,-MOTOR->PID_S.IN.ALL_LIT,MOTOR->PID_S.out.ALL_OUT);


    //电流环
//    MOTOR->PID_C.out.ERROR[YUN_D_NOW] = MOTOR->PID_S.out.ALL_OUT - (float )MOTOR->DATA.CURRENT;
//    //比例输出
//    MOTOR->PID_C.out.P_OUT = (MOTOR->PID_C.out.ERROR[YUN_D_NOW] * MOTOR->PID_C.out.ERROR[YUN_D_LAST]);
//    //积分输出
//    MOTOR->PID_C.out.I_OUT += (MOTOR->PID_C.out.ERROR[YUN_D_NOW]  * MOTOR->PID_C.IN.I );
//    //微分输出
//    MOTOR->PID_C.out.D_OUT = (MOTOR->PID_C.out.ERROR[YUN_D_NOW] - MOTOR->PID_C.out.ERROR[YUN_D_LAST]) * MOTOR->PID_C.IN.D;
//    //积分限幅
//    MOTOR->PID_C.out.I_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_C.IN.I_LIT, -MOTOR->PID_C.IN.I_LIT,MOTOR->PID_C.out.I_OUT);
//    /*数据迭代*/
//    MOTOR->PID_C.out.ERROR[YUN_D_LAST] = MOTOR->PID_C.out.ERROR[YUN_D_NOW];
//    /*速度环总输出*/
//    MOTOR->PID_C.out.ALL_OUT = (MOTOR->PID_C.out.P_OUT + MOTOR->PID_C.out.I_OUT);
//    /*总输出限幅*/
//    MOTOR->PID_C.out.ALL_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_C.IN.ALL_LIT, -MOTOR->PID_C.IN.ALL_LIT, MOTOR->PID_C.out.ALL_OUT);
}

//角度速度环双环PID
void YUN_F_MOTOR_PID_GIMBAL(YUN_TYPEDEF_MOTOR *MOTOR, float TOP_ANGLE, float TOP_SPEED)
{
    MOTOR->PID_P.out.ERROR[YUN_D_NOW] = MOTOR->DATA.AIM - TOP_ANGLE;


    if (MOTOR->PID_P.out.ERROR[YUN_D_NOW] > 4096)
    {
        MOTOR->DATA.AIM -= 8192;
        MOTOR->PID_P.out.ERROR[YUN_D_NOW] -= 8192;
    } else if (MOTOR->PID_P.out.ERROR[YUN_D_NOW] < -4096)
    {
        MOTOR->DATA.AIM += 8192;
        MOTOR->PID_P.out.ERROR[YUN_D_NOW] += 8192;
    }
    /*比例输出*/
    MOTOR->PID_P.out.P_OUT = (MOTOR->PID_P.out.ERROR[YUN_D_NOW] * MOTOR->PID_P.IN.P);
    /*微分输出*/
    MOTOR->PID_P.out.D_OUT = (MOTOR->PID_P.out.ERROR[YUN_D_NOW] - MOTOR->PID_P.out.ERROR[YUN_D_LAST]) * MOTOR->PID_P.IN.D;
    /*积分输出*/
    MOTOR->PID_P.out.I_OUT += (MOTOR->PID_P.out.ERROR[YUN_D_NOW] * MOTOR->PID_P.IN.I);
    /*积分限幅*/
    MOTOR->PID_P.out.I_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_P.IN.I_LIT, -MOTOR->PID_P.IN.I_LIT, MOTOR->PID_P.out.I_OUT);

//    printf("KP: OUT: %f",MOTOR->PID_P.out.P_OUT);
//    printf("AIM: %.2f ANGLE: %.2f\n",MOTOR->DATA.AIM,TOP_ANGLE);

    /*数据迭代*/
    MOTOR->PID_P.out.ERROR[YUN_D_LAST] = MOTOR->PID_P.out.ERROR[YUN_D_NOW];
    /*速度环总输出*/
    MOTOR->PID_P.out.ALL_OUT = (MOTOR->PID_P.out.P_OUT + MOTOR->PID_P.out.I_OUT);
    /*总输出限幅*/
    MOTOR->PID_P.out.ALL_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_P.IN.ALL_LIT, -MOTOR->PID_P.IN.ALL_LIT, MOTOR->PID_P.out.ALL_OUT);

    MOTOR->PID_S.out.ERROR[YUN_D_NOW] = MOTOR->PID_P.out.ALL_OUT - TOP_SPEED; // 记得改哈
    /*比例输出*/
    MOTOR->PID_S.out.P_OUT = (MOTOR->PID_S.out.ERROR[YUN_D_NOW] * MOTOR->PID_S.IN.P);
    /*微分输出*/
    MOTOR->PID_S.out.D_OUT = (MOTOR->PID_S.out.ERROR[YUN_D_NOW] - MOTOR->PID_S.out.ERROR[YUN_D_LAST]) * MOTOR->PID_S.IN.D;
    /*积分输出*/
    MOTOR->PID_S.out.I_OUT += (MOTOR->PID_S.out.ERROR[YUN_D_NOW] * MOTOR->PID_S.IN.I);
    MOTOR->PID_S.out.I_OUT += MOTOR->PID_S.out.D_OUT;
    /*积分限幅*/
    MOTOR->PID_S.out.I_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_S.IN.I_LIT, -MOTOR->PID_S.IN.I_LIT, MOTOR->PID_S.out.I_OUT);
    /*数据迭代*/
    MOTOR->PID_S.out.ERROR[YUN_D_LAST] = MOTOR->PID_S.out.ERROR[YUN_D_NOW];
    /*速度环总输出*/
    MOTOR->PID_S.out.ALL_OUT = (MOTOR->PID_S.out.P_OUT + MOTOR->PID_S.out.I_OUT);
    /*总输出限幅*/
    MOTOR->PID_S.out.ALL_OUT = YUN_D_MATH_LIMIT(MOTOR->PID_S.IN.ALL_LIT, -MOTOR->PID_S.IN.ALL_LIT, MOTOR->PID_S.out.ALL_OUT);
}

void YUN_F_PID_INIT(struct YUN_MOTOR_PID_Typedef *PID,const float SET[5],float i_limit,float all_limit)//SET:KP,KI,KD,I_LIMIT,ALL_LIMIT
{
    PID->IN.P = SET[1];
    PID->IN.I = SET[2];
    PID->IN.D = SET[3];
    PID->IN.I_LIT = SET[4];
    PID->IN.ALL_LIT = SET[5];
//    PID->out.ERROR = 0;
}