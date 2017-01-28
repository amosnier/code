#ifndef APPLICATION_CONSOLE_H_
#define APPLICATION_CONSOLE_H_

#include <stdbool.h>

void console_init(void);
void console_print_welcome(void);
void console_receive_completed(void);
void console_receive_char(void);
void console_command_handled(void);
const char * console_command(void);
bool console_stop_received(void);
void console_hide_cursor(void);
void console_show_cursor(void);

inline void console_transmit_completed(void)
{
	console_receive_char();
}

#endif // APPLICATION_CONSOLE_H_
