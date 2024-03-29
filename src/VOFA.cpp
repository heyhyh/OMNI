//
// Created by 86189 on 2024/3/21.
//
#include<iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <ifaddrs.h>
#include <unordered_map>

#include "VOFA.h"
void YUN_F_VOFA_PARSE(YUN_TYPEDEF_RECV_UNION *RECV)
{
    std::string ITER = RECV->ALL;
    auto POS = ITER.find(':');
    auto NAME_RAW = ITER.substr(0,POS);
    auto VALUE_RAW = ITER.substr(POS+1);
    auto PARAM = std::stof(VALUE_RAW);

    strcpy(RECV->DATA.NAME,NAME_RAW.c_str());
    RECV->DATA.PARAM = PARAM;

}



void YU_F_VOFA_DEBUG_CAL(YU_TYPEDEF_DEBUG *DEBUG, YUN_TYPEDEF_MOTOR *MOTOR)
{
    DEBUG->MOTOR_DATA.AIM = MOTOR->DATA.AIM;
    DEBUG->MOTOR_DATA.ANGLE = MOTOR->DATA.ANGLE_NOW;
    DEBUG->MOTOR_DATA.LAPS = MOTOR->DATA.LAPS;
    DEBUG->MOTOR_DATA.CURRENT = MOTOR->DATA.CURRENT;
    DEBUG->MOTOR_DATA.SPEED = MOTOR->DATA.SPEED_NOW;

    DEBUG->PID_S.out.ERROR[YUN_D_NOW] = MOTOR->PID_S.out.ERROR[YUN_D_NOW];
    DEBUG->PID_S.out.ERROR[YUN_D_LAST] = MOTOR->PID_S.out.ERROR[YUN_D_LAST];
    DEBUG->PID_S.out.P_OUT = MOTOR->PID_S.out.P_OUT;
    DEBUG->PID_S.out.I_OUT = MOTOR->PID_S.out.I_OUT;
    DEBUG->PID_S.out.D_OUT = MOTOR->PID_S.out.D_OUT;
    DEBUG->PID_S.out.ALL_OUT = MOTOR->PID_S.out.ALL_OUT;
    DEBUG->PID_S.IN.P = MOTOR->PID_S.IN.P;
    DEBUG->PID_S.IN.I = MOTOR->PID_S.IN.I;
    DEBUG->PID_S.IN.D = MOTOR->PID_S.IN.D;
    DEBUG->PID_S.IN.I_LIT = MOTOR->PID_S.IN.I_LIT;
    DEBUG->PID_S.IN.ALL_LIT = MOTOR->PID_S.IN.ALL_LIT;

    DEBUG->PID_A.out.ERROR[YUN_D_NOW] = MOTOR->PID_P.out.ERROR[YUN_D_NOW];
    DEBUG->PID_A.out.ERROR[YUN_D_LAST] = MOTOR->PID_P.out.ERROR[YUN_D_LAST];
    DEBUG->PID_A.out.P_OUT = MOTOR->PID_P.out.P_OUT;
    DEBUG->PID_A.out.I_OUT = MOTOR->PID_P.out.I_OUT;
    DEBUG->PID_A.out.D_OUT = MOTOR->PID_P.out.D_OUT;
    DEBUG->PID_A.out.ALL_OUT = MOTOR->PID_P.out.ALL_OUT;
    DEBUG->PID_A.IN.P = MOTOR->PID_P.IN.P;
    DEBUG->PID_A.IN.I = MOTOR->PID_P.IN.I;
    DEBUG->PID_A.IN.D = MOTOR->PID_P.IN.D;
    DEBUG->PID_A.IN.I_LIT = MOTOR->PID_P.IN.I_LIT;
    DEBUG->PID_A.IN.ALL_LIT = MOTOR->PID_P.IN.ALL_LIT;

    DEBUG->PID_C.out.ERROR[YUN_D_NOW] = MOTOR->PID_C.out.ERROR[YUN_D_NOW];
    DEBUG->PID_C.out.ERROR[YUN_D_LAST] = MOTOR->PID_C.out.ERROR[YUN_D_LAST];
    DEBUG->PID_C.out.P_OUT = MOTOR->PID_C.out.P_OUT;
    DEBUG->PID_C.out.I_OUT = MOTOR->PID_C.out.I_OUT;
    DEBUG->PID_C.out.D_OUT = MOTOR->PID_C.out.D_OUT;
    DEBUG->PID_C.out.ALL_OUT = MOTOR->PID_C.out.ALL_OUT;
    DEBUG->PID_C.IN.P = MOTOR->PID_C.IN.P;
    DEBUG->PID_C.IN.I = MOTOR->PID_C.IN.I;
    DEBUG->PID_C.IN.D = MOTOR->PID_C.IN.D;
    DEBUG->PID_C.IN.I_LIT = MOTOR->PID_C.IN.I_LIT;
    DEBUG->PID_C.IN.ALL_LIT = MOTOR->PID_C.IN.ALL_LIT;

}

void YUN_F_VOFA_ASSIGN(YUN_TYPEDEF_RECV_UNION *RECV)
{
    std::string OUTLINE = RECV->DATA.NAME;
    auto POS_1 = OUTLINE.find('_');
    auto HEAD = OUTLINE.substr(0,POS_1);
    auto TAIL = OUTLINE.substr(POS_1+1);

    static const std::unordered_map<std::string,int>MOTOR_MAP{
            {"C1",YUN_D_VOFA_C1 }

    };
}



void YUN_F_VOFA_DEBUG()
{
    switch (MOTOR_TYPE) {
        
    }
}

[[noreturn]] void YUN_F_THREAD_VOFA()
{
    YUN_TYPEDEF_SEND_UNION YUN_U_SEND;
    YUN_TYPEDEF_RECV_UNION YUN_U_RECV;
    YUN_U_SEND.DATA.TAIL[2] = 0x80;
    YUN_U_SEND.DATA.TAIL[3] = 0x7f;

    struct sockaddr_in YUN_U_SERVER_ADDR { }, YUN_U_CLIENT_ADDR{ };
    socklen_t YUN_U_CLIENT_ADDR_LEN = sizeof (YUN_U_CLIENT_ADDR);
    struct  ifaddrs *IFADDRS;
    char IPSTR[INET_ADDRSTRLEN];

    int YUN_U_SOCKET_FD = socket(AF_INET,SOCK_DGRAM,0);
    if(YUN_U_SOCKET_FD == -1)
    {
        printf("SOCKET FD ERROR\n");
        exit(1);
    }

    //设置非阻塞模式
    int FLAG = fcntl(YUN_U_SOCKET_FD,F_GETFL,0);
    if(fcntl(YUN_U_SOCKET_FD,F_SETFL,FLAG |O_NONBLOCK) == -1)
    {
        perror("设置非阻塞失败\n");
        exit(1);
    }

    memset(&YUN_U_SERVER_ADDR,0,sizeof (YUN_U_SERVER_ADDR));
    YUN_U_SERVER_ADDR.sin_family = AF_INET;//地址族设置为IPV4
    YUN_U_SERVER_ADDR.sin_port = htons(12345);//设置端口号（htons把主机字节序转换成网络字节序// ）
    YUN_U_SERVER_ADDR.sin_addr.s_addr = htonl(INADDR_ANY);//接收任何连接
    if (bind(YUN_U_SOCKET_FD,(sockaddr*)&YUN_U_SERVER_ADDR,(socklen_t)sizeof (YUN_U_SERVER_ADDR))<0)
    {
        perror("绑定失败\n");
        close(YUN_U_SOCKET_FD);
        exit(1);
    }
    if (getifaddrs(&IFADDRS) == -1)
    {
        perror("ip地址获取失败\n");
        exit(1);
    }

    struct ifaddrs * ifa;
    for (ifa = IFADDRS;ifa != nullptr;ifa = ifa->ifa_next )
    {
        if (ifa->ifa_addr == nullptr || ifa->ifa_addr->sa_family != AF_INET)
            continue;
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            auto *IPV4 = (struct sockaddr_in *)ifa->ifa_addr;
            inet_ntop(AF_INET, &IPV4->sin_addr, IPSTR, (socklen_t)sizeof (IPSTR));
            printf("Interface: %s\t Address: %s\n", ifa->ifa_name, IPSTR);
        }
    }


    while (true)
    {
        YUN_F_VOFA_DEBUG();

        if (recvfrom(YUN_U_SOCKET_FD,&YUN_U_RECV,sizeof (YUN_U_RECV.ALL),0,(struct sockaddr *)&YUN_U_CLIENT_ADDR,&YUN_U_CLIENT_ADDR_LEN)>0)
        {
            char CLIENT_IP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET,&YUN_U_CLIENT_ADDR.sin_addr,CLIENT_IP,INET_ADDRSTRLEN);

            YUN_F_VOFA_PARSE(&YUN_U_RECV);//解析收到的数据

            YUN_F_VOFA_ASSIGN(&YUN_U_RECV);


        }
        memcpy(&YUN_U_SEND.DATA.YUN_V_MOTOR_DEBUG,sizeof (YUN_V_DEBUG[MOTOR_TYPE]));
        if (sendto(YUN_U_SOCKET_FD,&YUN_U_SEND,sizeof (YUN_U_SEND.ALL),0,(struct sockaddr *)&YUN_U_CLIENT_ADDR,YUN_U_CLIENT_ADDR_LEN) > 0)
        {

        }
        usleep(1);
    }


}

