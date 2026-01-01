
all: client server
clean:
	rm build/server build/client
server:
	gcc -g -o build/server src/server.c lib/stats.c -Wall -Wextra

client:
	gcc -o build/client src/client.c -Wall -Wextra

install: 
	gcc -o server src/server.c lib/stats.c
	gcc -o client src/client.c
	strip server client
	sudo mv client server /usr/bin
uninstall:
	sudo rm /usr/bin/client /usr/bin/server
