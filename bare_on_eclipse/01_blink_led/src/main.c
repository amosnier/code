#include <stdint.h>

static void led_config(void);
static void led_on(void);
static void led_off(void);
static void busy_wait(void);

int main(void)
{
	led_config();
	for ( ; ; ) {
		led_on();
		busy_wait();
		led_off();
		busy_wait();
	}
}

static void led_config(void)
{
	/*
	 * Write 8 (IO port D clock enabled) to address 0x4002 3830 (RCC AHB1
	 * peripheral clock enable register).
	 */
	*(volatile uint16_t*)0x40023830 = 0x08;

	/*
	 * Write 0x0400 0000 (General purpose output mode for I/O 13) to address
	 * 0x4002 0c00 (GPIO D port mode register).
	 */
	*(volatile uint32_t*)0x40020c00 = 0x04000000;
}

static void led_on(void)
{
	/*
	 * Write 0x2000 (I/O 13 1) to address 0x4002 0c14 (GPIO D port output
	 * data register).
	 */
	*(volatile uint16_t*)0x40020c14 |= 0x2000;
}

static void led_off(void)
{
	*(volatile uint16_t*)0x40020c14 &= (uint16_t)~0x2000;
}

static void busy_wait(void)
{
	for (int i = 0; i < 10000000; i++)
		asm(""); // prevent the compiler from optimizing out the whole function
}
