# =========================================================
# Makefile for Smart Student Placement Management System
# Works with MinGW GCC on Windows (mingw32-make) and Linux/macOS (make)
# =========================================================

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
SRC_DIR = src
OBJ_DIR = obj

# Automatically picks up every .c file inside src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TARGET = placement_system.exe

# ---- OS detection so mkdir/rm work on both Windows (cmd.exe) and Linux ----
ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)
    CLEAN = if exist $(OBJ_DIR) del /Q $(OBJ_DIR)\*.o & if exist $(TARGET) del /Q $(TARGET)
else
    MKDIR = mkdir -p $(OBJ_DIR)
    CLEAN = rm -f $(OBJ_DIR)/*.o $(TARGET)
endif

# Default target: build everything
all: $(OBJ_DIR) $(TARGET)

# Link all object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	@echo Build complete: $(TARGET)

# Compile each .c file into a .o object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create the obj/ directory if it doesn't exist
$(OBJ_DIR):
	$(MKDIR)

# Remove all build artifacts
clean:
	$(CLEAN)

.PHONY: all clean
