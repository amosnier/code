#include "console_commands.h"
#include "console.h"
#include <stdio.h>
#include <stdbool.h>

bool command_received = false;

void console_command_step(void)
{
	if (command_received) {
		printf("\r\nYou have entered \"%s\"\r\n", console_command());
		command_received = false;
		console_command_handled();
	}
}

void console_command_received(void)
{
	command_received = true;
}
