# Include directories to files
inc_dir2file = $(wildcard $(addsuffix /*.h, $(1)))

# Source directories to files
# Warning: *template.c are removed from the list of files since there are such
# files in cube drivers that are user templates and not drivers.
src_dir2file = $(patsubst %template.c, , $(wildcard $(addsuffix /*.[cS], $(1))))

# Source files to object files, including path removal
src2obj = $(patsubst %.S, %.o, $(patsubst %.c, %.o, $(notdir $(1))))
