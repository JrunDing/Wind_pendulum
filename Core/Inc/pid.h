#ifndef __PID_H
#define __PID_H

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
}PID_parameter;//定义结构体









#endif



