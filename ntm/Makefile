APPS = ntm

CXXFLAGS = -Wall -std=c++11
LDLIBS = -lboost_system -lboost_filesystem

$(APPS):

ntm: ntm_interpreter.cpp ntm_interpreter.hpp ntm.cpp

.PHONY: clean
clean:
	rm -f $(APPS)
