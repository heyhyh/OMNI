//
// Created by 86189 on 2024/1/24.
//






#ifndef DEMO_DEFINE_H
#define DEMO_DEFINE_H

#define YUN_D_UART_PATH "../../config.ini"


/*****************************遥控模式**********************************/
//手动
#define RUI_D_MOD_MANUAL      1
//视觉
#define RUI_D_MOD_VISION      2
//不跟随
#define RUI_D_MOD_FOLLOW_NO   3
//跟随
#define RUI_D_MOD_FOLLOW      4
//键鼠
#define RUI_D_MOD_KEYBOARD    6
/*****************************遥控模式**********************************/
//需要离线检测的设备数量
#define YUN_D_STATUS_NUM               11
//离线检测设备的ID序号
#define YUN_D_STATUS_ID_CHASSIS_MOTOR_1 0
#define YUN_D_STATUS_ID_CHASSIS_MOTOR_2 1
#define YUN_D_STATUS_ID_CHASSIS_MOTOR_3 2
#define YUN_D_STATUS_ID_CHASSIS_MOTOR_4 3
#define YUN_D_STATUS_ID_GIMBAL_PIT     4
#define YUN_D_STATUS_ID_GIMBAL_YAW     5
#define YUN_D_STATUS_ID_ATTACK_L       6
#define YUN_D_STATUS_ID_ATTACK_R       7
#define YUN_D_STATUS_ID_ATTACK_G       8
#define YUN_D_STATUS_ID_TOP            9
#define YUN_D_STATUS_ID_DBUS           10
//设备状态
#define YUN_D_STATUS_ON                1
#define YUN_D_STATUS_OFF               2
#define YUN_D_STATUS_OFF_ON            3
#define YUN_D_STATUS_ON_OFF            4
//电机离线检测时间
#define YUN_D_STATUS_JUDGE_TIME_MOTOR  200
//陀螺仪离线检测时间
#define YUN_D_STATUS_JUDGE_TIME_TOP 15

#define YUN_D_NOW                1
#define YUN_D_LAST               0

#define YUN_D_ERROR              false
#define YUN_D_READY              true

/*****************************电机数组**********************************/
//数量
#define YUN_D_MOTOR_NUMBER        10
//电机序号
//底盘电机
#define YUN_D_MOTOR_CHASSIS_1      0
#define YUN_D_MOTOR_CHASSIS_2      1
#define YUN_D_MOTOR_CHASSIS_3      2
#define YUN_D_MOTOR_CHASSIS_4      3
//云台电机
//#define YUN_D_MOTOR_GIMBAL_YAW    4
#define YUN_D_MOTOR_GIMBAL_YAW    0
//#define YUN_D_MOTOR_GIMBAL_PIT    3
#define YUN_D_MOTOR_GIMBAL_PIT    1

#define YUN_D_MOTOR_ATTACK_L      1
#define YUN_D_MOTOR_ATTACK_R      0
#define YUN_D_MOTOR_ATTACK_G      2
//电机类型
#define YUN_D_MOTOR_TYPE_3508     1
#define YUH_D_MOTOR_TYPE_3510     2
#define YUN_D_MOTOR_TYPE_6020     3
#define YUN_D_MOTOR_TYPE_2006     4

//日志打印
#ifdef YUN_BUILD_RELEASE
#define YUN_D_YUN_BUILD_TYPE "YUN_RELEASE"
#endif

#ifdef YUN_BUILD_STATIC
#define YUN_D_YUN_BUILD_TYPE "YUN_STATIC"
#endif
#define YUN_D_LOG_NOTICE(format, ...) printf("\033[0;32m[%s] - %s  " format "\033[0m\n", YUN_D_YUN_BUILD_TYPE, &__func__[6], ##__VA_ARGS__);
#define YUN_D_LOG_ERROR(format, ...) printf("\033[0;31m[%s] - %s  " format "\033[0m\n", YUN_D_YUN_BUILD_TYPE, &__func__[6], ##__VA_ARGS__);
#define YUN_D_LOG_WARN(format, ...)  printf("\033[0;33m[%s] - %s  " format "\033[0m\n" ,YUN_D_YUN_BUILD_TYPE, &__func__[6], ##__VA_ARGS__);
//#define YUN_D_LOG_INFO(format, ...)  printf("\033[0;34m[%s] - %s  " format "\033[0m\n",  YUN_D_YUN_BUILD_TYPE,&__func__[6], ##__VA_ARGS__);

//#define YUN_D_LOG_INFO("format") printf("format\n");

#endif //DEMO_DEFINE_H

#ifdef YUN_BUILD_DEBUG
extern time_t YUN_V_T;
extern struct tm YUN_V_TM;
extern clock_t YUN_V_START_TIME;
#define YUN_D_LOG_NOTICE(format, ...) \
                YUN_V_T = time(NULL);YUN_V_TM = *localtime(&YUN_V_T) ;\
                printf("\033[0;32m[YUN_DEBUG %ld ms %02d:%02d] - %s  " format "\033[0m\n",  (clock() - YUN_V_START_TIME)/ 1000, YUN_V_TM.tm_hour, YUN_V_TM.tm_min, &__func__[6], ##__VA_ARGS__);
#define YUN_D_LOG_ERROR(format, ...) \
                YUN_V_T = time(NULL);YUN_V_TM = *localtime(&YUN_V_T) ;\
                printf("\033[0;31m[YUN_DEBUG %ld ms %02d:%02d] - %s  " format "\033[0m\n", (clock() - YUN_V_START_TIME)/ 1000, YUN_V_TM.tm_hour, YUN_V_TM.tm_min, &__func__[6], ##__VA_ARGS__);
#define YUN_D_LOG_WARN(format, ...) \
                YUN_V_T = time(NULL);YUN_V_TM = *localtime(&YUN_V_T) ;\
                printf("\033[0;33m[YUN_DEBUG %ld ms %02d:%02d] - %s  " format "\033[0m\n" , (clock() - YUN_V_START_TIME)/ 1000, YUN_V_TM.tm_hour, YUN_V_TM.tm_min, &__func__[6], ##__VA_ARGS__);
#define RUI_D_LOG_INFO(format, ...)  \
                YUN_V_T = time(NULL);YUN_V_TM = *localtime(&YUN_V_T) ;\
                printf("\033[0;34m[YUN_DEBUG %ld ms %02d:%02d] - %s  " format "\033[0m\n", (clock() - YUN_V_START_TIME)/ 1000, YUN_V_TM.tm_hour, YUN_V_TM.tm_min, &__func__[6], ##__VA_ARGS__);

/*****************************离线检测**********************************/

#define RUI_D_NOW                1
#define RUI_D_LAST               0

#define RUI_D_ERROR              false
#define RUI_D_READY              true


#endif


/******************************CAN_ID********************************/
#define YUN_D_CAN_1 0
#define YUN_D_CAN_2 1

//底盘
#define YUN_D_CAN_ID_CHASSIS_1    0x201
#define YUN_D_CAN_ID_CHASSIS_2    0x202
#define YUN_D_CAN_ID_CHASSIS_3    0x203
#define YUN_D_CAN_ID_CHASSIS_4    0x204
//电容
#define YUN_D_CAN_ID_CAP          0x206
//陀螺仪
#define YUN_D_CAN_ID_TOP         0x101
//云台
#define YUN_D_CAN_ID_YAW         0x20B
#define YUN_D_CAN_ID_PIT         0x209
//发射
#define YUN_D_CAN_ID_ATTACK_L    0x203
#define YUN_D_CAN_ID_ATTACK_R    0x204
//#define YUN_D_CAN_ID_ATTACK_G    0x205
/******************************CAN_ID********************************/

//????????????????????????????VOFA NAME???????????????????????????/
#define YUN_D_VOFA_C1 0
#define YUN_D_VOFA_C2 1
#define YUN_D_VOFA_C3 2
#define YUN_D_VOFA_C4 3

#define YUN_D_VOFA_GY 5
#define YUN_D_VOFA_GP 6
