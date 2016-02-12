#include "fault.h"
#include <stdbool.h>
#include <stdio.h>

void halt(const char* file, int line)
{
	static bool been_here_before = false;
	if (!been_here_before)
	{
		been_here_before = true;
		printf("Halted: file %s, line %d\r\n", file, line);
	}
	while (true)
		;
}
