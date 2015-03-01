MCU = STM32F407xx

EXE = app

BASE = ../../..

INC_DIRS = \
. \
$(BOARDS)/stm32f4-disc/led \
$(MCUS)/stm32f407xx/minimal_hw_init \
$(CUBE)/STM32F4-Discovery \
$(CUBE)/STM32F4xx_HAL_Driver_Inc \
$(CUBE)/CMSIS_STM32F4xx_Inc \
$(CUBE)/CMSIS_Inc \

# Directories in which all source files are compiled and linked
SRC_DIRS = \
. \
$(MCUS)/stm32f407xx/startup \
$(MCUS)/stm32f407xx/minimal_hw_init \
$(CUBE)/STM32F4xx_HAL_Driver_Src \

# Directories in which source files are cherry-picked
SRC_ADD_DIRS = \
$(CUBE)/STM32F4-Discovery \

# Cherry-picked source files
SRC_ADD_FILES = \
stm32f4_discovery.c \
