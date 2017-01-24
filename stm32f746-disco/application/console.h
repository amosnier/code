#ifndef APPLICATION_CONSOLE_H_
#define APPLICATION_CONSOLE_H_

void console_init(void);
void console_print_welcome(void);
void console_receive_completed(void);
void console_receive_char(void);
void console_check_and_handle_command(void);

inline void console_transmit_completed(void)
{
	console_receive_char();
}

#endif // APPLICATION_CONSOLE_H_
