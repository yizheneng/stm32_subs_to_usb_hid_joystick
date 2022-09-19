#include "sbus.h"
#include "main.h"
#include "stm32f1xx_it.h"

#define SBUS_MIDD_VAL 900
#define SBUS_MAX_VAL 1300
#define SBUS_MIN_VAL 500

#define ACC_INDEX 2

uint8_t sbusBuffer[SBUS_BUFFER_SIZE];
int32_t channelData[16];
extern uint8_t data_ready;
void sbusDataHandler(void)
{
	if((sbusBuffer[0] == 0x0F) 
		&& (sbusBuffer[24] == 0x00)) {
		channelData[0] = ((sbusBuffer[1] | sbusBuffer[2] << 8) & 0x07FF);
		channelData[1] = ((sbusBuffer[2] >> 3 | sbusBuffer[3] << 5) & 0x07FF);
		channelData[2] = ((sbusBuffer[3] >> 6 | sbusBuffer[4] << 2 | sbusBuffer[5] << 10) & 0x07FF);
		channelData[3] = ((sbusBuffer[5] >> 1 | sbusBuffer[6] << 7) & 0x07FF);
		channelData[4] = ((sbusBuffer[6] >> 4 | sbusBuffer[7] << 4) & 0x07FF);
		channelData[5] = ((sbusBuffer[7] >> 7 | sbusBuffer[8] << 1 | sbusBuffer[9] << 9) & 0x07FF);
		channelData[6] = ((sbusBuffer[9] >> 2 | sbusBuffer[10] << 6) & 0x07FF);
		
//		for(int i = 0; i < 16; i++) {
//			if(i == ACC_INDEX) {
//				continue;
//			}
//			
//			channelData[i] = (channelData[i] - SBUS_MIDD_VAL) * 32768 / (SBUS_MAX_VAL - SBUS_MIDD_VAL) + 32768;
////			if(channelData[i] > 65535) {
////				channelData[i] = 65535;
////			} else if(channelData[i] < 0) {
////				channelData[i] = 0;
////			}
//		}
		data_ready = 1;
	}
}

