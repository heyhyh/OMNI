//
// Created by 86189 on 2024/3/15.
//

#ifndef DEMO_CHASSIS_H
#define DEMO_CHASSIS_H
#include "MOTOR.h"
#include "UART.h"
//限速
//限制最大值
#define LimitMax(input, max)       \
    {                              \
        if (input > max) {         \
            input = max;           \
        } else if (input < -max) { \
            input = -max;          \
        }                          \
    }

#define radian_angle 57.3f //弧度角度转化系数（180/Pi）（角度/弧度）

typedef struct
{
    float Chassis_Vx;
    float Chassis_Vy;
    float Chassis_Vr;
} Chassis_typedef;

typedef struct
{
    float Wheel_Perimeter;    /* 轮的周长（mm）*/
    float Wheel_Track;        /* 轮距（mm）*/
    float Wheel_Base;         /*轴距（mm）*/
    float Rotate_x_offset;    /* 相对于底盘中心的x轴旋转偏移量(mm) */
    float Rotate_y_offset;    /* 相对于底盘中心的y轴旋转偏移量(mm) */
    float Deceleration_ratio; /*电机减速比*/
    int Max_vx_speed;         /*底盘的x轴的最大速度(mm/s)*/
    int Max_vy_speed;         /*底盘的y轴的最大速度(mm/s)*/
    int Max_vr_speed;         /*底盘的自转的最大速度(degree/s)*/
    int Max_wheel_ramp;       /*3508最大转速*/
    // 每一个轮子的旋转比率//与旋转中心点相关
    float raid_fr;         // 右前
    float raid_fl;         // 左前
    float raid_bl;         // 左后
    float raid_br;         // 右后
    float Wheel_rpm_ratio; // 用来将速度转化成转每分钟

    float MecanumOut[4];   // 分配后的输出
} Mecanum_typdef;

extern int16_t RELATIVE_ANGLE;

void MecanumInit(void);
void YUN_F_CHASSIS_MECANUM(TYPEDEF_DBUS_ *DBUS);
void GetMecanumOut(float *target);

#endif //DEMO_CHASSIS_H
