EXE = program

CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

CCFLAGS = -mthumb -mcpu=cortex-m4 -g
ASFLAGS = $(CCFLAGS)
LDFLAGS = -T script.ld

.PHONY: all
all: $(EXE).elf

%.elf: %.o
	$(LD) $(LDFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.elf *.o *.s *~
