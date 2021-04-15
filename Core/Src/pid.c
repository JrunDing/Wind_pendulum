#include "pid.h"

extern Motor motor[4];
PID_parameter PID1_X;//用于追踪轨迹
PID_parameter PID1_Y;
PID_parameter PID2_X;//用于快速恢复中点
PID_parameter PID2_Y;

//位置式PID
float Position_Pid(PID_parameter* PID,float Current,float Target)
{
    PID->Sv=Target;
    PID->Pv=Current;
    PID->Bias=PID->Sv-PID->Pv;
    PID->Bias_sum+=PID->Bias;
		PID->Intergral=PID->Ki*PID->Bias_sum;
    PID->Output=PID->Kp*PID->Bias+PID->Intergral+0.5*PID->Kd*(PID->Bias-PID->Last_bias)+0.5*PID->Kd*(PID->Last_bias-PID->Last_last_bias);//针对微分项有一阶低通滤波
	  PID->Last_last_bias=PID->Last_bias;
    PID->Last_bias=PID->Bias;
    return PID->Output;
}
void Cap(PID_parameter* PID_X,PID_parameter* PID_Y){
	if(PID_X->Output>PID_X->Output_max){
		motor[1].pwm=PID_X->Output_max;
		motor[3].pwm=PID_X->Output_max;
	}
	else if(PID_X->Output<-PID_X->Output_max){
		motor[1].pwm=-PID_X->Output_max;
		motor[3].pwm=-PID_X->Output_max;
	}
	else{
		motor[1].pwm=PID_X->Output;
		motor[3].pwm=PID_X->Output;
	}
	if(PID_Y->Output>PID_Y->Output_max){
		motor[0].pwm=PID_Y->Output_max;
		motor[2].pwm=PID_Y->Output_max;
	}
	else if(PID_Y->Output<-PID_Y->Output_max){
		motor[0].pwm=-PID_Y->Output_max;
		motor[2].pwm=-PID_Y->Output_max;
	}
	else{
		motor[0].pwm=PID_Y->Output;
		motor[2].pwm=PID_Y->Output;
	}
}
void Execute(void){
//	for(uint8_t i =0;i<4;i++){
//		if(motor[i].pwm>=0){
//			motor[i].dir=1;
//			motor_ctl(i+1,motor[i].dir,(uint16_t)motor[i].pwm);
//		}
//		else{
//			motor[i].dir=0;
//			motor_ctl(i+1,motor[i].dir,(uint16_t)-motor[i].pwm);
//		}
//	}
		
		if(motor[0].pwm>=0){
			motor[0].dir=1;
			motor_ctl(1,motor[0].dir,(uint16_t)motor[0].pwm);
			motor[2].dir=0;
			motor_ctl(3,motor[2].dir,200);
		}
		else{
			motor[0].dir=1;
			motor_ctl(1,motor[0].dir,200);
			motor[2].dir=0;
			motor_ctl(3,motor[2].dir,(uint16_t)-motor[2].pwm);
		}
		if(motor[1].pwm>=0){
			motor[1].dir=1;
			motor_ctl(2,motor[1].dir,(uint16_t)motor[1].pwm);
			motor[3].dir=0;
			motor_ctl(4,motor[3].dir,200);
		}
		else{
			motor[1].dir=1;
			motor_ctl(2,motor[1].dir,200);
			motor[3].dir=0;
			motor_ctl(4,motor[3].dir,(uint16_t)-motor[3].pwm);
		}
	
}
void AntiWindup(PID_parameter* PID){
	if(PID->Intergral > PID->Intergral_max){
		PID->Intergral = PID->Intergral_max;
	}
	else if(PID->Intergral < -PID->Intergral_max){
		PID->Intergral = -PID->Intergral_max;
	}
}




