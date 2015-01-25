EXE = program

CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

ASFLAGS = -mthumb -mcpu=cortex-m4 -g
CFLAGS = $(ASFLAGS) -std=c11
LDFLAGS = -nostartfiles -T script.ld

.PHONY: all
all: $(EXE)

$(EXE): vectors.S

.PHONY: clean
clean:
	rm -f $(EXE) *.o *.s *~
