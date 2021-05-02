CC = gcc
CC_FLAGS = -std=c11 -pedantic -Wall -I..

all: client.x
.PHONY: all

client.x: main.o commands.o utils.o
	$(CC) $(CC_FLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CC_FLAGS) -c $< -o $@

clean:
	rm -f *.o client.x
.PHONY: clean