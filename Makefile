CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = src/main.c \
src/stack.c \
src/queue.c \
src/circular_queue.c \
src/linked_list.c \
src/doubly_linked_list.c \
src/scheduler/fifo.c \
src/scheduler/round_robin.c \
src/scheduler/sjf.c \
src/memory/first_fit.c \
src/memory/best_fit.c \
src/memory/worst_fit.c \
src/memory/coalescence.c \
src/memory/compactation.c \
src/algorithms/backtracking.c \
src/algorithms/brute_force.c \
src/algorithms/divide_conquer.c \
src/algorithms/dp_bottomup.c

OUT = bin/programa.exe

all:
	if not exist bin mkdir bin
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run:
	$(OUT)

clean:
	del bin\*.exe