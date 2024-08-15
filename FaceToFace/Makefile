CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = test

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/main
TEST_TARGET = $(BIN_DIR)/test

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TEST_TARGET): $(OBJ_DIR)/Game.o $(TEST_DIR)/GameTest.cpp
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
