#ifndef _fw_h_
#define _fw_h_
#include "serial_rx.h"
//#define FW_DEBUG

typedef struct{
  char cmd[11];
  void (*Callback)(void *args,uint8_t len);
}fw_pare_t;
int8_t fw_pare_cb_tassk(Serial_Msg_t *msg , void* args,uint16_t len);
void fw_init(void);
void fw_task(void);
#endif
