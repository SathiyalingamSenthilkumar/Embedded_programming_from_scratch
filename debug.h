#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>

#if defined(DEBUG_SEMIHOSTING) || defined(DEBUG_SWV)
#define DEBUG 1
#else /* DEBUG_SEMIHOSTING */
#define DEBUG 0
#endif /* DEBUG_SEMIHOSTING */

#if DEBUG
#define PRINTF(...) printf(__VA_ARGS__)
#else /* DEBUG */
#define PRINTF(...) do {} while (0)
#endif /* DEBUG */

#ifdef DEBUG_SEMIHOSTING
//Prototype of the function to initialise the semi-hosting feature
extern void initialise_monitor_handles(void);
#endif /* DEBUG_SEMIHOSTING */

#ifdef DEBUG_SWV
void ITM_SendChar(unsigned char);
#endif /*DEBUG_SWV*/

#endif /* _DEBUG_H_ */
