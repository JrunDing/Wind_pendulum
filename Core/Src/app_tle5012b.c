#include "app_tle5012b.h"
									


uint16_t SPIx_ReadWriteByte(uint16_t byte)
{

	uint16_t read_value = 0;
	
	HAL_SPI_Transmit( &hspi1, (uint8_t *)(&byte), sizeof(byte)/sizeof(uint16_t), 0xff );
	
	HAL_SPI_Transmit( &hspi1, (uint8_t *)(&read_value), sizeof(read_value)/sizeof(uint16_t), 0xff );
	return read_value;
}
 

uint16_t ReadAngle(void)
{
	return ( ReadValue(READ_ANGLE_VALUE) );
}
 

uint16_t ReadSpeed(void)
{
	return ReadValue(READ_SPEED_VALUE);
}
 
 
uint16_t ReadValue(uint16_t u16RegValue)
{
	uint16_t u16Data;
 
	SPI_CS_ENABLE;
	
	HAL_SPI_Transmit( &hspi1, (uint8_t *)(&u16RegValue), sizeof(u16RegValue)/sizeof(uint16_t), 0xff );
	HAL_SPI_Receive( &hspi1,(uint8_t *)(&u16Data), sizeof(u16Data)/sizeof(uint16_t), 0xff );
	
	SPI_CS_DISABLE;

	
	return((u16Data & 0x7FFF )<<1);
}





/*****************************************************/





uint16_t SPIx_ReadWriteByte_Y(uint16_t byte)
{

	uint16_t read_value = 0;
	
	HAL_SPI_Transmit( &hspi2, (uint8_t *)(&byte), sizeof(byte)/sizeof(uint16_t), 0xff );
	
	HAL_SPI_Transmit( &hspi2, (uint8_t *)(&read_value), sizeof(read_value)/sizeof(uint16_t), 0xff );
	return read_value;
}
 

uint16_t ReadAngle_Y(void)
{
	return ( ReadValue_Y(READ_ANGLE_VALUE) );
}
 

uint16_t ReadSpeed_Y(void)
{
	return ReadValue_Y(READ_SPEED_VALUE);
}
 
 
uint16_t ReadValue_Y(uint16_t u16RegValue)
{
	uint16_t u16Data;
 
	SPI_CS_ENABLE_Y;
	
	HAL_SPI_Transmit( &hspi2, (uint8_t *)(&u16RegValue), sizeof(u16RegValue)/sizeof(uint16_t), 0xff );
	HAL_SPI_Receive( &hspi2,(uint8_t *)(&u16Data), sizeof(u16Data)/sizeof(uint16_t), 0xff );
	
	SPI_CS_DISABLE_Y;

	
	return((u16Data & 0x7FFF )<<1);
}


