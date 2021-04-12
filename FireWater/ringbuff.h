#ifndef __ringbuff_H
#define __ringbuff_H
#define DEBUG 0
#include "def.h"
typedef int16_t err_t;

#define ERR_NULL -1
#define ERR_NOK  -2
#define ERR_OK 	 0
typedef struct ringbuff 
{
	uint8_t *buffer;  	/* 数据区域 */
	uint32_t size;      /* 环形缓冲区大小 */
	uint32_t in;        /* 数据入队指针 (in % size) */
	uint32_t out;       /* 数据出队指针 (out % size) */
}RingBuff_t;

extern err_t Create_RingBuff(RingBuff_t *rb, 
                             uint8_t *buffer,
                             uint32_t size
                            );
														
extern uint32_t Write_RingBuff(RingBuff_t *rb,
                               uint8_t *buffer, 
                               uint32_t len);
																
extern uint32_t Read_RingBuff(RingBuff_t *rb,
                              uint8_t *buffer, 
                              uint32_t len);

extern uint32_t CanRead_RingBuff(RingBuff_t *rb);

extern uint32_t CanWrite_RingBuff(RingBuff_t *rb);



#endif 












