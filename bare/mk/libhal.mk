# Path relative to including Makefile at ../dir1/dir2/!
include ../../mk/env.mk

# INC_DIRS, also required by tags.mk!
INC_DIRS = \
. \
$(DRIVERS)/STM32F4xx_HAL_Driver/Inc \
$(DRIVERS)/CMSIS/Device/ST/STM32F4xx/Include \
$(DRIVERS)/CMSIS/Include \

# Include dirs
INC = $(addprefix -I, $(INC_DIRS))

# SRC, also required by tags.mk!
SRC = \
$(DRIVERS)/STM32F4xx_HAL_Driver/Src \

vpath %.c $(SRC)

# Object files for archive, removing template files
SRC_FILES = $(patsubst %template.c,,$(notdir $(wildcard $(DRIVERS)/STM32F4xx_HAL_Driver/Src/*.c)))
OBJS = $(patsubst %.c,%.o,$(SRC_FILES))

include ../../mk/lib.mk
