CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -Iinclude

TARGET = bin/main.exe

SOURCES := $(shell find src -name "*.c")

all: $(TARGET)

$(TARGET): $(SOURCES)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

benchmark: all
	python scripts/benchmark.py
	cat data/benchmarks/benchmark.csv

graph:
	python scripts/graphs.py

clean:
	rm -f $(TARGET)

rebuild: clean all