
all: client server
clean:
	rm server client
server:
	gcc -g -o server server.c lib/stats.c -Wall -Wextra

client:
	gcc -o client client.c -Wall -Wextra

install: 
	gcc -o server server.c lib/stats.c
	gcc -o client client.c
	strip server client
	sudo mv client server /usr/bin
uninstall:
	sudo rm /usr/bin/client /usr/bin/server
