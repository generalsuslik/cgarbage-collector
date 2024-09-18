CC = gcc
CC_FLAGS = -g -Wall -Werror

TARGET = cgc

SRC_DIR = src
BIN_DIR = bin

SOURCES = $(SRC_DIR)/*c

DEL_FILE = rm -rf
LIBS_DIR = -I/.include
LIBS = $(LIBS_DIR) -lc

.PHONY: clean build
all: build

build: $(SOURCE)
	$(CC) $(CC_FLAGS) $(LIBS) $(SOURCES) -o $(BIN_DIR)/$(TARGET)

run:
	./$(BIN_DIR)/$(TARGET)

clean:
	$(DEL_FILE) $(BIN_DIR)/*

