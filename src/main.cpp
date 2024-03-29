#include <iostream>
#include <thread>
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
#include "main.h"
#include "UART.h"
#include "CHASSIS.h"


TYPEDEF_DBUS dbus_data{ };
YUN_TYPEDEF_MOTOR CHASSIS_DATA[4];
float AIM[4];
void YUN_F_THREAD_01(void)
{

    YUN_F_CAN_INIT();

    printf("INIT OK\n");
   // YUN_TYPEDEF_MOTOR MOTOR6020[10];
    MecanumInit();
    YUN_TYPEDEF_TOP TEST;
    while (true)
    {



        YUN_F_CHASSIS_MECANUM(&dbus_data);
        YUN_F_CAN_RECEIVE(CHASSIS_DATA,&TEST,YUN_D_CAN_1);
        //printf("ANGLE:  %d\n",MOTOR6020[4].DATA.ANGLE_NOW);
        CHASSIS_DATA[0].PID_S.IN.P = 5;
        CHASSIS_DATA[1].PID_S.IN.P = 5;
        CHASSIS_DATA[2].PID_S.IN.P = 5;
        CHASSIS_DATA[3].PID_S.IN.P = 5;
        CHASSIS_DATA[0].PID_S.IN.I = 0.1;

        GetMecanumOut(AIM);

//        printf("TARGET:  \nMOTOR1:  %f  MOTOR2:  %f  MOTOR3:  %f  MOTOR4:  %f",
//               AIM[0],AIM[1],AIM[2],AIM[3]);

        CHASSIS_DATA[0].DATA.AIM = AIM[0];
        CHASSIS_DATA[1].DATA.AIM = AIM[1];
        CHASSIS_DATA[2].DATA.AIM = AIM[2];
        CHASSIS_DATA[3].DATA.AIM = AIM[3];
        YUN_F_MOTOR_PID_SC(&CHASSIS_DATA[0]);
        YUN_F_MOTOR_PID_SC(&CHASSIS_DATA[1]);
        YUN_F_MOTOR_PID_SC(&CHASSIS_DATA[2]);
        YUN_F_MOTOR_PID_SC(&CHASSIS_DATA[3]);

        printf("TARGET:  MOTOR1:  %f  MOTOR2:  %f  MOTOR3:  %f  MOTOR4:  %f\n",
               CHASSIS_DATA[0].PID_S.out.ALL_OUT,CHASSIS_DATA[1].PID_S.out.ALL_OUT,
               CHASSIS_DATA[2].PID_S.out.ALL_OUT,CHASSIS_DATA[3].PID_S.out.ALL_OUT);

//        YUN_F_CAN_SEND(YUN_D_CAN_1, 0X200,CHASSIS_DATA[0].PID_S.out.ALL_OUT,CHASSIS_DATA[1].PID_S.out.ALL_OUT,CHASSIS_DATA[2].PID_S.out.ALL_OUT,CHASSIS_DATA[3].PID_S.out.ALL_OUT);

        usleep(1);
    }
}

void YUN_F_THREAD_02(void)
{

}

int main()
{
    std::thread t1(YUN_F_THREAD_01);
    std::thread t2(YUN_F_DBUS_THREAD, &dbus_data);
    t1.join();
    t2.join();
    return 0;

}