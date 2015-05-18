PROJNAME = pattern_test

CFLAGS = -Wall -O0 -std=c++11
CFLAGS_DEBUG = $(CFLAGS) --debug

SRC = main.cpp recognizer.cpp
DEPS = $(SRC) recognizer.h

all: $(DEPS)
	$(CXX) -o$(PROJNAME) $(SRC) $(CFLAGS_DEBUG)
	./$(PROJNAME)

clean:
	rm $(PROJNAME)
