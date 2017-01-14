#ifndef CONSOLE_H
#define CONSOLE_H

void console_init(void);
void console_print_welcome(void);
void console_receive_char(void);
void console_start_rx(void);
void console_handle_rx_event(void);

#endif // CONSOLE_H
