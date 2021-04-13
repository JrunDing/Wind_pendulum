#ifndef __PID_H
#define __PID_H
#include "main.h"

typedef struct PID_parameter
{
    float Sv;//Ŀ��ֵ
    float Pv;//��ǰֵ
    float Kp,Ki,Kd;//Kp,Ki,Kd
    float Bias;//��ǰƫ��
    float Last_bias;//�ϴ�ƫ��
    float Last_last_bias;//���ϴ�ƫ��
    float Bias_sum;//ƫ���
    float Output;//���
	  float Intergral;//����ֵ
	  float Intergral_max;//�������ֵ,���ڿ����ֱ���
	  float Output_max;//������ֵ,�����޷�
}PID_parameter;//����ṹ��
float Position_Pid(PID_parameter* PID,float Current,float Target);
void Cap(PID_parameter* PID_X,PID_parameter* PID_Y);
void Execute(void);
void AntiWindup(PID_parameter* PID);
#endif



