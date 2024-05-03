//
// Created by 86189 on 2024/1/30.
//

#ifndef DEMO_PID_H
#define DEMO_PID_H

void YUN_F_MOTOR_PID_SC(YUN_TYPEDEF_MOTOR *MOTOR);
void YUN_F_MOTOR_PID_GIMBAL(YUN_TYPEDEF_MOTOR *MOTOR, float TOP_ANGLE, float TOP_SPEED);
void YUN_F_PID_INIT(YUN_MOTOR_PID_Typedef *PID,const float *SET,float i_limit,float all_limit);
#endif //DEMO_PID_H
