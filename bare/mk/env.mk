CC = arm-none-eabi-gcc
AR = arm-none-eabi-ar
RANLIB = arm-none-eabi-ranlib

# Directories
BASE = ../..
CUBE = $(BASE)/stm32cube
DRIVERS = $(CUBE)/Drivers

# MCU flags
ARCH_FLAGS = -mthumb -mcpu=cortex-m4

## STM32Cube HAL flags
HAL_FLAGS = -DUSE_HAL_DRIVER -D$(MCU)

# Use newlib-nano. To disable it, specify USE_NANO=
USE_NANO = -specs=nano.specs

# Create include dependency files
DEP_FLAGS = -MD -MP


