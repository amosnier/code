include ../../mk/functions.mk

# Generate include path flags
INC = $(addprefix -I, $(INC_DIRS))

# Note: SRC_FILES are directly used for tags, while prerequites for binaries use
# object files. The latter allows the use of implicit rules to build object
# files, but requires the use of vpath, since the path information is lost in
# OBJS.
INC_FILES = $(call inc_dir2file, $(INC_DIRS))
SRC_FILES = $(call src_dir2file, $(SRC_DIRS))
OBJS = $(call src2obj, $(SRC_FILES))

# AR_OBJS is used instead of OBJS if we are building a library
AR_OBJS = $(patsubst %.o,$(LIB)(%.o),$(OBJS))

vpath %.c $(SRC_DIRS)
vpath %.S $(SRC_DIRS)
