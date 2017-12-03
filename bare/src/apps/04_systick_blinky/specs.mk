MCU = STM32F407xx

EXE = app

BASE = ../../..

INC_DIRS = \
. \
mcu_init \
scheduler \
$(BOARDS)/stm32f4-disc/led \
$(CUBE)/STM32F4-Discovery \
$(CUBE)/STM32F4xx_HAL_Driver_Inc \
$(CUBE)/CMSIS_STM32F4xx_Inc \
$(CUBE)/CMSIS_Inc \

# Directories in which all source files are compiled and linked
SRC_DIRS = \
. \
mcu_init \
scheduler \
$(MCUS)/stm32f407xx/startup \
$(CUBE)/STM32F4xx_HAL_Driver_Src \

# Directories in which source files are cherry-picked
SRC_ADD_DIRS = \
$(CUBE)/STM32F4-Discovery \

# Cherry-picked source files
SRC_ADD_FILES = \
stm32f4_discovery.c \
