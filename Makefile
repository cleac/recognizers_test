PROJNAME = pattern_test

CFLAGS = -Wall -O0 -std=c++11
CFLAGS_DEBUG = $(CFLAGS) --debug

SRC = main.cpp fake_templates.c 
DEPS = $(SRC) fake_templates.h memory_counter.h

all: $(DEPS)
	$(CXX) -o$(PROJNAME) $(SRC) $(CFLAGS)
	./$(PROJNAME)

clean:
	rm $(PROJNAME)
