#Serial console program on STM32F4-Discovery
Based on CubeMX with a configured USART2 on PA2 and PA3. I use a UART to USB
adapter cable based on a Prolific 2303HX chip. It pops up automatically under
/dev and cu works as a terminal emulator pretty much out of the box (I had to
add myself to the dialout group and to logout and login again to make it work). 
