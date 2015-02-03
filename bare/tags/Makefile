CUBE_SOURCES = $(shell find ../stm32cube/ -name "*.[ch]")
SOURCES = $(shell find .. -name "*.[ch]")

TAGS: cube.tags $(SOURCES)
	etags $(SOURCES) -i cube.tags

cube.tags: $(CUBE_SOURCES)
	etags $^ -o $@

.PHONY: clean
clean:
	rm -f cube.tags TAGS *~

.PHONY: show
show:
	@echo $(CUBE_SOURCES)
	@echo $(SOURCES)
