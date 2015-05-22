PROJNAME = pattern_test

CFLAGS = -Wall -O0 -std=c++11
CFLAGS_DEBUG = $(CFLAGS) --debug

SRC = main.cpp
DEPS = $(SRC)

all: $(DEPS)
	$(CXX) -o$(PROJNAME) $(SRC) $(CFLAGS_DEBUG)
	valgrind ./$(PROJNAME)
	./$(PROJNAME)

clean:
	rm $(PROJNAME)
