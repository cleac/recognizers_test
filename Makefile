PROJNAME = pattern_test

CFLAGS = -Wall -O0 -std=c++11
CFLAGS_DEBUG = $(CFLAGS) --debug

SRC = main.cpp
DEPS = $(SRC) uwave_recognizer.h

all: $(DEPS)
	$(CXX) -o$(PROJNAME) $(SRC) $(CFLAGS_DEBUG)
	echo "Measuring memory needed by algorythm, time will be uncertain"
	valgrind ./$(PROJNAME)
	echo "Measuring time of algorythm work" 
	./$(PROJNAME)

clean:
	rm $(PROJNAME)
