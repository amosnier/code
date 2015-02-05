include target.mk
include ../../mk/common.mk
include ../../mk/calc_files.mk

EXE = app

LIB_HAL_DIR = $(BASE)/lib/lib$(LIB_HAL)

INC_DIRS = \
. \
$(BASE)/common/bsp \
$(BASE)/common/init \
$(LIB_HAL_DIR) \
$(DRIVERS)/BSP/STM32F4-Discovery \
$(DRIVERS)/STM32F4xx_HAL_Driver/Inc \
$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
$(DRIVERS)/CMSIS/Include \

SRC_DIRS = \
. \
$(BASE)/startup \
$(BASE)/common/init \

# Immediate evaluation, must be done here, not earlier!
include ../../mk/vpath.mk

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

.PHONY: all
all: $(EXE) TAGS

# Note: implicit rule won't work here because of the lib dependency
$(EXE): $(OBJS) $(LIB_HAL)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $@

.PHONY: $(LIB_HAL)
$(LIB_HAL):
	make -C $(LIB_HAL_DIR)

TAGS: $(INC_FILES) $(SRC_FILES)
	etags $^ -i $(LIB_HAL_DIR)/TAGS

.PHONY: clean
clean:
	rm -f $(EXE) *.o *.d *.map *~ TAGS

.PHONY: show
show:
	@echo '$(OBJS)'
