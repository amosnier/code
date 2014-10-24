SPACE =
SPACE +=
ifeq ($(EXE),)
  CUR_PATH_NAMES = $(subst /,$(SPACE),$(subst $(SPACE),_,$(CURDIR)))
  EXE = $(word $(words $(CUR_PATH_NAMES)),$(CUR_PATH_NAMES))
  ifeq ($(EXE),)
    EXE = a.out
  endif
endif

DEP_FLAGS = -MD -MP
CPPFLAGS = $(DEP_FLAGS) $(DEBUG_FLAGS) -Wall -std=c++11
CXXFLAGS = -g -O3
LDLIBS = -lX11 -lGL -lGLEW

SRC = $(wildcard *.cpp)
OBJS = $(SRC:%.cpp=%.o)
DEPS = $(SRC:%.cpp=%.d)

$(EXE): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

run: $(EXE)
	./$^

debug: DEBUG_FLAGS=-DDEBUG

debug: $(EXE)

run_debug: DEBUG_FLAGS=-DDEBUG

run_debug: run

-include $(DEPS)

.PHONY: clean
clean:
	rm -f *.d *.o $(EXE) *~

.PHONY: show
show:
	@echo 'EXE:' $(EXE)
