#include "console_commands.h"
#include <stdio.h>

void console_interpret_command(const char * command)
{
	printf("\r\nYou have entered \"%s\"\r\n", command);
}
