TAGS: $(shell find $(INC_DIRS) -name "*.[h]") $(shell find $(SRC) -name "*.[Sc]")
	etags $^
