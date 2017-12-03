# Generic application Makefile for Cortex-M4. The actual Makefile should be a
# symlink to this, and application specifics should be defined in specs.mk to be
# located in the same directory as the Makefile.

# Paths from base for convenience. Can be used in specs.mk. But specs.mk must
# define BASE, since the file supports building from arbitrary relative
# positions in the file tree.
SHARED = $(BASE)/src/shared
CUBE = $(SHARED)/stm32cubef4
BOARDS = $(SHARED)/boards
MCUS = $(SHARED)/mcus

include specs.mk

# Evaluated immediately, do not execute earlier!
include $(BASE)/mk/vpath.mk

include $(BASE)/mk/calc_files.mk

CC = arm-none-eabi-gcc

# MCU flags
ARCH_FLAGS = -mthumb -mcpu=cortex-m4

## STM32Cube HAL flags
HAL_FLAGS = -DUSE_HAL_DRIVER -D$(MCU)

# Use newlib-nano. To disable it, specify USE_NANO=
USE_NANO = -specs=nano.specs

# Create include dependency files
DEP_FLAGS = -MD -MP

# Use semihosting or not
USE_SEMIHOST = -specs=rdimon.specs
USE_NOHOST = -specs=nosys.specs

SPEC_FLAGS = $(USE_NANO) $(USE_NOHOST) -D__STARTUP_CLEAR_BSS -D__START=main

# Garbage collect unused sections
GC=-Wl,--gc-sections

# Create map file
MAP=-Wl,-Map=$(EXE).map

# CPPFLAGS are passed both to the compiler and the assembler (but not the linker)
COMMON_FLAGS = $(DEP_FLAGS) $(SPEC_FLAGS) $(ARCH_FLAGS) -g -Wall
CPPFLAGS = $(HAL_FLAGS) $(INC) $(COMMON_FLAGS)
CFLAGS = -std=c11
LDFLAGS = -L$(BASE)/ldscripts -T script.ld $(GC) $(MAP) $(SPEC_FLAGS) -g


# Actual build rules: clean and simple (using GNU Make implicit rules)

.PHONY: all
all: $(EXE)

$(EXE): $(OBJS)

-include $(DEPS)

.PHONY: clean
clean:
	rm -f $(EXE) *.o *.d *.map *~

.PHONY: show
show:
	@echo '$(OBJS)'
