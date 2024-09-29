CXX         = clang++ -std=c++17
WARN        = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wfloat-equal -pedantic

# Libs
LIB         = ./lib
INCLUDES    = $(wildcard $(LIB)/include/*.hpp)
SOURCES     = $(wildcard $(LIB)/src/*.cpp)
OBJECTS     = $(SOURCES:$(LIB)/src/%.cpp=$(LIB)/obj/%.o)

# Test
TESTDIR     = ./test
GAMETEST    = $(TESTDIR)/src/GameTest.cpp
BIN         = $(TESTDIR)/bin/GameTest

INCLUDEPATH = -I$(LIB)/include

FLAGS       = -Ofast $(WARN)

# SFML Libraries
SFML_LIBS   = -lsfml-graphics -lsfml-window -lsfml-system

all: $(BIN)

$(LIB)/obj/%.o : $(LIB)/src/%.cpp
	$(CXX) $(FLAGS) $(INCLUDEPATH) -c $< -o $@

$(BIN): $(GAMETEST) $(OBJECTS)
	$(CXX) $(FLAGS) $(INCLUDEPATH) $< -o $@ $(OBJECTS) $(SFML_LIBS)

.PHONY: clean
clean:
	$(RM) $(LIB)/obj/*.o $(BIN)
