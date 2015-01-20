#Light up LED
##Background
The idea of this application is to light up a LED on the board and enter a for
ever loop. The code is written in assembly language. If the correct LED is lit
forever when running the application, it will be considered successful.
##Which LED?
We use the board's datasheet to select and locate the LED. We select LD3, which
is orange and "connected to the I/O PD13 of the STM32F407VGT6".
We use the MCU's datasheet and reference manual to understand how we can control
I/O PD13 by software. PD13 is bit 13 in GPIO port D.
In order to light it up, we need to:
- Write 8 (IO port D clock enabled) to address 0x4002 3830 (RCC AHB1 peripheral
reset register).
- Write 0x0400 0000 (General purpose output mode for I/O 13) to address
0x4002 0c00 (GPIO D port mode register).
- Write 0x2000 (I/O 13 1) to address 0x4002 0C14 (GPIO D port output data register).
