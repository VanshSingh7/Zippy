CC = gcc
CFLAGS = -Wall -Iinclude
# SRC = src/main.c src/freq.c
# SRC = src/main.c src/heap.c
# SRC = src/main.c src/freq.c src/heap.c src/tree.c
SRC = src/main.c src/bitio.c

TARGET = zippy

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: clean