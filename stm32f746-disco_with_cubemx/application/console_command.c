#include "console.h"
#include "stopwatch.h"
#include "console_command_table.h"

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <console_command.h>
#include <string.h>

extern const Command commands[];
extern const size_t num_commands;

static const Command *command;

static bool illegal_step(void);

static Command illegal_command = {
		"illegal", NULL, illegal_step, NULL
};

static Command empty_command = {
		"empty", NULL, NULL, NULL
};

static volatile bool command_received = false;

static enum State {
	STATE_IDLE,
	STATE_RUNNING
} state = STATE_IDLE;

/* Warning: size specifier in sscanf further down must be size of argument below minus one! */
char arg[8][17]; // 1 command name + (n - 1) arguments

int num_args = 0;

size_t command_index;

static bool illegal_step(void)
{
	printf("\"%s\" is illegal\r\n", console_command());
	return false;
}

static const Command *find_command(const char *name)
{
	if (*name == 0)
		return &empty_command;

	const Command *cmd = &illegal_command;

	for (size_t i = 0; i < num_commands; i++) {
		if (!strcmp(name, commands[i].name)) {
			cmd = &commands[i];
			break;
		}
	}

	return cmd;
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
		arg[0][0] = 0; // empty command ("")
		num_args = 0;
	} else {
		--num_args;
	}

	command = find_command(arg[0]);

	if (command->start != NULL)
		command->start();

	state = STATE_RUNNING;
}

static void state_running(void)
{
	if (console_stop_received()) {
		if (command->stop != NULL)
			command->stop();
		state = STATE_IDLE;
	} else if (command->step == NULL || !command->step()) {
		state = STATE_IDLE;
	}

	if (state == STATE_IDLE) {
		command_received = false;
		console_command_handled();
	}
}

void console_command_step(void)
{
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
