include $(BASE)/mk/functions.mk

# Generate include path flags
INC = $(addprefix -I, $(INC_DIRS))

SRC_FILES = $(SRC_ADD_FILES)
SRC_FILES += $(call src_dir2file, $(SRC_DIRS))
OBJS = $(call src2obj, $(SRC_FILES))
DEPS = $(call obj2dep, $(OBJS))
