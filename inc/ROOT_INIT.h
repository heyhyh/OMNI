//
// Created by 86189 on 2024/1/24.
//

#ifndef DEMO_ROOT_INIT_H
#define DEMO_ROOT_INIT_H

#include <csignal>
#include<cstdint>

#include "define.h"

struct YUN_MONITOR_Typedef
{
    int8_t STATUS[2][YUN_D_STATUS_NUM];
    uint16_t  TIME[YUN_D_STATUS_NUM];
};
extern struct YUN_MONITOR_Typedef YUN_V_MONITOR;
#endif //DEMO_ROOT_INIT_H
