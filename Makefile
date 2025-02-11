
CC := gcc
CFLAGS := -O2
SRC_DIR := src
TARGET := ./main

SRCS := $(wildcard $(SRC_DIR)/*.c)

.PHONY: build run clean

build:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

run: build
	$(TARGET)

clean:
	rm -f $(TARGET)
