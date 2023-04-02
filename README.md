# Description
 
- The objective of this project is to develop an embedded bare-metal application
 from scratch with GNU cross-compiler tool chain (without IDE).
- The microcontroller chosen for this purpose is STM32F407VGT from ST Microelectronics.
- The microcontroller is based on Arm® Cortex®-M4 32-bit processor.
- The main focus of the project includes:
    - Writing the startup file from scratch.
	- Writing the Linker script from scratch.
	- Automating build system using GNU Make
	- Using openOCD and GDB client for debugging.
- The main program uses the SysTick timer (interrupt mode) to blink a few LEDs.

## Toolchain

### Building
- GNU Make is used to automate the build process.
- To build the final application:
```bash
make all
```
### Flashing and Erasing
- The open-source version of STM's [STLINK tools](https://github.com/stlink-org/stlink) are used for this purpose.
- Make commands are made available, to flash the executable:
```bash
make flash
```
- To erase the flash:
```bash
make erase
```
- To reset the target:
```bash
make reset
```

## Debug

- The support for printf() style debugging is maintained.
- ARM Cortex M4 supports two ways of doing this semi-hosting and serial wire viwer (SWD + SWO).
- Support for semi-hosting is available now.

### Semihosting
- Semi-hosting is mechanism the enables code running on ARM processor to communicate with
 host computer running a debugger. To know more about semi-hosting refer ARM's documentation.

- To enable semi-hosting the application should be built with a special flag (DEBUG=semihosting):

```bash
make DEBUG=semihosting
```
- The application now needs debugger with semi-hosting enabled. In this project the OpenOCD
 GDBServer is used.
- Open a terminal and start gdb server using openOCD:
```bash
openocd -f board/stm32f4discovery.cfg
```
- Open another terminal to start gdb client and enable semi-hositing
```bash
arm-none-eabi-gdb -ex "target extended-remote localhost:3333" -ex "monitor reset halt" -ex "monitor arm semihosting enable"
```
- Now, the printouts should be seen on the server terminal.

> NOTE: Starting the application before enabling semi-hosting would result in a HardFault.

### Serial wire viewer (SWD + SWO)
- Most of the implementation was inspired from this page:
https://www.codeinsideout.com/blog/stm32/swv/

- The serial wire viewer will work on the IDE, to get it working
with openOCD may be this link is useful:
https://www.openstm32.org/forumthread4455
