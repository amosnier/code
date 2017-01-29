#include "console.h"
#include "stopwatch.h"
#include "console_command_table.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <console_command.h>
#include <string.h>

extern const struct Command commands[];
extern const size_t num_commands;

static volatile bool command_received = false;
static bool stop_received = false;

static enum State {
	STATE_IDLE,
	STATE_RUNNING
} state = STATE_IDLE;

/* Warning: size specifier in sscanf further down must be size of argument below minus one! */
char arg[8][17]; // 1 command name + (n - 1) arguments

int num_args = 0;

size_t command_index;

static void illegal_command(void)
{
	printf("\"%s\" is illegal\r\n", console_command());
}

static bool find_command(size_t *index, const char *name)
{
	for (*index = 0; *index < num_commands; ++*index) {
		if (!strcmp(name, commands[*index].name)) {
			break;
		}
	}
	return *index < num_commands;
}

static void state_idle(void)
{
	if (!command_received)
		return;

	printf("\r\n");

	/* Warning: size specifier below must be size of argument above minus one! */
	num_args = sscanf(console_command(), "%16s%16s%16s%16s%16s%16s%16s%16s", arg[0], arg[1],
			arg[2], arg[3], arg[4], arg[5], arg[6], arg[7]);

	if (num_args <= 0) {
		illegal_command();
	} else {
		--num_args;
		if (find_command(&command_index, arg[0])) {
			commands[command_index].start();
			state = STATE_RUNNING;
		} else {
			illegal_command();
		}
	}
}

static void state_running(void)
{
	if (stop_received) {
		commands[command_index].stop();
		state = STATE_IDLE;
	} else if (!commands[command_index].step()) {
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
	case STATE_RUNNING:
		state_running();
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

const char * console_command_arg(size_t index)
{
	assert(index < (size_t) num_args);
	return arg[index + 1];
}

int console_command_num_args(void)
{
	return num_args;
}
