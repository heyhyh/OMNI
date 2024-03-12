//
// Created by 86189 on 2024/3/7.
//

#ifndef DEMO_TOP_H
#define DEMO_TOP_H
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdbool>

#include "define.h"
#include "ROOT_INIT.h"
typedef struct _YUN_TYPEDEF_TOP
{
   float REALITY_ANGLE;            //真实角度//带圈数
   int16_t YAW_ANGLE[2];
   float YAW_ANGLE_F;
   int16_t YAW_SPEED[2];
   int16_t PIT_ANGLE[2];
   float PIT_ANGLE_F;
   int16_t PIT_SPEED[2];
   int16_t ROUND;

} YUN_TYPEDEF_TOP;
 _YUN_TYPEDEF_TOP TEST;

union YUN_TYPEDEF_TOP_DATA_UNION                            //共用体(用于接受各种数据)(视觉，陀螺仪)
{
    struct
    {
        int16_t YAW_ANGLE;
        int16_t PIT_ANGLE;
        int16_t YAW_SPEED;
        int16_t PIT_SPEED;
    };
    uint8_t GET_DATA[8];
};
#endif //DEMO_TOP_H
