# Compilador y estándar
CXX         = clang++ -std=c++17

# Flags y librerías
WARN        = -Wall -Wextra -Wcast-align -Wno-sign-compare -Wno-write-strings -Wno-parentheses -Wfloat-equal -pedantic
FLAGS       = -Ofast $(WARN)

# Directorios
LIB         = ./lib
BUILD_DIR   = $(LIB)/obj
DSG         = /home/gustalbert/DeSiGNAR-2.0.0
TESTDIR     = ./test
INCLUDEPATH = -I./include -I$(DSG)/include -I$(LIB)/include


# Archivos y reglas de objeto
INCLUDES    = $(wildcard $(LIB)/include/*.hpp)
SOURCES     = $(wildcard $(LIB)/src/*.cpp)
OBJECTS     = $(SOURCES:$(LIB)/src/%.cpp=$(BUILD_DIR)/%.o)

# Archivo de prueba y ejecutable
GAMETEST    = $(TESTDIR)/src/GameTest.cpp
BIN         = $(TESTDIR)/bin/GameTest

# Librerías de enlace
LIBS        = -L$(LIB) -lDesignar
SFML_LIBS   = -lsfml-graphics -lsfml-window -lsfml-system

# Objetivo principal
all: $(BIN)

# Reglas de compilación de objetos
$(BUILD_DIR)/%.o: $(LIB)/src/%.cpp
	$(CXX) $(FLAGS) $(INCLUDEPATH) -c $< -o $@

# Compilación del ejecutable de prueba
$(BIN): $(BUILD_DIR) $(OBJECTS) $(GAMETEST)
	$(CXX) $(FLAGS) $(INCLUDEPATH) $(GAMETEST) -o $@ $(OBJECTS) $(SFML_LIBS)

# Crear directorio de compilación si no existe
$(BUILD_DIR):
	mkdir -p $@

# Limpieza de archivos compilados
.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)/*.o $(BIN)

