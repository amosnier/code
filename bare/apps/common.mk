CC = arm-none-eabi-gcc

EXE = app

# Directories
BASE = ../..
CUBE = $(BASE)/stm32cube
DRIVERS = $(CUBE)/Drivers

# Include dirs
INCLUDE_DIRS = \
-I. \
-I$(DRIVERS)/BSP/STM32F4-Discovery \
-I$(DRIVERS)/STM32F4xx_HAL_Driver/Inc \
-I$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
-I$(DRIVERS)/CMSIS/Include \

# Source dirs
SOURCES = $(BASE)/startup:.
vpath %.c $(SOURCES)
vpath %.S $(SOURCES)

# Add common object files to per app list
OBJS += startup_ARMCM4.o $(patsubst %.c,%.o,$(wildcard *.c))

# MCU flags
ARCH_FLAGS = -mthumb -mcpu=cortex-m4

## STM32Cube flags
CUBE_FLAGS = -DSTM32F407xx -DUSE_HAL_DRIVER

# Use newlib-nano. To disable it, specify USE_NANO=
USE_NANO = -specs=nano.specs

# Use semihosting or not
USE_SEMIHOST = -specs=rdimon.specs
USE_NOHOST = -specs=nosys.specs

SPEC_FLAGS = $(USE_NANO) $(USE_NOHOST)

# Garbage collect unused sections
GC=-Wl,--gc-sections

# Create map file
MAP=-Wl,-Map=$(EXE).map

# Create include dependency files
DEP_FLAGS = -MD -MP

# CPPFLAGS are passed both to the compiler and the assembler (but not the linker)
COMMON_FLAGS = $(DEP_FLAGS) $(SPEC_FLAGS) $(ARCH_FLAGS) -g -Wall
CPPFLAGS = -D__NO_SYSTEM_INIT $(CUBE_FLAGS) $(INCLUDE_DIRS) $(COMMON_FLAGS)
LDFLAGS= -L$(BASE)/ldscripts -T script.ld $(GC) $(MAP) $(SPEC_FLAGS) -g

# Dependencies and rules, using GNU make implicits as much as possible
$(EXE): $(OBJS)

.PHONY: clean
clean:
	rm -f $(EXE) *.o *.d *.map *~

.PHONY: show
show:
	@echo $(OBJS)
