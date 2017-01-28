#include "console.h"
#include "hal_globals.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <console_commands.h>

static const char TOP_LEFT[] = "\033[0;0H";
static const char CLEAR[] = "\033[2J";
static const char HIDE_CURSOR[] = "\033[?25l";
static const char SHOW_CURSOR[] = "\033[?25h";
static const char PROMPT[] = "\r\nf746-disco> ";

static const char ETX = 3;
static const char DEL = 127;

static char rx_char;

static char command[64];
static char *rx_pos = command;

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
	printf("\r\nWelcome to the STM32F746-Discovery!\r\n");
	printf("===================================\r\n\n");
	printf(PROMPT);
}

void console_hide_cursor(void)
{
	printf(HIDE_CURSOR);
}

void console_show_cursor(void)
{
	printf(SHOW_CURSOR);
}

static inline bool rx_command_full(void)
{
	return rx_pos == command + sizeof command - 1;
}

void console_receive_completed(void)
{
	static char tx_char;

	tx_char = rx_char;

	if (!rx_command_full() && isprint(rx_char))	{
		if (HAL_UART_Transmit_IT(&huart1, (uint8_t*) &tx_char, 1) == HAL_OK) // enable RX in TX callback
			*rx_pos++ = rx_char;
	} else if (rx_pos > command && rx_char == DEL) {
		if (HAL_UART_Transmit_IT(&huart1, (uint8_t*) &tx_char, 1) == HAL_OK) // enable RX in TX callback
			--rx_pos;
	} else if (rx_char == '\r')	{
		*rx_pos = 0; // NULL-termination
		console_command_received();
	} else {
		console_receive_char(); // character ignored, enable RX
	}
}

/*
 * Receive a character in interrupt mode.
 * Does not block!
 */
void console_receive_char(void)
{
	assert(HAL_UART_Receive_IT(&huart1, (uint8_t *) &rx_char, 1) == HAL_OK);
}

bool console_stop_received(void)
{
	char c;
	return (HAL_UART_Receive(&huart1, (uint8_t *) &c, 1, 0) == HAL_OK && c == ETX);
}

void console_command_handled(void)
{
	printf(PROMPT);
	rx_pos = command;
	console_receive_char();
}

const char * console_command(void)
{
	return command;
}
