# Path relative to including Makefile at ../dir1/dir2/!
include ../../mk/env.mk

# Include dirs
INCLUDE_DIRS = \
-I. \
-I$(DRIVERS)/STM32F4xx_HAL_Driver/Inc \
-I$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
-I$(DRIVERS)/CMSIS/Include \

# Source dirs
SOURCES = \
.:\
$(DRIVERS)/STM32F4xx_HAL_Driver/Src:\

vpath %.c $(SOURCES)

# Object files for archive, removing template files
SRC = $(patsubst %template.c,,$(notdir $(wildcard $(DRIVERS)/STM32F4xx_HAL_Driver/Src/*.c)))
OBJS = $(patsubst %.c,%.o,$(SRC))
AR_OBJS = $(patsubst %.o,$(LIB)(%.o),$(OBJS))

# CPPFLAGS are passed both to the compiler and the assembler (but not the linker)
COMMON_FLAGS = $(DEP_FLAGS) $(ARCH_FLAGS) -g -Wall
CPPFLAGS = $(HAL_FLAGS) $(INCLUDE_DIRS) $(COMMON_FLAGS)

# Dependencies and rules, using GNU make implicits as much as possible
$(LIB): $(AR_OBJS)
	$(RANLIB) $@

.PHONY: clean
clean:
	rm -f $(LIB) *.o *.d *~

.PHONY: show
show:
	@echo '$(OBJS)'
	@echo '$(AR_OBJS)'
