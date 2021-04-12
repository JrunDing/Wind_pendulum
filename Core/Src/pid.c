#include "pid.h"


PID_parameter PID;


//Œª÷√ ΩPID
float Position_Pid(float Current,float Target)
{
    PID.Sv=Target;
    PID.Pv=Current;
    PID.Bias=PID.Sv-PID.Pv;
    PID.Bias_sum+=PID.Bias;
    PID.Output=PID.Kp*PID.Bias+PID.Ki*PID.Bias_sum+PID.Kd*(PID.Bias-PID.Last_bias);
    PID.Last_bias=PID.Bias;
    return PID.Output;
}




