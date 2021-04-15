#include <string.h>
#include <stdio.h>
#include <math.h>
#include "ringbuff.h"
#include "serial_rx.h"
#include "fw.h"
#include "gpio.h"
#include "Vofa.h"
#include "main.h"
#define WaveSize 1500
extern DataFrame command_data;//存储串口接收的命令
extern 	Vofa_HandleTypedef jSHandle;  //JustFloat句柄
extern Amp amp;//存储两个轴的幅度
extern float K_ff;
extern WavePointer pointer;//存储跟踪曲线的两个下标
extern PID_parameter PID1_X;//用于追踪轨迹
extern PID_parameter PID1_Y;
extern PID_parameter PID2_X;//用于快速恢复中点
extern PID_parameter PID2_Y;
//以下变量是必要的
//环形缓冲区
RingBuff_t uart_ringbuff;		//定义一个fifo变量
uint8_t rb[64];							//定义fifo数组，用于存放串口字节流
//烈酒协议接收及解析变量
uint8_t res =0;
Serial_Msg_t msg;						//烈酒协议数据包接收结构体
Serial_status_t status;			//烈酒协议解析状态数据结构体
//以上变量是必要的
 /***********************************************
*函数名称：default_cb
*功    能：命令匹配缺省回调函数（勿动）
*入口参数： *args (无意义，缺省值为0)， len((无意义，缺省值为0)
*返 回 值：无
*备    注：
************************************************/
void default_cb(void *args,uint8_t len)
{
	Vofa_Printf(&jSHandle,"can not find cmd or cmd callback NULL!\r\n");
}
 /***********************************************
*函数名称：cmd1_cb
*功    能：匹配"cmd1"命令字符串回调函数
*入口参数： *args (解析后的数据指针)， len("cmd1"命令后面的浮点数据个数)
*返 回 值：无
*备    注：
************************************************/
void stop_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	command_data.mode=4;
	PID1_X.Bias_sum=0;
	PID1_X.Intergral=0;
	PID1_X.Last_bias=0;
	PID1_X.Last_last_bias=0;
	PID1_Y.Bias_sum=0;
	PID1_Y.Intergral=0;
	PID1_Y.Last_bias=0;
	PID1_Y.Last_last_bias=0;
	PID2_X.Bias_sum=0;
	PID2_X.Intergral=0;
	PID2_X.Last_bias=0;
	PID2_X.Last_last_bias=0;
	PID2_Y.Bias_sum=0;
	PID2_Y.Intergral=0;
	PID2_Y.Last_bias=0;
	PID2_Y.Last_last_bias=0;
	amp.CAX=0;
	amp.CAY=0;
	//Vofa_Printf(&jSHandle,"received data len =%d,test1_callback,float[0]=%f\r\n",len,buf[0]);
}
 /***********************************************
*函数名称：cmd2_cb
*功    能：匹配"cmd2"命令字符串回调函数
*入口参数： *args (解析后的数据指针)， len("cmd2"命令后面的浮点数据个数)
*返 回 值：无
*备    注：
************************************************/
void extend_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	//Vofa_Printf(&jSHandle,"received data len =%d,test2_callback,float[0]=%f,float[1]=%f\r\n",len,buf[0],buf[1]);
}
 /***********************************************
*函数名称：cmd3_cb
*功    能：匹配"cmd3"命令字符串回调函数
*入口参数： *args (解析后的数据指针)， len("cmd3"命令后面的浮点数据个数)
*返 回 值：无
*备    注：
************************************************/
void line_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	command_data.mode=1;
	command_data.angle=(uint16_t)buf[0];
	command_data.amp=(uint16_t)buf[1];
	//pointer.p_x=0;
	//pointer.p_y=0;//后续还可以根据实时位置动态调整开始跟踪点
	amp.AY=190*atan(command_data.amp*sin((float)command_data.angle/180.0*3.1415926)/92.0)*180.0/3.1415926;
	amp.AX=190*atan(command_data.amp*cos((float)command_data.angle/180.0*3.1415926)/92.0)*180.0/3.1415926;
		if(amp.CAX<amp.AX){
		amp.xlarger=1;
	}
	else{
		amp.xlarger=0;
	}
	if(amp.CAY<amp.AY){
		amp.ylarger=1;
	}
	else{
		amp.ylarger=0;
	}
	uint8_t i =command_data.angle/90;//判断象限
	switch(i){
		case 0:
			break;
		case 1:
			pointer.p_x=pointer.p_y+WaveSize/2;
			break;
		case 2:
			break;
		case 3:
			pointer.p_x=pointer.p_y+WaveSize/2;
			break;
	}

	//Vofa_Printf(&jSHandle,"received data len =%d,test3_callback,float[0]=%f,float[1]=%f,float[2]=%f\r\n",len,buf[0],buf[1],buf[2]);
}
void circle_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	command_data.mode=3;
	command_data.angle=(uint16_t)buf[0];
	command_data.amp=(uint8_t)buf[1];
//	pointer.p_x=0;
//	pointer.p_y=WaveSize/4;//pi/2相位超前
	pointer.p_y=pointer.p_x+WaveSize/4;//pi/2相位超前
	amp.AY=190*atan(command_data.amp/92.0)*180.0/3.1415926;
	amp.AX=190*atan(command_data.amp/92.0)*180.0/3.1415926;
	if(amp.CAX<amp.AX){
		amp.xlarger=1;
	}
	else{
		amp.xlarger=0;
	}
	if(amp.CAY<amp.AY){
		amp.ylarger=1;
	}
	else{
		amp.ylarger=0;
	}
	
	//Vofa_Printf(&jSHandle,"received data len =%d,test4_callback,float[0]=%f,float[1]=%f,float[2]=%f,float[3]=%f\r\n",len,buf[0],buf[1],buf[2],buf[3]);
}
void to_mid_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	command_data.mode=2;
	//pointer.p_x=0;
	//pointer.p_y=0;//后续还可以根据实时位置动态调整开始跟踪点
	amp.AY=48994;
	amp.AX=59590;
	//Vofa_Printf(&jSHandle,"received data len =%d,xxx_callback,float[0]=%f,float[1]=%f,float[2]=%f,float[3]=%f\r\n",len,buf[0],buf[1],buf[2],buf[3]);
}
void cmd123_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	motor_ctl((int)buf[0],(int)buf[1],(int)buf[2]);
	//Vofa_Printf(&jSHandle,"received data len =%d,cmd123_callback,float[0]=%f,float[1]=%f,float[2]=%f,float[3]=%f\r\n",len,buf[0],buf[1],buf[2],buf[3]);
}
void setkp_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	PID1_X.Kp=buf[0];
	K_ff=buf[1];
	PID1_X.Kd=buf[2];
	//Vofa_Printf(&jSHandle,"received data len =%d,setkp_cb_callback,kp=%f\r\n",len,buf[0]);
}
//烈酒协议字符命令及回调函数
fw_pare_t fw_cb[]={
	{"default",default_cb},
	{"stop",stop_cb},
	{"extend",extend_cb},
	{"line",line_cb},
	{"circle",circle_cb},
	{"to_mid",to_mid_cb},
	{"motor",cmd123_cb},
	{"SETKP",setkp_cb},
};

//烈酒协议数据变量初始化
void fw_init(void)
{
	  memset(&status,0,sizeof(status));
		memset(&msg,0,sizeof(msg));
		Create_RingBuff(&uart_ringbuff,rb,sizeof(rb));	//创建串口FIFO缓冲区
		#ifdef FW_DEBUG
		   Vofa_Printf(&jSHandle,"ringbuff creat \r\n");
		#endif		
}
//烈酒协议解析任务，需要在main函数中循环调用或者定时调用，此任务非阻塞。
void fw_task(void)
{
		while(1 == Read_RingBuff(&uart_ringbuff,&res,1))
		{
			 if( FRAMING_COMPLETE == Serial_parse_char(res,&msg,&status))	//从串口FIFO中查找符合烈酒协议的数据包
			 {
					if( 0 == assic_check(&msg))		//检查数据包中的数据字符是否合法在<'0'-'9','-',','>或者存在连续','','的情况
				 {			
					  fw_pare_cb_tassk(&msg,fw_cb,sizeof(fw_cb)/sizeof(fw_cb[0]));//匹配命令。并回调用户设置的命令对应函数
				 }
				 else				   
				 {
						#ifdef FW_DEBUG
							Vofa_Printf(&jSHandle,"assic_check fail! \r\n");
						#endif		 
				 }
			 	break;		//只要检测到一包烈酒协议数据，无论正确与错误，均退出此次解析防止阻塞
			 }
		}
}
