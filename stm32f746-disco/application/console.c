#include "console.h"
#include "hal_globals.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <console_commands.h>

static const char TOP_LEFT[] = "\033[0;0H";
static const char CLEAR[] = "\033[2J";
static const char PROMPT[] = "\r\nf746-disco> ";

static const char DEL = 127;

static char rx_char;

static char rx_command[64];
static char *rx_pos = rx_command;

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

static inline bool rx_command_full(void)
{
	return rx_pos == rx_command + sizeof rx_command - 1;
}

void console_receive_completed(void)
{
	/*
	 * Strategy: if the received character is printable or a delete, and we can buffer it,
	 * we try to echo it. If we manage to echo it, we buffer it. If the received character
	 * is a carriage return, we NULL-terminate the buffer and handle the command.
	 * In all other cases, we ignore the received character.
	 * In the carriage return case, we re-enable reception when the command has been handled
	 * (RX is ignored while handling a command). Otherwise, we re-enable reception in the TX
	 * completed callback, or at once if we do not echo.
	 *
	 * Note: yes, we handle the command in this ISR-context, which might take ages. But
	 * reception is disabled anyway during that time. We might block interrupts with a
	 * priority that is lower or equal to ours. If this is a problem, these interrupts
	 * shall be moved to a higher priority.
	 */

	static char tx_char;

	tx_char = rx_char;

	if (!rx_command_full() && isprint(rx_char))	{
		if (HAL_UART_Transmit_IT(&huart1, (uint8_t*) &tx_char, 1) == HAL_OK)
			*rx_pos++ = rx_char;
	} else if (rx_pos > rx_command && rx_char == DEL) {
		if (HAL_UART_Transmit_IT(&huart1, (uint8_t*) &tx_char, 1) == HAL_OK)
			--rx_pos;
	} else if (rx_char == '\r')	{
		*rx_pos = 0; // NULL-termination
		console_handle_command(rx_command);
		printf(PROMPT);
		rx_pos = rx_command;
		console_receive_char();
	} else {
		console_receive_char();
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
