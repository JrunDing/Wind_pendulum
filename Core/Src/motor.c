#include <stdint.h>
#include "motor.h"
#include "gpio.h"
#include "tim.h"


//��һ�� ǰ������-1234    ����1 2    en 0-9999
/*
	1 ��	1��  0��
	2	��	1��  0��
	3	��	1��	 0��
	4	��	1��	 0��
*/
void motor_ctl ( uint8_t which , uint8_t ph , uint16_t en)
{
		switch(which)
		{
				case 1:
				{
						if(ph==1)
						{
								HAL_GPIO_WritePin(GPIOA, frontPh_Pin, GPIO_PIN_SET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,en);
						}
						else
						{
								HAL_GPIO_WritePin(GPIOA, frontPh_Pin, GPIO_PIN_RESET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1,en);
						}
				}break;
				case 3:
				{
						if(ph==1)
						{
								HAL_GPIO_WritePin(GPIOA, backPh_Pin, GPIO_PIN_RESET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,en);							
						}
						else
						{
								HAL_GPIO_WritePin(GPIOA, backPh_Pin, GPIO_PIN_SET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2,en);							
						}
				}break;
				case 2:
				{
						if(ph==1)
						{
								HAL_GPIO_WritePin(GPIOA, leftPh_Pin, GPIO_PIN_RESET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,en);							
						}
						else
						{
								HAL_GPIO_WritePin(GPIOA, leftPh_Pin, GPIO_PIN_SET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3,en);							
						}				
				}break;
				case 4:
				{
						if(ph==1)
						{
								HAL_GPIO_WritePin(GPIOA, rightPh_Pin, GPIO_PIN_SET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,en);							
						}
						else
						{
								HAL_GPIO_WritePin(GPIOA, rightPh_Pin, GPIO_PIN_RESET);
								__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4,en);							
						}			
				}break;	
		}
}




