#include "console.h"
#include "console_commands.h"
#include <stdbool.h>

void application(void)
{
	console_init();
	console_print_welcome();
	console_receive_char();

	while (true)
	{
		console_transmit_completed();
	}
}
