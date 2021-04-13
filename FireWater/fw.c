#include <string.h>
#include <stdio.h>
#include <math.h>
#include "ringbuff.h"
#include "serial_rx.h"
#include "fw.h"
#include "gpio.h"
#include "Vofa.h"

#define WaveSize 10000
extern DataFrame command_data;//�洢���ڽ��յ�����
extern 	Vofa_HandleTypedef jSHandle;  //JustFloat���
extern Amp amp;//�洢������ķ���
extern WavePointer pointer;//�洢�������ߵ������±�
//���±����Ǳ�Ҫ��
//���λ�����
RingBuff_t uart_ringbuff;		//����һ��fifo����
uint8_t rb[64];							//����fifo���飬���ڴ�Ŵ����ֽ���
//�Ҿ�Э����ռ���������
uint8_t res =0;
Serial_Msg_t msg;						//�Ҿ�Э�����ݰ����սṹ��
Serial_status_t status;			//�Ҿ�Э�����״̬���ݽṹ��
//���ϱ����Ǳ�Ҫ��
 /***********************************************
*�������ƣ�default_cb
*��    �ܣ�����ƥ��ȱʡ�ص��������𶯣�
*��ڲ����� *args (�����壬ȱʡֵΪ0)�� len((�����壬ȱʡֵΪ0)
*�� �� ֵ����
*��    ע��
************************************************/
void default_cb(void *args,uint8_t len)
{
	Vofa_Printf(&jSHandle,"can not find cmd or cmd callback NULL!\r\n");
}
 /***********************************************
*�������ƣ�cmd1_cb
*��    �ܣ�ƥ��"cmd1"�����ַ����ص�����
*��ڲ����� *args (�����������ָ��)�� len("cmd1"�������ĸ������ݸ���)
*�� �� ֵ����
*��    ע��
************************************************/
void stop_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
	command_data.mode=4;
	//Vofa_Printf(&jSHandle,"received data len =%d,test1_callback,float[0]=%f\r\n",len,buf[0]);
}
 /***********************************************
*�������ƣ�cmd2_cb
*��    �ܣ�ƥ��"cmd2"�����ַ����ص�����
*��ڲ����� *args (�����������ָ��)�� len("cmd2"�������ĸ������ݸ���)
*�� �� ֵ����
*��    ע��
************************************************/
void extend_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	//Vofa_Printf(&jSHandle,"received data len =%d,test2_callback,float[0]=%f,float[1]=%f\r\n",len,buf[0],buf[1]);
}
 /***********************************************
*�������ƣ�cmd3_cb
*��    �ܣ�ƥ��"cmd3"�����ַ����ص�����
*��ڲ����� *args (�����������ָ��)�� len("cmd3"�������ĸ������ݸ���)
*�� �� ֵ����
*��    ע��
************************************************/
void line_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	command_data.mode=1;
	command_data.angle=(uint16_t)buf[0];
	command_data.amp=(uint16_t)buf[1];
	pointer.p_x=0;
	pointer.p_y=0;//���������Ը���ʵʱλ�ö�̬������ʼ���ٵ�
	amp.AY=command_data.amp*sin(command_data.angle);
	amp.AX=amp.AY*(tan(command_data.angle)>0?tan(command_data.angle):-tan(command_data.angle));
	uint8_t i =command_data.angle/90;//�ж�����
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
	command_data.amp=(uint16_t)buf[1];
	pointer.p_x=0;
	pointer.p_y=WaveSize/4;//pi/2��λ��ǰ
	//Vofa_Printf(&jSHandle,"received data len =%d,test4_callback,float[0]=%f,float[1]=%f,float[2]=%f,float[3]=%f\r\n",len,buf[0],buf[1],buf[2],buf[3]);
}
void to_mid_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	command_data.mode=2;
	//Vofa_Printf(&jSHandle,"received data len =%d,xxx_callback,float[0]=%f,float[1]=%f,float[2]=%f,float[3]=%f\r\n",len,buf[0],buf[1],buf[2],buf[3]);
}
void cmd123_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	//Vofa_Printf(&jSHandle,"received data len =%d,cmd123_callback,float[0]=%f,float[1]=%f,float[2]=%f,float[3]=%f\r\n",len,buf[0],buf[1],buf[2],buf[3]);
}
void setkp_cb(void *args,uint8_t len)
{
	float buf[4];
	memset(buf,0,sizeof(buf)/sizeof(char));
	memcpy(buf,args,sizeof(buf)/sizeof(char));
	//Vofa_Printf(&jSHandle,"received data len =%d,setkp_cb_callback,kp=%f\r\n",len,buf[0]);
}
//�Ҿ�Э���ַ�����ص�����
fw_pare_t fw_cb[]={
	{"default",default_cb},
	{"stop",stop_cb},
	{"extend",extend_cb},
	{"line",line_cb},
	{"circle",circle_cb},
	{"to_mid",to_mid_cb},
	{"123",cmd123_cb},
	{"SETKP",setkp_cb},
};

//�Ҿ�Э�����ݱ�����ʼ��
void fw_init(void)
{
	  memset(&status,0,sizeof(status));
		memset(&msg,0,sizeof(msg));
		Create_RingBuff(&uart_ringbuff,rb,sizeof(rb));	//��������FIFO������
		#ifdef FW_DEBUG
		   Vofa_Printf(&jSHandle,"ringbuff creat \r\n");
		#endif		
}
//�Ҿ�Э�����������Ҫ��main������ѭ�����û��߶�ʱ���ã��������������
void fw_task(void)
{
		while(1 == Read_RingBuff(&uart_ringbuff,&res,1))
		{
			 if( FRAMING_COMPLETE == Serial_parse_char(res,&msg,&status))	//�Ӵ���FIFO�в��ҷ����Ҿ�Э������ݰ�
			 {
					if( 0 == assic_check(&msg))		//������ݰ��е������ַ��Ƿ�Ϸ���<'0'-'9','-',','>���ߴ�������','','�����
				 {			
					  fw_pare_cb_tassk(&msg,fw_cb,sizeof(fw_cb)/sizeof(fw_cb[0]));//ƥ��������ص��û����õ������Ӧ����
				 }
				 else				   
				 {
						#ifdef FW_DEBUG
							Vofa_Printf(&jSHandle,"assic_check fail! \r\n");
						#endif		 
				 }
			 	break;		//ֻҪ��⵽һ���Ҿ�Э�����ݣ�������ȷ����󣬾��˳��˴ν�����ֹ����
			 }
		}
}
