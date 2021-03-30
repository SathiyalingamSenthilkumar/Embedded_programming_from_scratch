#------------------------------------------------------------------------------
#  @file           : Makefile
#  @author         : Sathiya Lingam Senthil Kumar <slsathiya20@gmail.com>
#
# Makefile to perform cross-compilation as per requested platform target
#
#      build - Builds and links all source files
#      all - same as build
#      compile-all - Compile all object files  
#      clean - removes all generated files
#------------------------------------------------------------------------------

SOURCES = main.c startup_STM32F407.c 

TARGET = final

# Architectures Specific Flags
LINKER_FILE = ls_STM32F407.ld
CPU = cortex-m4
ISA_ARCH = thumb
SPECS = rdimon.specs


# Compiler Flags and Defines
CC = arm-none-eabi-gcc 
LD = arm-none-eabi-ld
LDFLAGS = -Wl,-Map=$(TARGET).map -T $(LINKER_FILE) --specs=$(SPECS)
CFLAGS =  -O0 -Wall -Werror -std=gnu11 -mcpu=$(CPU) -m$(ISA_ARCH) \
			-mfloat-abi=soft
	#-march=armv7e-m  -mfpu=fpv4-sp-d16 \
	#--specs=$(SPECS) -Wall \
	#-g #For debug

SIZETOOL = arm-none-eabi-size     #To produce the size of code
DUMPTOOL = arm-none-eabi-objdump  


# Creating object file variables
OBJS = $(SOURCES:.c=.o)

# Creating Preprocessed file variables
PRES = $(SOURCES:.c=.i)

# Creating assembly file variables
ASMS = $(SOURCES:.c=.asm)

#Generating the Preprocessed files
%.i : %.c
	$(CC) $(CFLAGS) -E -o $@ $^

#Generating the assembly files	
%.asm : %.c
	$(CC) $(CFLAGS) -S -o $@ $^

#Generating the object files	
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^
	
# Building and linking to obtain the final target
.PHONY: all
all:$(TARGET).out 

$(TARGET).out: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Cleaning all non-source files and executables
.PHONY: clean
clean:
	rm -f $(OBJS) $(PRES) $(ASMS) $(TARGET).out $(TARGET).map

.PHONY: load
load:
	openocd -f board/stm32f4discovery.cfg