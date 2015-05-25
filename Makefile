PROJNAME = pattern_test

CFLAGS = -Wall -O0
CFLAGS_C = $(CFLAGS) -std=gnu11 -L. -lanalyzer -lm
CFLAGS_CPP = $(CFLAGS) -std=gnu++11
CFLAGS_DEBUG = $(CFLAGS) --debug

SRC = main.c
DEPS = $(SRC) $(DEPS_ANALYZER)

SRC_ANALYZER = algo_analyzer.cpp fake_templates.c
LIBS_ANALYZER = algo_analyzer.o fake_templates.o
DEPS_ANALYZER = $(SRC_ANALYZER) fake_templates.h algo_analyzer.h

all: analyzer $(DEPS)
	$(CC) -o$(PROJNAME) $(SRC) $(CFLAGS_C) 
	./$(PROJNAME)

analyzer: $(DEPS_ANALYZER)
	$(CXX) -c $(SRC_ANALYZER) $(CFLAGS_CPP)
	ar rcs libanalyzer.a $(LIBS_ANALYZER)

clean:
	rm *.o *.a $(PROJNAME)
