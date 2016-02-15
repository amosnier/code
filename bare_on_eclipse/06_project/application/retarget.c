#include "usart.h"

/**
 * @brief  Newlib standard output re-targeting. Send the bytes, e.g. to a UART,
 *         and printf() will automagically start working! :-)
 * @param  fd: file descriptor (Posix-like interface)
 * @param  ptr: pointer to the bytes to output
 * @param  len: number of bytes to output
 *
 * @return The number of bytes output
 *
 * @note   Blocking!
 * @note   Will halt on failure.
 */
int _write (int fd, char *ptr, int len)
{
	(void)fd;
	assert_param(len >= 0 && len <= (int)UINT16_MAX);
	assert_param(HAL_UART_Transmit(&huart2, (uint8_t*)ptr, (uint16_t)len, UINT32_MAX) == HAL_OK);
	return len;
}

/**
 * @brief  Newlib standard input re-targeting. Fetch the bytes, e.g. from a UART,
 *         and scanf() will automagically start working! :-)
 * @param  fd: file descriptor (Posix-like interface)
 * @param  ptr: pointer to the bytes to input
 * @param  len: number of bytes to input
 *
 * @return The number of bytes input
 *
 * @note   Blocking!
 * @note   Will halt on failure.
 */
int _read (int fd, char *ptr, int len)
{
	(void)fd;
	assert_param(len >= 0 && len <= (int)UINT16_MAX);
	assert_param(HAL_UART_Receive(&huart2, (uint8_t*)ptr, (uint16_t)len, UINT32_MAX) == HAL_OK);
	return len;
}

/**
 * @brief  Newlib standard output re-targeting. Send a byte.
 * @param  ch: character
 *
 * @note   Blocking!
 * @note   Will halt on failure.
 */
void _ttywrch(int ch) {
	assert_param(HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, UINT32_MAX) == HAL_OK);
}
