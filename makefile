
all: client server
server:
	gcc -o server server.c lib/stats.c -Wall -Wextra

client:
	gcc -o client client.c -Wall -Wextra
clean:
	rm server client
