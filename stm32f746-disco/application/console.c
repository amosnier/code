#include "console.h"
#include "hal_globals.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

static const char TOP_LEFT[] = "\033[0;0H";
static const char CLEAR[] = "\033[2J";
static const char PROMPT[] = "746-disco> ";

static const char DEL = 127;

static char rx_char;

static char rx_command[64];
static char *rx_pos = rx_command;

static bool command_received = false;

void console_init(void)
{
	/*
	 * Disable I/O buffering for STDOUT stream, so that
	 * chars are sent out as soon as they are printed.
	 */
	setvbuf(stdout, NULL, _IONBF, 0);
}

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
	printf("\r\nWelcome to STM32F746-Discovery!\r\n");
	printf("===============================\r\n\n");
	printf(PROMPT);
}

static bool rx_command_full(void)
{
	return rx_pos == rx_command + sizeof rx_command - 1;
}

void console_receive_char(void)
{
	static char tx_char1;
	static char tx_char2;
	static char* tx_char;
	static bool using_tx_char1 = true;

	if (using_tx_char1)
		tx_char = &tx_char1;
	else
		tx_char = &tx_char2;

	*tx_char = rx_char;
	using_tx_char1 = !using_tx_char1;

	if (!rx_command_full() && isprint(rx_char))	{
		if (HAL_UART_Transmit_IT(&huart1, (uint8_t *) tx_char, 1) == HAL_OK)
			*rx_pos++ = rx_char;
	} else if (rx_pos > rx_command && rx_char == DEL) {
		if (HAL_UART_Transmit_IT(&huart1, (uint8_t *) tx_char, 1) == HAL_OK)
			--rx_pos;
	} else if (rx_char == '\r')	{
		*rx_pos = 0; // NULL-termination
		command_received = true;
	}

	if (!command_received)
		console_start_rx();
}

/*
 * Receive a character in interrupt mode.
 * Does not block!
 */
void console_start_rx(void)
{
	assert(HAL_UART_Receive_IT(&huart1, (uint8_t *) &rx_char, 1) == HAL_OK);
}

void console_handle_rx_event(void)
{
	if (command_received) {
		printf("\r\nYou have entered \"%s\"\r\n", rx_command);
		printf(PROMPT);
		rx_pos = rx_command;
		command_received = false;
		console_start_rx();
	}
}
