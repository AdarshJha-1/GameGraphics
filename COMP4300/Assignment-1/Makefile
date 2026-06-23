PROJECTNAME = prog
OUTPUT_DIR = build

CXX = g++
CXXFLAGS = -std=c++17 -Iinclude/imgui $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)

SRC = $(wildcard src/*.cpp) $(wildcard imgui/*.cpp)

default:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(LDFLAGS)

run:
	./build/prog