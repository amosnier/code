inc_dir2file = $(wildcard $(addsuffix /*.h, $(1)))

# Warning: *template.c are removed from the list of files since there are such
# files in cube drivers that are user templates and not drivers.
src_dir2file = $(patsubst %template.c,,$(wildcard $(addsuffix /*.[cS], $(1))))
