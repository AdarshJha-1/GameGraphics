# Compilers
CXX = g++

# Flags: Includes both 'include' and 'include/imgui'
CXXFLAGS = -Wall -std=c++11 -Iinclude -Iinclude/imgui

# Framework and OS Libraries (Configured for Linux)
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# For macOS: LIBS = -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Output Folders
OBJ_DIR = obj
BIN_DIR = bin

# Target Executable Path
TARGET = $(BIN_DIR)/main

# Source files mapping your exact layout
SRCS = src/main.cpp \
       src/MP3MusicMetadata.cpp \
       imgui/imgui.cpp \
       imgui/imgui_demo.cpp \
       imgui/imgui_draw.cpp \
       imgui/imgui_tables.cpp \
       imgui/imgui_widgets.cpp \
       imgui/rlImGui.cpp


# Map source file paths to the obj/ folder structure
# Example: src/main.cpp -> obj/src/main.o, imgui/imgui.cpp -> obj/imgui/imgui.o
OBJS = $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# Default build rule
all: $(TARGET)

# Final linking step (links objects from obj/ into bin/)
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Compilation rule for all C++ objects (places them inside obj/ mirroring the source paths)
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Deep clean rule to clear build folders completely
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean
