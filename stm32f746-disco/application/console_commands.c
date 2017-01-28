#include "console_commands.h"
#include "console.h"
#include <stdio.h>
#include <stdbool.h>

static bool command_received = false;

static enum {
	STATE_IDLE,
	STATE_STOPWATCH,
} state = STATE_IDLE;

static void state_idle(void)
{
	if (!command_received)
		return;

	printf("\r\n\"%s\" is not a supported command\r\n", console_command());
	command_received = false;
	console_command_handled();
}

static void state_stopwatch(void)
{

}

void console_command_step(void)
{
	switch (state) {
	case STATE_IDLE:
		state_idle();
		break;
	case STATE_STOPWATCH:
		state_stopwatch();
		break;
	default:
		assert(false);
		break;
	}

}

void console_command_received(void)
{
	command_received = true;
}
