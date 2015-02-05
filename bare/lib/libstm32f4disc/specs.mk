MCU = STM32F407xx
LIB = libstm32f4_disc.a

INC_DIRS = \
$(DRIVERS)/BSP/STM32F4-Discovery \
$(DRIVERS)/STM32F4xx_HAL_Driver/Inc \
$(BASE)/lib/libhal407 \
$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
$(DRIVERS)/CMSIS/Include \

SRC_DIRS = \
$(DRIVERS)/BSP/STM32F4-Discovery \
$(DRIVERS)/STM32F4xx_HAL_Driver/Src \
