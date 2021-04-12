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
	uint8_t *buffer;  	/* �������� */
	uint32_t size;      /* ���λ�������С */
	uint32_t in;        /* �������ָ�� (in % size) */
	uint32_t out;       /* ���ݳ���ָ�� (out % size) */
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












