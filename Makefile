CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude

SRC_DIR = src
APP_DIR = app
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objects

TARGET = $(BUILD_DIR)/db

# All .c files inside src/
SRCS = $(wildcard $(SRC_DIR)/*.c)

# All .o files from src/
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Main file
MAIN = $(APP_DIR)/main.c
MAIN_OBJ = $(OBJ_DIR)/main.o

# Default target
all: $(TARGET)

# Link everything
$(TARGET): $(OBJ_DIR) $(OBJS) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(MAIN_OBJ) -o $(TARGET)

# Compile .c files inside src/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c separately
$(OBJ_DIR)/main.o: $(MAIN) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure build/objects exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
