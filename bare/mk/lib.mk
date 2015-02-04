include ../../mk/common.mk
include specs.mk
include ../../mk/calcfiles.mk

# CPPFLAGS are passed both to the compiler and the assembler (but not the linker)
COMMON_FLAGS = $(DEP_FLAGS) $(ARCH_FLAGS) -g -Wall
CPPFLAGS = $(HAL_FLAGS) $(INC) $(COMMON_FLAGS)

.PHONY: all
all: $(LIB) TAGS

# Dependencies and rules, using GNU make implicits as much as possible
$(LIB): $(AR_OBJS)
	$(RANLIB) $@

TAGS: $(INC_FILES) $(SRC_FILES)
	etags $^

.PHONY: clean
clean:
	rm -f $(LIB) *.o *.d *~ TAGS

.PHONY: show
show:
	@echo '$(OBJS)'
	@echo '$(AR_OBJS)'
