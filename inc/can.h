//
// Created by 86189 on 2024/2/2.
//

#ifndef DEMO_CAN_H
#define DEMO_CAN_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include"MOTOR.h"
#include"define.h"
#include "TOP.h"
//#include""

typedef void *YUN_TYPEDEF_CHOSE_TYPEDEF[9];

bool YUN_F_CAN_INIT();

static bool YUN_F_CAN_RECEIVE_SOLVE(YUN_TYPEDEF_MOTOR *MOTOR,YUN_TYPEDEF_TOP *YUN_V_TOP_DATA,uint8_t can, u_int32_t CAN_ID,uint8_t *CAN_DATA);
bool YUN_F_CAN_RECEIVE(YUN_TYPEDEF_MOTOR *MOTOR,YUN_TYPEDEF_TOP *YUN_V_TOP_DATA,uint8_t can);
static bool YUN_F_CAN_SEND(uint8_t can, u_int32_t can_id,int16_t num1,int16_t num2,int16_t num3,int16_t num4);


#endif
