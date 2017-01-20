#ifndef CONSOLE_H
#define CONSOLE_H

void console_init(void);
void console_print_welcome(void);
void console_receive_completed(void);
void console_receive_char(void);

inline void console_transmit_completed(void)
{
	console_receive_char();
}

#endif // CONSOLE_H
