#include "console.h"
#include "hal_globals.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

static const char TOP_LEFT[] = "\033[0;0H";
static const char CLEAR[] = "\033[2J";
static const char NEWLINE[] = "\r\n";
static const char WELCOME1[] = "Welcome to STM32F746-Discovery!\r\n";
static const char WELCOME2[] = "===============================\r\n\n";

static uint8_t rx_char;

static char rx_command[256];
static char *rx_pos = rx_command;

/*
 * _write() is a poorly documented weak callback from newlib that
 * makes printf() work as specified by the C standard.
 * This implementation conforms to the GCC ARM retarget sample code
 * and, apparently, makes printf() work.
 * Since we want to use it in our global assert(), we are tolerant
 * for errors (best effort strategy).
 * Will block!
 */
int _write(int fd, char *ptr, int len)
{
	(void) fd;
	(void) HAL_UART_Transmit(&huart1, (uint8_t*)ptr, (uint16_t)len, HAL_MAX_DELAY);
	return len;
}

void console_print_welcome(void)
{
	printf(TOP_LEFT);
	printf(CLEAR);
	printf(NEWLINE);
	printf(WELCOME1);
	printf(WELCOME2);
}

static bool rx_command_full(void)
{
	return rx_pos == rx_command + sizeof rx_command - 1;
}

static void interpret_received_char(char c)
{
	if (c == '\b')
	{
		if (rx_pos > rx_command)
			--rx_pos;
	}
	else
	{
		*rx_pos++ = c;
	}
}

void console_char_received(void)
{
	static uint8_t tx_char;
	tx_char = rx_char;

	if ((!rx_command_full() && isprint(rx_char)) || rx_char == '\b')
	{
		/*
		 * Try to echo back in interrupt mode (non-blocking, but will only work if the previous TX
		 * character has already made its way out).
		 * Notes:
		 * - tx_char, like rx_char, must be static: HAL_UART_Transmit_IT() does not make its own copy!
		 * - We cannot pass rx_char instead of tx_char, since it will immediately be reused for RX
		 *   when this function has returned.
		 * - We only consider the character as received if it was successfully echoed back.
		 */
		if (HAL_UART_Transmit_IT(&huart1, &tx_char, 1) == HAL_OK)
		{
			interpret_received_char((char) rx_char);
		}
	}

	console_start_rx();
}

/*
 * Receive a character in interrupt mode.
 * Does not block!
 */
void console_start_rx(void)
{
	assert(HAL_UART_Receive_IT(&huart1, &rx_char, 1) == HAL_OK);
}
