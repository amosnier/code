#include "console_commands.h"
#include "console.h"
#include "stopwatch.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

static volatile bool command_received = false;
static bool stop_received = false;

static enum State {
	STATE_IDLE,
	STATE_STOPWATCH,
} state = STATE_IDLE;

char arg[8][16]; // 1 command name + (n - 1) arguments
int num_args = 0;

static void illegal_command(void)
{
	printf("\"%s\" is illegal\r\n", console_command());
}

static void state_idle(void)
{
	if (!command_received)
		return;

	printf("\r\n");

	num_args = sscanf(console_command(), "%s%s%s%s%s%s%s%s", arg[0], arg[1],
			arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);

	if (num_args <= 0) {
		illegal_command();
	} else {
		--num_args;
		if (!strcmp(arg[0], stopwatch_name())) {
			stopwatch_start();
			state = STATE_STOPWATCH;
		} else {
			illegal_command();
		}
	}
}

static void state_stopwatch(void)
{
	if (stop_received) {
		stopwatch_stop();
		state = STATE_IDLE;
	} else if (!stopwatch_step()) {
		state = STATE_IDLE;
	}
}

void console_command_step(void)
{
	if (command_received && console_stop_received())
		stop_received = true;

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

	stop_received = false; // must have been handled in the state

	if (command_received == true && state == STATE_IDLE) {
		/*
		 * We have received a command. We may or may not have gone through
		 * a state corresponding to the command. In any case, when we are
		 * (back) in the idle state, we have finished handling the command.
		 */
		command_received = false;
		console_command_handled();
	}
}

void console_command_received(void)
{
	command_received = true;
}
