#include "console.h"
#include "hal_globals.h"
#include <assert.h>

static const char TOP_LEFT[] = "\033[0;0H";
static const char CLEAR[] = "\033[2J";
static const char NEWLINE[] = "\r\n";
static const char WELCOME1[] = "Welcome to STM32F746-Discovery!\r\n";
static const char WELCOME2[] = "===============================\r\n\n";

static uint8_t rx_char;
static uint8_t buf[256];
static uint8_t *in;
static uint8_t *out;

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

void console_char_received(void)
{
	printf("%d", rx_char);
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
