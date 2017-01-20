#include "console.h"

void application(void)
{
	console_init();
	console_print_welcome();
	console_receive_char();

	for (;;)
	{
		console_handle_rx_event();
	}
}
