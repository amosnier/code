CC = arm-none-eabi-gcc

CPPFLAGS = -mthumb -mcpu=cortex-m4 -g
CFLAGS = -std=c11
LDFLAGS = -nostartfiles -T script.ld

app: vectors.S

.PHONY: clean
clean:
	rm -f app *~
