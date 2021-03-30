/**
 ******************************************************************************
 * @file           : startup_STM32F407.c
 * @author         : Sathiya Lingam Senthil Kumar <slsathiya20@gmail.com>
 * @brief          : Linker script for STM32F407
 *                      - 1024Kbytes FLASH
 *                      - 128Kbytes RAM.
 *					 The Linker script is responsible for merging the different
					 sections of the object file.
 *            
 ******************************************************************************
 */
 
/* Entry Point */
ENTRY(Reset_Handler)

/* Memory Definitions */
MEMORY
{
  FLASH    (rx)    : ORIGIN = 0x08000000,   LENGTH = 1024K
  SRAM     (xrw)   : ORIGIN = 0x20000000,   LENGTH = 128K
}

/* Sections Definitions*/
SECTIONS
{
  .text :
  {	
	. = ALIGN(4);       /* Aliging to word boundary*/
    *(.isr_vector)
    *(.text)
	*(.text.*)
	*(.init)
	*(.fini)
	*(.rodata)
	*(.rodata.*)
	. = ALIGN(4);       /* Aliging to word boundary*/
	_etext = .;        /* define a global symbols at end of text memory (.data section starts here)*/
  } > FLASH
  
  /* The stdlib introduces new sections between .text and .data.
		-Therefore this should be changed. */
  _loadaddr_data = LOADADDR(.data); /* Storing the load address to a new symbol */
  
  .data :
  {
	. = ALIGN(4);       /* Aliging to word boundary*/  
	_sdata = .;        /*Create a global symbol at data start*/  
	*(.data)
	*(.data.*)
	. = ALIGN(4);       /* Aliging to word boundary*/
	_edata = .;        /* define a global symbol at data end */
  } > SRAM AT> FLASH   /* VMA - SRAM, LMA - FLASH*/
  
  .bss :
  {
	. = ALIGN(4);       /* Aliging to word boundary*/  
	_sbss = .;  		/* define a global symbol at bss start */
	__bss_start__ = _sbss; /* Symbol required when integrating stdlib*/
	*(.bss)
	*(.bss.*)
	. = ALIGN(4);       /* Aliging to word boundary*/
	_ebss = .;  		/* define a global symbol at bss end */
	__bss_end__ = _ebss;    /* Symbol required when integrating stdlib*/
	. = ALIGN(4); 
	end = .;     /*This is required for sbark => To indicate the start of heap*/
	__end__ = end; /* Required by the semihosting library*/
  } > SRAM

}