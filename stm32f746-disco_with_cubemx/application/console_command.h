#ifndef APPLICATION_CONSOLE_COMMAND_H_
#define APPLICATION_CONSOLE_COMMAND_H_

#include <stddef.h>

void console_command_received(void);
void console_command_step(void);
const char * console_command_arg(size_t index);
int console_command_num_args(void);

#endif /* APPLICATION_CONSOLE_COMMAND_H_ */
