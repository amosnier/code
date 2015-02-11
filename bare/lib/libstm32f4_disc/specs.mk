MCU = STM32F407xx
LIB = libstm32f4_disc.a

INC_DIRS = \
$(CUBE)/STM32F4-Discovery \
$(CUBE)/STM32F4xx_HAL_Driver_Inc \
$(BASE)/lib/libhal407 \
$(CUBE)/CMSIS_STM32F4xx_Inc \
$(CUBE)/CMSIS_Inc \

SRC_DIRS = \
$(CUBE)/STM32F4-Discovery \
$(CUBE)/STM32F4xx_HAL_Driver_Src \
