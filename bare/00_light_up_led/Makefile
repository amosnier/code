EXE = program

CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

ASFLAGS = -mthumb -mcpu=cortex-m4 -g
CFLAGS = $(ASFLAGS)
LDFLAGS = -nostartfiles -T script.ld

.PHONY: all
all: $(EXE)

.PHONY: clean
clean:
	rm -f $(EXE) *.o *.s *~
