/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Sathiya Lingam Senthil Kumar <slsathiya20@gmail.com>
 * @brief          : A simple example of configuring the SysTick timer and blink
 * 					 the LED's. Example was performed to familaize with configuring
 * 					 the SysTick timer
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>

/* Debug related macros and functions */
#include "debug.h"

/* Platform dependant defines */
#include "stm32f407.h"

#define SYSCLK 16000000U

//Function to initialize the SysTick timer
void init_systick(float timeout);

int global_data_1 = 1; //Goes into .data section
int global_data_2 = 1; //Goes into .data section

int global_bss_1;      //Goes into .bss section
int global_bss_2 = 0;  //Goes into .bss section

const int const_data_1 = 10;     //Goes into .rodata section 
const uint8_t const_data_2 = 2;  //Goes into .rodata section

struct data_struct{
	uint32_t var_2;
	uint8_t var_1;
};

typedef struct data_struct data_struct_t; 

data_struct_t arr_struct_init_data[50] = {{1,2},{3,2}}; //Goes into .data section
data_struct_t arr_struct_uinit_bss[50];                 //Goes into .bss section
//Each array element of struct takes 8 bytes (It is aligned).

int main(void)
{	
#ifdef DEBUG_SEMIHOSTING
	//Initializing the semi-hosting feature
	initialise_monitor_handles();
#endif /* DEBUG_SEMIHOSTING */

#ifdef DEBUG_SWV
    // Enable TRCENA
    DEMCR |= ( 1 << 24);
    // Enable stimulus port 0
    ITM_TRACE_EN |= ( 1 << 0);
#endif /* DEBUG_SWV */

	//Blinking the LEDs of the board
	  //4 LED's of the boardare connected to portD pins 12-15

	//Registers
	volatile uint32_t* pRCC_AHB1ENR = (uint32_t*)(RCC_BASE_ADDR + RCC_AHB1ENR_OFFST);
	volatile uint32_t* pGPIOD_MODER = (uint32_t*)(GPIOD_BASE_ADDR + GPIOD_MODER_OFFST);
	volatile uint32_t* pGPIOD_ODR   = (uint32_t*)(GPIOD_BASE_ADDR + GPIOD_ODR_OFFST);

	//RCC_AHB1 bus enable the portD => Setting the bit 3
	*pRCC_AHB1ENR |= (1<<3);

	//Configuring the Port pins 12-15 as output using the GPIOD_MODER Register (01 for output)
	  //Configuring pin12 as output - pin 24 must be set
	*pGPIOD_MODER |= (1 << 24);
	  //Configuring pin13 as output - pin 26 must be set
	*pGPIOD_MODER |= (1 << 26);
	  //Configuring pin14 as output - pin 28 must be set
	*pGPIOD_MODER |= (1 << 28);
	  //Configuring pin15 as output - pin 30 must be set
	*pGPIOD_MODER |= (1 << 30);

	//Writing the output high for glowing the LED
	  //Setting bit 12
	*pGPIOD_ODR |= (1 << 12);
	  //Setting bit 13
	*pGPIOD_ODR |= (0 << 13);
	  //Setting bit 14
	*pGPIOD_ODR |= (1 << 14);
	  //Setting bit 15
	*pGPIOD_ODR |= (0 << 15);

	//SYSTICK-------------------------------------------------
	float timeout = 1; //Enter the timeout in seconds (within 1s)=> Reload value is 24 bits calculate the upper limit
	init_systick(timeout);
	//--------------------------------------------------------
	while(1);
}

void init_systick(float timeout){

	float N_singlecount = (1/(float)SYSCLK);
	uint32_t Ncount_reload = timeout/N_singlecount;
	
	/* The division part requires few other symbols.
		Inorder to link with nostdlib the division part is commented out
	*/
	
	//uint32_t Ncount_reload = 16000000; //Reload value for a delay of 1 second

	//Registers
	volatile uint32_t* pSYST_CSR = (uint32_t*) SYST_CSR_ADDR;
	volatile uint32_t* pSYST_RVR = (uint32_t*) SYST_RVR_ADDR;

	//Setting the reload value
	*pSYST_RVR = Ncount_reload;

	//Configuring the control register
	  //Setting the clock to be processor clock
	*pSYST_CSR |= (1<<2);
	  //Enabling the exception for the SysTick timer
	*pSYST_CSR |= (1<<1);
	  //Enable the counter itself
	*pSYST_CSR |= (1<<0);

}

void SysTick_Handler(void){
	// Printing 
	PRINTF("Hello from SysTick_Handler\n");
	
	// Initializing the pointer variable in this function
	volatile uint32_t* pGPIOD_ODR   = (uint32_t*)(GPIOD_BASE_ADDR + GPIOD_ODR_OFFST);

	//Toggling the LED's
	  //Setting bit 12
	*pGPIOD_ODR ^= (1 << 12);
	  //Setting bit 13
	*pGPIOD_ODR ^= (1 << 13);
	  //Setting bit 14
	*pGPIOD_ODR ^= (1 << 14);
	  //Setting bit 15
	*pGPIOD_ODR ^= (1 << 15);
}
