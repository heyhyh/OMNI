//
// Created by 86189 on 2024/3/18.
//
#include "CHASSIS.h"
#include "UART.h"
#include "MATH.h"
Chassis_typedef Chassis_Data;
Mecanum_typdef MecanumData;

void MecanumInit(void)
{
    MecanumData.Wheel_Perimeter = 478;
    MecanumData.Wheel_Track = 365;
    MecanumData.Wheel_Base = 305;
    MecanumData.Rotate_x_offset = 0;
    MecanumData.Rotate_y_offset = 0;
    MecanumData.Deceleration_ratio = 1.0f / 19.0f;
    MecanumData.Max_vx_speed = 5000;
    MecanumData.Max_vy_speed = 5000;
    MecanumData.Max_vr_speed = 90;
    MecanumData.Max_wheel_ramp = 500;

    //计算旋转比率
    MecanumData.raid_fr = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
                           - MecanumData.Rotate_x_offset + MecanumData.Rotate_y_offset) / radian_angle;

    MecanumData.raid_fl = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
                           - MecanumData.Rotate_x_offset - MecanumData.Rotate_y_offset) / radian_angle;

    MecanumData.raid_bl = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
                           + MecanumData.Rotate_x_offset - MecanumData.Rotate_y_offset) / radian_angle;

    MecanumData.raid_br = ((MecanumData.Wheel_Track + MecanumData.Wheel_Base) / 2.0f
                           + MecanumData.Rotate_x_offset + MecanumData.Rotate_y_offset) / radian_angle;

    //将数据转化到转每分钟 60/(减速比*周长)
    MecanumData.Wheel_rpm_ratio = 60.0f / (MecanumData.Wheel_Perimeter * MecanumData.Deceleration_ratio);
}

//麦轮解算
void YUN_F_CHASSIS_MECANUM(TYPEDEF_DBUS_ *DBUS)
{
    float tempMax = 0;//寻找输出的最大值
    float AngleSin = 0;
    float AngleCos = 0;
    float  remote[4] = {0};
    remote[0] = (float )DBUS->REMOTE.CH0_int16;
    remote[1] = (float )DBUS->REMOTE.CH1_int16;
    remote[2] = -(float )DBUS->REMOTE.CH2_int16;
    remote[3] = (float )DBUS->REMOTE.CH3_int16;
//死区
    if(YUN_D_MATH_ABS(remote[0])<20)
    {
        remote[0] = 0;
    }
    if (YUN_D_MATH_ABS(remote[1])<20)
    {
        remote[1] = 0;
    }
    if (YUN_D_MATH_ABS(remote[2])<20)
    {
        remote[2] = 0;
    }
    if (YUN_D_MATH_ABS(remote[3])<20)
    {
        remote[3] = 0;
    }
    remote[0] = YUN_D_MATH_LIMIT(MecanumData.Max_vx_speed, -MecanumData.Max_vx_speed, remote[0]);
    remote[1] = YUN_D_MATH_LIMIT(MecanumData.Max_vy_speed, -MecanumData.Max_vy_speed, remote[1]);
    remote[2] = YUN_D_MATH_LIMIT(MecanumData.Max_vr_speed, -MecanumData.Max_vr_speed, remote[2]);

// 寻找输出最大值
    MecanumData.MecanumOut[0] = ( remote[1] + remote[0] - remote[2] * MecanumData.raid_fl) * MecanumData.Wheel_rpm_ratio;
    MecanumData.MecanumOut[1] = (-remote[1] + remote[0] - remote[2] * MecanumData.raid_fr) * MecanumData.Wheel_rpm_ratio;
    MecanumData.MecanumOut[2] = (-remote[1] - remote[0] - remote[2] * MecanumData.raid_br) * MecanumData.Wheel_rpm_ratio;
    MecanumData.MecanumOut[3] = ( remote[1] - remote[0] - remote[2] * MecanumData.raid_bl) * MecanumData.Wheel_rpm_ratio;
    for (uint8_t i = 0; i < 4; i++)
    {
        if (YUN_D_MATH_ABS(MecanumData.MecanumOut[i]) >= tempMax)
        {
            tempMax = YUN_D_MATH_ABS(MecanumData.MecanumOut[i]);
        }
    }
    // 如果输出超过最大值，对四个轮子进行等比例降速
    if (tempMax > MecanumData.Max_wheel_ramp)
    {
        float rate = MecanumData.Max_wheel_ramp / tempMax;
        for (uint8_t i = 0; i < 4; i++)
        {
            MecanumData.MecanumOut[i] *= rate;
        }
    }
}

void GetMecanumOut(float *AIM)
{
    for (uint8_t i = 0; i < 4; i++)
    {
        AIM[i]=MecanumData.MecanumOut[i];
    }
}
