//
// Created by 86189 on 2024/2/2.
//
#include <sys/select.h>
#include <unistd.h>
#include <net/if.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>

#include "can.h"
#include "define.h"
#include "TOP.h"

struct can_frame frame[2];
int YUN_V_FD_CAN[2];//存储两个can口的文件描述符

//can口初始化
bool YUN_F_CAN_INIT()
{
    printf("CAN初始化\n");

    struct sockaddr_can ADDR[2];// 用于存储两个CAN接口的地址
    struct ifreq IFR[2];//用于存储两个CAN口的接口请求
    char *IFNAMES[2] =  {(char *) "can1",(char *)"can2"};

    //创建socket,并绑定can口
    if((YUN_V_FD_CAN[0] = socket(PF_CAN, SOCK_RAW,CAN_RAW)) > 0)
    {
        printf("成功创建socket_can1\n");
    }
    else
    {
        printf("错误创建socket_can1]\n");
        close(YUN_V_FD_CAN[0]);
        return YUN_D_ERROR;
    }
    strcpy(IFR[0].ifr_name, IFNAMES[0]);

    if(ioctl(YUN_V_FD_CAN[0],SIOCGIFINDEX, &IFR[0])<0)
    {
        printf("错误-获取CAN1接口索引\n");
        printf("警告-请检查CAN接口是否存在\n");
        printf("警告-程序即将退出\n");
//        close(YUN_V_FD_CAN[0]);
    }
    ADDR[0].can_family = AF_CAN;
    ADDR[0].can_ifindex = IFR[0].ifr_ifindex;
    if(bind(YUN_V_FD_CAN[0],(struct sockaddr*) &ADDR[0], (socklen_t )sizeof(ADDR[0])) == 0)
    {
    printf("成功-绑定CAN1套接字和地址\n");

    } else
    {
       printf("错误-绑定CAN1套接字和地址\n");
        close(YUN_V_FD_CAN[0]);
#ifdef YUN_BUILD_STATIC
        exit(-1);
#endif
    }

    if((YUN_V_FD_CAN[1] = socket(PF_CAN, SOCK_RAW, CAN_RAW)) > 0)
    {
        printf("成功-创建SOCKET_CAN2\n");
    }else
    {
        printf("错误-创建SOCKET_CAN2\n");
        close(YUN_V_FD_CAN[1]);
#ifdef YUN_BUILD_STATIC
        exit(-1);
#endif
    }
    strcpy(IFR[1].ifr_name,IFNAMES[1]);
    if (ioctl(YUN_V_FD_CAN[1], SIOCGIFINDEX,&IFR[1]) < 0)
    {
        printf("错误-获取CAN2接口索引\n");
        printf("警告-请检查CAN接口是否存在\n");
        printf("警告-程序即将退出\n");
        close(YUN_V_FD_CAN[1]);
#ifdef YUN_BUILD_STATIC
         exit(-1);
#endif
    }
    ADDR[1].can_family = AF_CAN;
    ADDR[1].can_ifindex = IFR[1].ifr_ifindex;
    if (bind(YUN_V_FD_CAN[1], (struct sockaddr *) &ADDR[1], sizeof(ADDR[1])) == 0)
    {
        printf("成功-绑定CAN2套接字和地址\n");

    }else
    {
        printf("错误-绑定CAN2套接字和地址\n");
        close(YUN_V_FD_CAN[1]);
#ifdef YUN_BUILD_STATIC
        exit(-1);
#endif
    }

    return  YUN_D_READY;

}



//CAN解算
static bool YUN_F_CAN_RECEIVE_SOLVE(YUN_TYPEDEF_MOTOR *MOTOR,YUN_TYPEDEF_TOP *YUN_V_TOP_DATA,uint8_t can, u_int32_t CAN_ID,uint8_t *CAN_DATA)
{
    if(can == YUN_D_CAN_2)
    {

        switch (CAN_ID)
        {
        case YUN_D_CAN_ID_YAW:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_GIMBAL_YAW], CAN_DATA, YUN_D_MOTOR_TYPE_6020, YUN_D_STATUS_ID_GIMBAL_YAW);
        break;
        case YUN_D_CAN_ID_PIT:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_GIMBAL_PIT], CAN_DATA, YUN_D_MOTOR_TYPE_6020, YUN_D_STATUS_ID_GIMBAL_PIT);
        break;
        case YUN_D_CAN_ID_ATTACK_L:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_ATTACK_L], CAN_DATA, YUN_D_MOTOR_TYPE_3508, YUN_D_STATUS_ID_ATTACK_L);
        break;
        case YUN_D_CAN_ID_ATTACK_R:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_ATTACK_R], CAN_DATA, YUN_D_MOTOR_TYPE_3508, YUN_D_STATUS_ID_ATTACK_R);
        break;
        case YUN_D_CAN_ID_ATTACK_G:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_ATTACK_G], CAN_DATA, YUN_D_MOTOR_TYPE_2006,YUN_D_STATUS_ID_ATTACK_G);
        break;
//        case YUN_D_CAN_ID_TOP:YUN_F_TOP_CAN_RX(YUN_V_TOP_DATA, CAN_DATA);
        break;
        default:break;
        }
    }
  else if (can == YUN_D_CAN_1)
    {
//        printf("123")  ;
      switch (CAN_ID)
        {

            case YUN_D_CAN_ID_CHASSIS_1:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_CHASSIS_1], CAN_DATA, YUN_D_MOTOR_TYPE_3508, YUN_D_STATUS_ID_CHASSIS_MOTOR_1);
                break;
            case YUN_D_CAN_ID_CHASSIS_2:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_CHASSIS_2], CAN_DATA, YUN_D_MOTOR_TYPE_3508, YUN_D_STATUS_ID_CHASSIS_MOTOR_2);
                break;
            case YUN_D_CAN_ID_CHASSIS_3:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_CHASSIS_3], CAN_DATA, YUN_D_MOTOR_TYPE_3508, YUN_D_STATUS_ID_CHASSIS_MOTOR_3);
                break;
            case YUN_D_CAN_ID_CHASSIS_4:YUN_F_MOTOR_CAN_RX(&MOTOR[YUN_D_MOTOR_CHASSIS_4], CAN_DATA, YUN_D_MOTOR_TYPE_3508, YUN_D_STATUS_ID_CHASSIS_MOTOR_4);
                break;
                //case YUN_D_CAN_ID_TOP:YUN_F_TOP_CAN_RX(YUN_V_TOP_DATA, CAN_DATA);
                //break;
        }


    }
return  YUN_D_READY;
}


//CAN接收
bool YUN_F_CAN_RECEIVE(YUN_TYPEDEF_MOTOR *MOTOR,YUN_TYPEDEF_TOP *YUN_V_TOP_DATA,uint8_t can)
{

    ssize_t  DATA_FLAG;
    fd_set YUN_READ_FDS;
    struct timeval YUN_CAN_TIMEOUT{ };


    FD_ZERO(&YUN_READ_FDS);
    FD_SET(YUN_V_FD_CAN[can],&YUN_READ_FDS);
//    printf("%d\n",can);

    YUN_CAN_TIMEOUT.tv_sec = 1;
    YUN_CAN_TIMEOUT.tv_usec = 0;

    int SELECT_RESULT = select(YUN_V_FD_CAN[can] + 1,&YUN_READ_FDS, nullptr, nullptr,&YUN_CAN_TIMEOUT);

    if(SELECT_RESULT > 0)
    {
        //收到数据
        DATA_FLAG = read(YUN_V_FD_CAN[can],&frame[can],sizeof (struct can_frame));
        if(DATA_FLAG > 0)
        {
            YUN_F_CAN_RECEIVE_SOLVE(MOTOR,YUN_V_TOP_DATA,can,frame[can].can_id,frame[can].data);
//            printf("0:%x 1:%x\n",frame[can].data[0],frame[can].data[1]);
            return YUN_D_READY;
        }else
        {
            return YUN_D_ERROR;
        }
    }
    return true;
}



//CAN发送
bool YUN_F_CAN_SEND(uint8_t can, u_int32_t can_id,int16_t num1,int16_t num2,int16_t num3,int16_t num4)
{
    struct  can_frame CAN_FRAME{ };

    CAN_FRAME.can_id = can_id;
    CAN_FRAME.can_dlc = 0x08;

    CAN_FRAME.data[0] = ((num1) >> 8);
    CAN_FRAME.data[1] = (num1);
    CAN_FRAME.data[2] = ((num2) >> 8);
    CAN_FRAME.data[3] = (num2);
    CAN_FRAME.data[4] = ((num3) >> 8);
    CAN_FRAME.data[5] = (num3);
    CAN_FRAME.data[6] = ((num4) >> 8);
    CAN_FRAME.data[7] = (num4);

    fd_set YUN_WRITE_FDS;
    FD_ZERO(&YUN_WRITE_FDS);
    FD_SET(YUN_V_FD_CAN[can],&YUN_WRITE_FDS);
    struct timeval YUN_CAN_TIMEOUT{ };
    YUN_CAN_TIMEOUT.tv_sec = 1;
    YUN_CAN_TIMEOUT.tv_usec = 0;

//    //等待CAN_FD[can]可写
    int RET = select(YUN_V_FD_CAN[can] + 1, nullptr,&YUN_WRITE_FDS, nullptr,&YUN_CAN_TIMEOUT);

    if(RET > 0)
    {
//        perror("select error!\n");
        if(write(YUN_V_FD_CAN[can], &CAN_FRAME, sizeof (struct can_frame)) > 0)
//        exit(0);
//        sleep(2);
        {
            return YUN_D_READY;
        }
    }else
        //CAN_FD[can]可写，执行写操作
    {
        printf("CAN ERROR");
        return YUN_D_ERROR;
    }

//    write(YUN_V_FD_CAN[can], &CAN_FRAME, sizeof (struct can_frame));
//    ssize_t number = write(YUN_V_FD_CAN[can], &CAN_FRAME, sizeof (CAN_FRAME));

    return true;
}

//电机结构体
//void YUN_F_CAN_SEND_MOTOR(YUN_TYPEDEF_MOTOR *MOTOR,int MOD)
//{
 //   void *(SEND_CHOSE[2])(YUN_TYPEDEF_MOTOR *) = {
 //           YUN_F_CAN_SEND_MOTOR_CHASSIS,
  //          YUN_F_CAN_SEND_MOTOR_GIMBAL,
  //  };
 //   SEND_CHOSE[MOD](MOTOR);
//}