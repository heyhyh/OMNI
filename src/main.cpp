#include <iostream>
#include "thread"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include <sys/select.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <cstdint>

#include "MOTOR.h"
#include "PID.h"
#include "can.h"


void YUN_F_THREAD_01(void)
{
    YUN_F_CAN_INIT();
    YUN_F_CAN_RECEIVE(&MOTOR6020,&TEST,YUN_D_CAN_1);
    YUN_F_CAN_SEND(YUN_D_CAN_1, 0X1FF,1000,0,0,0);
}

int main() {
    while(1)
    {
        std::thread t1(YUN_F_THREAD_01);
        t1.join();
    }

}