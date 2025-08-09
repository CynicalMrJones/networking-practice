
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    struct socket_addr{
        int sa_family;
        char data;
    };

    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1){
        perror("Could not create socket\n");
        return -1;
    }

    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8690);
    
    if (bind(socketfd, &address, sizeof(address)) < 0){
        perror("whoops couldn't bind\n");
        return -1;
    }

    listen(socketfd, 5);
    
    printf("Now Accepting new connections\n");
    int new_socket = accept(socketfd, &address, (socklen_t*)sizeof(address));
    char buf[20]  = "Hello, World server!";
    int sendt = send(socketfd, &buf, 20, 0);
    printf("%d\n", sendt);

    close(new_socket);
    close(socketfd);
}
