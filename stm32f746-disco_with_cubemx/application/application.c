#include <console_command.h>
#include "console.h"
#include <stdbool.h>

void application(void)
{
	console_init();
	console_print_welcome();
	console_receive_char();

	while (true) {
		console_command_step();
	}
}
