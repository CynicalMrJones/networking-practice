
all: client server
clean:
	rm server client
server:
	gcc -g -o server server.c lib/stats.c -Wall -Wextra

client:
	gcc -o client client.c -Wall -Wextra

release:
	gcc -o server server.c lib/stats.c
	gcc -o client client.c
