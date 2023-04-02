#ifndef _STM32F407_H_
#define _STM32F407_H_

//-----------Micro controller definitions (STM32F07)------------------
// Defining the base addresses of the u-controller peripherals
#define RCC_BASE_ADDR   (0x40023800)
#define GPIOD_BASE_ADDR (0x40020C00)

// Defining the offsets of the required registers
#define RCC_AHB1ENR_OFFST (0x30)
#define GPIOD_MODER_OFFST (0x0)
#define GPIOD_ODR_OFFST (0x14)

//-----------ARM Cortex M4 peripheral definitions----------------------
//Defining the Address of the SysTick registers
#define SYST_CSR_ADDR (0xE000E010)
#define SYST_RVR_ADDR (0xE000E014)

/* Debug Exception and Monitor Control Register base address */
#define DEMCR                 *((volatile uint32_t*) 0xE000EDFCu)

/* ITM register addresses */
#define ITM_STIMULUS_PORT0    *((volatile uint32_t*) 0xE0000000u)
#define ITM_TRACE_EN          *((volatile uint32_t*) 0xE0000E00u)

#endif /* _STM32F407_H_ */
