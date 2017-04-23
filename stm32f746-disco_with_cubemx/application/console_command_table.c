#include "console_command_table.h"
#include "stopwatch.h"

const Command commands[] = {
		{"stopwatch", stopwatch_start, stopwatch_step, stopwatch_stop}
};

const size_t num_commands = sizeof commands / sizeof (Command);
