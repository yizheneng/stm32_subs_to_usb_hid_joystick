#ifndef _SBUS_H_
#define _SBUS_H_
#include <stdint.h>
#define SBUS_BUFFER_SIZE 40
extern uint8_t sbusBuffer[SBUS_BUFFER_SIZE];

void sbusDataHandler(void);

#endif
