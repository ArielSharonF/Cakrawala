# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -I./include

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files and output binary
SRC_FILES = $(SRC_DIR)/main.cpp $(SRC_DIR)/item.cpp  $(SRC_DIR)/util.cpp $(SRC_DIR)/transaction.cpp $(SRC_DIR)/menu.cpp $(SRC_DIR)/goods-transaction.cpp 
OUTPUT = $(BUILD_DIR)/RMS

# OS detection
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    # Linux specific settings
else
    # Windows specific settings
    OUTPUT = $(BUILD_DIR)/RMS.exe
endif

# Default target
all: $(OUTPUT)

# Build target
$(OUTPUT): $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Clean up
clean:
	rm -f $(OUTPUT)

.PHONY: all clean
