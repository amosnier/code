#Blink LED

##Background
The idea of this application is to build on top of the previous light up LED
project, developing it in two ways:
- Let the reset handler branch to C code as soon as possible.
- Let the C code blink the LED at an arbitrary but visible fixed frequency.

##C-runtime environment
In order to support C's features, C compilers and linkers assume the presence of
a stack, a so-called BSS-segment in RAM (static variables initialized to zero)
and a data segment, also in RAM. Code using these is usually located by some
library files delivered with the compiler and linked in the executable
(e.g. crt0.o).
We do initialize the stack pointer to the top of the RAM (it grows downwards),
by emitting that address to at address 0 as required for Cortex-M4, but since we
do not so far need any static in RAM, we decide to simplify the linker script by
skipping the BSS and data segments. In order to achieve this, we invoke gcc with
the option -nostartfiles.
