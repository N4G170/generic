#Project Euler Makefile

#paths
SRC_BASE_PATH=src/base/
SRC_SNAKE_PATH=src/snake/
SRC_RAIN_PATH=src/rain/
SRC_SOLAR_PATH=src/solar/
SRC_GRID_MAP_PATH=src/a_star_map_demo/
SRC_INFLUENCE_WARS_PATH=src/influence_wars/
SRC_GUI_PATH=src/sdl_gui/

OBJ_PATH=objects/
GUI_OBJ_PATH=objects/gui/
GUI_OBJ_DIR=objects/gui/
BIN_PATH=./
EXEC_FILE=generic_sdl

#include directories
INCLUDE=-Isrc/base/ -Isrc/rain/ -Isrc/snake/ -Isrc/solar/ -Isrc/a_star_map_demo/ -Isrc/influence_wars -Isrc/sdl_gui

#c++ compiler
CXX=g++

#c++ compile flags
CXXFLAGS=-c -g -Wall -std=c++11 $(INCLUDE)
#Linker flags
LDFLAGS=-lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image -pthread

#files
SRC_BASE_FILES:=$(wildcard $(SRC_BASE_PATH)*.cpp)
SRC_SNAKE_FILES:=$(wildcard $(SRC_SNAKE_PATH)*.cpp)
SRC_RAIN_FILES:=$(wildcard $(SRC_RAIN_PATH)*.cpp)
SRC_SOLAR_FILES:=$(wildcard $(SRC_SOLAR_PATH)*.cpp)
SRC_GRID_MAP_FILES:=$(wildcard $(SRC_GRID_MAP_PATH)*.cpp)
SRC_INFLUENCE_WARS_FILES:=$(wildcard $(SRC_INFLUENCE_WARS_PATH)*.cpp)
SRC_GUI_FILES:=$(wildcard $(SRC_GUI_PATH)*.cpp)

BASE_OBJECTS:=$(patsubst $(SRC_BASE_PATH)%.cpp,$(OBJ_PATH)%.o,$(wildcard $(SRC_BASE_PATH)*.cpp))
SNAKE_OBJECTS:=$(patsubst $(SRC_SNAKE_PATH)%.cpp,$(OBJ_PATH)%.o,$(wildcard $(SRC_SNAKE_PATH)*.cpp))
RAIN_OBJECTS:=$(patsubst $(SRC_RAIN_PATH)%.cpp,$(OBJ_PATH)%.o,$(wildcard $(SRC_RAIN_PATH)*.cpp))
SOLAR_OBJECTS:=$(patsubst $(SRC_SOLAR_PATH)%.cpp,$(OBJ_PATH)%.o,$(wildcard $(SRC_SOLAR_PATH)*.cpp))
GRID_MAP_OBJECTS:=$(patsubst $(SRC_GRID_MAP_PATH)%.cpp,$(OBJ_PATH)%.o,$(wildcard $(SRC_GRID_MAP_PATH)*.cpp))
INFLUENCE_WARS_OBJECTS:=$(patsubst $(SRC_INFLUENCE_WARS_PATH)%.cpp,$(OBJ_PATH)%.o,$(wildcard $(SRC_INFLUENCE_WARS_PATH)*.cpp))
GUI_OBJECTS:=$(patsubst $(SRC_GUI_PATH)%.cpp,$(GUI_OBJ_PATH)%.o,$(wildcard $(SRC_GUI_PATH)*.cpp))

#recipes - this method only recompiles changed files
all: build | $(GUI_OBJ_DIR)

build:$(BASE_OBJECTS) $(SNAKE_OBJECTS) $(RAIN_OBJECTS) $(SOLAR_OBJECTS) $(GRID_MAP_OBJECTS) $(INFLUENCE_WARS_OBJECTS) $(GUI_OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJ_PATH)*.o $(GUI_OBJ_PATH)*.o -o $(BIN_PATH)$(EXEC_FILE)

$(GUI_OBJ_DIR) :
	mkdir -p $(GUI_OBJ_PATH)

$(BASE_OBJECTS):$(OBJ_PATH)%.o:$(SRC_BASE_PATH)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
$(SNAKE_OBJECTS):$(OBJ_PATH)%.o:$(SRC_SNAKE_PATH)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
$(RAIN_OBJECTS):$(OBJ_PATH)%.o:$(SRC_RAIN_PATH)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
$(SOLAR_OBJECTS):$(OBJ_PATH)%.o:$(SRC_SOLAR_PATH)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
$(GRID_MAP_OBJECTS):$(OBJ_PATH)%.o:$(SRC_GRID_MAP_PATH)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
$(INFLUENCE_WARS_OBJECTS):$(OBJ_PATH)%.o:$(SRC_INFLUENCE_WARS_PATH)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
$(GUI_OBJECTS):$(GUI_OBJ_PATH)%.o:$(SRC_GUI_PATH)%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm $(OBJ_PATH)*.o $(GUI_OBJ_PATH)*.o $(EXEC_FILE)
