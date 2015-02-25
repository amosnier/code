include specs.mk
include $(BASE)/mk/common.mk
include $(BASE)/mk/calc_files.mk
include $(BASE)/mk/vpath.mk

# CPPFLAGS are passed both to the compiler and the assembler (but not the linker)
COMMON_FLAGS = $(DEP_FLAGS) $(ARCH_FLAGS) -g -Wall
CPPFLAGS = $(HAL_FLAGS) $(INC) $(COMMON_FLAGS)

.PHONY: all
all: $(LIB)

$(LIB): $(AR_OBJS)
	$(RANLIB) $@

.PHONY: clean
clean:
	rm -f $(LIB) *.o *.d *~

.PHONY: show
show:
	@echo '$(OBJS)'
	@echo '$(AR_OBJS)'
