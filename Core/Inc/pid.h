#ifndef __PID_H
#define __PID_H
#include "main.h"

typedef struct PID_parameter
{
    float Sv;//目标值
    float Pv;//当前值
    float Kp,Ki,Kd;//Kp,Ki,Kd
    float Bias;//当前偏差
    float Last_bias;//上次偏差
    float Last_last_bias;//上上次偏差
    float Bias_sum;//偏差和
    float Output;//输出
	  float Intergral;//积分值
	  float Intergral_max;//积分最大值,用于抗积分饱和
	  float Output_max;//最大输出值,用于限幅
}PID_parameter;//定义结构体
float Position_Pid(PID_parameter* PID,float Current,float Target);
void Cap(PID_parameter* PID_X,PID_parameter* PID_Y);
void Execute(void);
void AntiWindup(PID_parameter* PID);
#endif



