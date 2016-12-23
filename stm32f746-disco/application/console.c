#include "stm32f7xx_hal.h"

extern UART_HandleTypeDef huart1;

static const char TOP_LEFT[] = "\033[0;0H";
static const char CLEAR[] = "\033[2J";
static const char NEWLINE[] = "\r\n";
static const char WELCOME1[] = "Welcome to STM32F746-Discovery!\r\n";
static const char WELCOME2[] = "===============================\r\n\n";

/*
 * _write() is a poorly documented weak callback from newlib that
 * makes printf() work as specified by the C standard.
 * This implementation conforms to the GCC ARM retarget sample code
 * and, apparently, makes printf() work.
 * Since we want to use it in our global assert() we are tolerant
 * for errors (best effort strategy).
 */
int _write(int fd, char *ptr, int len)
{
	(void) fd;
	(void) HAL_UART_Transmit(&huart1, (uint8_t*)ptr, (uint16_t)len, HAL_MAX_DELAY);
	return len;
}

void print_welcome(void)
{
	printf(TOP_LEFT);
	printf(CLEAR);
	printf(NEWLINE);
	printf(WELCOME1);
	printf(WELCOME2);
}
