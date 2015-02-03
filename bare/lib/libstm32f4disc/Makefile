# Path relative to including Makefile at ../dir1/dir2/!
include ../../mk/env.mk

MCU = STM32F407xx
LIB = libstm32f4disc.a

# INC_DIRS, also required by tags.mk!
INC_DIRS = \
$(DRIVERS)/BSP/STM32F4-Discovery \
$(DRIVERS)/STM32F4xx_HAL_Driver/Inc \
$(BASE)/lib/libhal407 \
$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
$(DRIVERS)/CMSIS/Include \

# Include dirs
INC = $(addprefix -I, $(INC_DIRS))

# SRC, also required by tags.mk!
SRC = \
$(DRIVERS)/BSP/STM32F4-Discovery \

vpath %.c $(SRC)

OBJS = $(patsubst %.c,%.o,$(notdir $(wildcard $(DRIVERS)/BSP/STM32F4-Discovery/*.c)))

include ../../mk/lib.mk
