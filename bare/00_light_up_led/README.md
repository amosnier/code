#Light up LED
##Background
The idea of this application is to light up a LED on the board and enter a for
ever loop. The code is written in assembly language. If the correct LED is lit
forever when running the application, it will be considered successful.
##Which LED?
We use the board's datasheet to select and locate the LED. We select LD3, which
is orange and "connected to the I/O PD13 of the STM32F407VGT6".
We use the MCU's reference manual to understand how we can control I/O PD13 by
software. PD13 is bit 13 in GPIO port D.
