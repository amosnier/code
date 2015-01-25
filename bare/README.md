#Minimalist bare metal programming from scratch

##Background
Right now, the contents of this directory are based on the STM32F4-Discovery.
The development host is based on Linux.
Minimalist means that I use as few and simple tools as possible to write code,
store code to the board, and test the code (GNU suite, GNU Emacs, GNU make, GDB,
etc.).
The approach is bottom/up, i.e. using the board resources as much as possible
rather than trying to achieve some particular functional goals. The purpose is
learning and creating a clean, simple and effective code base.

##Tools used
As of this commit, the tools I use in the bare project are:
- Host: Manjaro Linux
- Target: STM34F4-Discovery + mini USB cable
- On chip debugger: Open On-Chip Debugger 0.8.0 (openOCD)
- IDE: GNU Emacs 24.4.1 + GNU Make 4.1 + GNU gdb (GNU Tools for ARM Embedded
Processors) 7.8.1.20141128-cvs
- ARM cross toolchain: GNU Tools for ARM Embedded Processors 4.9-2014-q4-major

##Tips
- I find the command "arm-none-eabi-objdump -m _binary_" invaluable to check
that the binary has the correct layout or understand what the compiler is doing.
- GDB in Emacs is not as intuitive as in Eclipse, but it is less complicated to
set up and quite powerful with symbolic breakpoints, etc. Also, the Emacs based
environment takes no time to start, whereas Eclipse takes ages. I use directives
in .emacs and .gdbinit to ease gdb's startup and automate openOCD's start and
connection (see [code](https://github.com/amosnier/code), I have symbolic links
to these file in my home directory). I very often use the following commands
under gdb:
  - monitor reset halt (ask OpenOCD to reset the target)
  - load (write the binary to flash).
  - continue (run the program to the next breakpoint or until I break with C-c
  C-c)
