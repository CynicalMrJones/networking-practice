
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){
    struct socket_in{
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
    address.sin_port = htons(8888);
    
    if (bind(socketfd, (struct sockaddr*)&address, sizeof(address)) < 0){
        perror("whoops couldn't bind\n");
        return -1;
    }

    if (listen(socketfd, 5) < 0){
        perror("Could not listen\n");
        return -1;
    }
    
    printf("Now Accepting new connections\n");

    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int new_socket = accept(socketfd, (struct sockaddr *)&client_address, &client_len);

    if (new_socket < 0){
        perror("Failed to accept\n");
        return -1;
    }
    char buf[19]  = "Hello, World server";
    send(new_socket, buf, 19, 0);

    close(new_socket);
    close(socketfd);
}
