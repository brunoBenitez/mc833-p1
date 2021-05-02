all: client.x server.x
.PHONY: all

client.x: $(shell find client -type f)
	$(MAKE) --directory client
	cp client/client.x ./client.x

server.x: $(shell find server -type f)
	$(MAKE) --directory server
	cp server/server.x ./server.x

clean:
	$(MAKE) clean --directory client
	$(MAKE) clean --directory server
	rm -f server.x client.x
.PHONY: clean