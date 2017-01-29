#ifndef APPLICATION_CONSOLE_COMMAND_TABLE_H_
#define APPLICATION_CONSOLE_COMMAND_TABLE_H_

#include <stdbool.h>
#include <stddef.h>

struct Command {
	const char * name;
	void (*start)(void);
	bool (*step)(void);
	void (*stop)(void);
};

#endif /* APPLICATION_CONSOLE_COMMAND_TABLE_H_ */
