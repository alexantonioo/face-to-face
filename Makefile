CXX         = clang++ -std=c++17
WARN        = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wfloat-equal -pedantic

# Libs
LIB         = ./lib
INCLUDES    = $(wildcard $(LIB)/include/*.hpp)
SOURCES     = $(wildcard $(LIB)/src/*.cpp)
OBJECTS     = $(SOURCES:$(LIB)/src/%.cpp=$(LIB)/obj/%.o)

# Test
TESTDIR     = ./test
TEST        = $(wildcard $(TESTDIR)/src/*.cpp)
MKTEST      = $(TEST:$(TESTDIR)/src/%.cpp=$(TESTDIR)/bin/%)

INCLUDEPATH = -I$(LIB)/include

FLAGS       = -Ofast $(WARN)

# SFML Libraries
SFML_LIBS   = -lsfml-graphics -lsfml-window -lsfml-system

all: test

$(LIB)/obj/%.o : $(LIB)/src/%.cpp
	$(CXX) $(FLAGS) $(INCLUDEPATH) -c $< -o $@

$(TESTDIR)/bin/%: $(TESTDIR)/src/%.cpp $(OBJECTS)
	$(CXX) $(FLAGS) $(INCLUDEPATH) $< -o $@ $(OBJECTS) $(SFML_LIBS)

test: $(TEST) $(INCLUDES) $(SOURCES) $(MKTEST)

.PHONY:
clean:
	$(RM) $(MKTEST)
