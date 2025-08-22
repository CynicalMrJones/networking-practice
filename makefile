
all: client server
server:
	gcc -o server server.c -Wall

client:
	gcc -o client client.c -Wall
clean:
	rm server client
