CC = gcc
CFLAGS = -Wall -Iinclude
# SRC = src/main.c src/freq.c
SRC = src/main.c src/heap.c
TARGET = zippy

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: clean