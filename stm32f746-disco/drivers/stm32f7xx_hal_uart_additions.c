#include "stm32f7xx_hal_uart_additions.h"

/**
  * @brief Send a byte if possible. Does not block.
  * @param huart: UART handle.
  * @param byte: byte to send.
  * @retval HAL status
  * @note: not reentrant, and might conflict with standard HAL UART functions, but they are not thread-safe anyway.
  */
HAL_StatusTypeDef HAL_UART_TransmitByte(UART_HandleTypeDef *huart, uint8_t byte)
{
	if (__HAL_UART_GET_FLAG(huart, UART_FLAG_TXE)) {
		if ((huart->Init.WordLength == UART_WORDLENGTH_9B) && (huart->Init.Parity == UART_PARITY_NONE))
		{
			huart->Instance->TDR = ((uint16_t) byte & (uint16_t) 0x01FFU);
		}
		else
		{
			huart->Instance->TDR = (byte & (uint8_t)0xFFU);
		}
		return HAL_OK;
	} else {
		return HAL_BUSY;
	}
}
