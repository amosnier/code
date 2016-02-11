#Serial console program on STM32F4-Discovery
Based on CubeMX with a configured USART2 on PA2 and PA3. I use a UART to USB
adapter cable based on a Prolific 2303HX chip. It pops up automatically under
/dev and cu works as a terminal emulator pretty much out of the box (I had to
add myself to the dialout group and to logout and login again to make it work). 

At the time of writing, this program only outputs "baresh>" prompts (for bare 
shell) any time the user presses the button B1. I will probably leave it as is
and move on to a more ambitious application that tests the capabilities of the
STM32F4-Discovery with the help of console commands.
