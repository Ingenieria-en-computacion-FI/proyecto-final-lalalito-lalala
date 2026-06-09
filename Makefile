CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -Iinclude

SRC=$(filter-out src/main.c, $(wildcard src/*.c)) \
    $(wildcard src/*/*.c)

BIN=bin
TARGET=$(BIN)/main.exe

all:
	if not exist bin mkdir bin
	$(CC) $(CFLAGS) src/main.c $(SRC) -o $(TARGET)

run:
	$(TARGET) fifo 100

test:
	if not exist bin mkdir bin
	$(CC) $(CFLAGS) tests/*.c $(SRC) -o $(BIN)/tests.exe
	$(BIN)/tests.exe

clean:
	del /Q bin\*