include $(BASE)/mk/functions.mk

# Generate include path flags
INC = $(addprefix -I, $(INC_DIRS))

SRC_FILES += $(call src_dir2file, $(SRC_DIRS))
OBJS = $(call src2obj, $(SRC_FILES))
DEPS = $(call obj2dep, $(OBJS))

# AR_OBJS is used instead of OBJS if we are building a library
AR_OBJS = $(patsubst %.o,$(LIB)(%.o),$(OBJS))
