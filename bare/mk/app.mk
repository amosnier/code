# Path relative to including Makefile at ../dir1/dir2/!
include ../../mk/env.mk

EXE = app

LIB_HAL_DIR = $(BASE)/lib/lib$(LIB_HAL)

TAGS = $(BASE)/tags

INC_DIRS = \
. \
$(BASE)/common/bsp \
$(BASE)/common/init \
$(LIB_HAL_DIR) \
$(DRIVERS)/BSP/STM32F4-Discovery \
$(DRIVERS)/STM32F4xx_HAL_Driver/Inc \
$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
$(DRIVERS)/CMSIS/Include \

# Include dirs
INC = $(addprefix -I, $(INC_DIRS))

# Source dirs
SRC = \
. \
$(BASE)/startup \
$(BASE)/common/init \

vpath %.c $(SRC)
vpath %.S $(SRC)

# Object files
OBJS = \
$(patsubst %.c,%.o,$(wildcard *.c)) \
startup_ARMCM4.o \
$(patsubst %.c,%.o,$(notdir $(wildcard $(BASE)/common/init/*.c))) \

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
LDLIBS = -L$(LIB_HAL_DIR) -l$(LIB_HAL)
LDFLAGS = -L$(BASE)/ldscripts -T script.ld $(GC) $(MAP) $(SPEC_FLAGS) -g

# Dependency on phony prerequesites ensures that we try to rebuild them every
# time, letting the respective Makefiles decide whether they actually need to be
# rebuilt or not.
.PHONY: all
all: $(LIB_HAL) $(EXE) TAGS

# Dependencies and rules, using GNU make implicits as much as possible
$(EXE): $(OBJS)

.PHONY: $(LIB_HAL)
$(LIB_HAL):
	make -C $(LIB_HAL_DIR)

TAGS: $(shell find $(INC_DIRS) -name "*.[h]") $(shell find $(SRC) -name "*.[Sc]")
	etags $^ -i $(LIB_HAL_DIR)/TAGS

.PHONY: clean
clean:
	rm -f $(EXE) *.o *.d *.map *~ TAGS

.PHONY: show
show:
	@echo '$(OBJS)'
