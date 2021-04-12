#include "Vofa.h"
#include "js.h"
#include "usart.h"



void Vofa_SendDataCallBack(Vofa_HandleTypedef *handle, uint8_t *data, uint16_t length)
{
		HAL_UART_Transmit(&huart1,data++,length,0xffff);
		while(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_TC)==RESET);//TC Register
}



