#ifndef STM32F7XX_HAL_UART_ADDITIONS_H
#define STM32F7XX_HAL_UART_ADDITIONS_H

#include "stm32f7xx_hal.h"

HAL_StatusTypeDef HAL_UART_TransmitByte(UART_HandleTypeDef *huart, uint8_t byte);

#endif // STM32F7XX_HAL_UART_ADDITIONS_H
