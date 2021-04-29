CC = gcc
CC_FLAGS = 

all: client.x server.x
.PHONY: all

%.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

client.x: $(shell find client -type f)
	$(MAKE) --directory client
	$(CC) $(CC_FLAGS) client/*.o -o client.x

server.x: $(shell find server -type f)
	$(MAKE) --directory server
	$(CC) $(CC_FLAGS) server/*.o -o client.x