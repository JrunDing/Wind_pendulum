#ifndef __PID_H
#define __PID_H

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
}PID_parameter;//����ṹ��









#endif



