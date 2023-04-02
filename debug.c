#include <stdint.h>

#include "debug.h"
#include "stm32f407.h"

#ifdef DEBUG_SWV
/* Send a char through ITM */
void ITM_SendChar(uint8_t ch) {
    // read FIFO status in bit [0]:
    while(!(ITM_STIMULUS_PORT0 & 1));
    // write to ITM stimulus port0
    ITM_STIMULUS_PORT0 = ch;
}
#endif /*DEBUG_SWV*/
