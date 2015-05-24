PROJNAME = pattern_test

CFLAGS = -Wall -O0 -std=c++11
CFLAGS_DEBUG = $(CFLAGS) --debug

SRC = main.cpp criteria_state.c
DEPS = $(SRC) criteria_state.h

all: $(DEPS)
	$(CXX) -o$(PROJNAME) $(SRC) $(CFLAGS_DEBUG)
	# Measuring memory needed by algorythm, time will be uncertain
	valgrind ./$(PROJNAME)
	# Measuring time of algorythm work
	./$(PROJNAME)

clean:
	rm $(PROJNAME)
