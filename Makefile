all: server client

server:
	chmod +x server

client: 
	cc -o chatclient chatclient.c
	gcc chatclient.c

clean:
	rm -rf *.o chatclient
