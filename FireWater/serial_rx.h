#ifndef _serial_rx_h_
#define _serial_rx_h_
#define ID_LEN 11
#define MAX_LEN 32
#include "def.h"
typedef struct{
uint8_t msgid_buf[ID_LEN];
uint8_t buf[MAX_LEN];
}Serial_Msg_t;
typedef struct {
    uint8_t msg_received;               ///< Number of received messages
    uint8_t parse_error;                ///< Number of parse errors
    uint8_t parse_state;  							///< Parsing state machine
    uint8_t packet_rx_count;						///< Received packets
} Serial_status_t;
typedef enum{
	PARSE_IDLE=0,
	PARSE_STATE,
	PARSE_BREAK,
	PARSE_DATE,
	PARSE_STOP,
}Parse_State_t;
typedef enum{
	FRAMING_COMPLETE=0,
	FRAMING_INCOMPLETE,
	FRAMING_CHARERROR,
	FRAMING_DATELENERROR,
	FRAMING_CMDLENERROR
}Parse_Error_t;
extern uint8_t assic_check(Serial_Msg_t *msg);
extern uint8_t Serial_parse_char(uint8_t res,Serial_Msg_t *msg,Serial_status_t *status);
extern uint8_t fw_sscanf(float des[],Serial_Msg_t *msg);
#endif // _serial_rx_h
