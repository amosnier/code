CC = arm-none-eabi-gcc

EXE = app

BASE=../..

ARCH_FLAGS = -mthumb -mcpu=cortex-m4

# Use newlib-nano. To disable it, specify USE_NANO=
USE_NANO = -specs=nano.specs

# Use semihosting or not
USE_SEMIHOST = -specs=rdimon.specs
USE_NOHOST = -specs=nosys.specs

SPEC_FLAGS = $(USE_NANO) $(USE_NOHOST)

# Garbage collect unused sections
GC=-Wl,--gc-sections

# Create map file
MAP=-Wl,-Map=$(EXE).map

# Create include dependency files
DEP_FLAGS = -MD -MP

# CPPFLAGS are passed both to the compiler and the assembler (but not the linker)
CPPFLAGS = -D__NO_SYSTEM_INIT $(DEP_FLAGS) $(SPEC_FLAGS) $(ARCH_FLAGS) -g -Wall
LDFLAGS= -L$(BASE)/ldscripts -T script.ld $(GC) $(MAP) $(SPEC_FLAGS) -g

OBJS += startup_ARMCM4.o $(patsubst %.c,%.o,$(wildcard *.c))

SOURCE_PATH = $(BASE)/startup:.

vpath %.c $(SOURCE_PATH)
vpath %.S $(SOURCE_PATH)

$(EXE): $(OBJS)

.PHONY: clean
clean:
	rm -f $(EXE) *.o *.d *.map *~

.PHONY: show
show:
	@echo $(OBJS)
