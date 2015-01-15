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