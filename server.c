
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/statvfs.h>
#include "lib/stats.h"


int main(){
    FILE *fptr;
    fptr = fopen("server.log", "a+");
    if (fptr == NULL) {
        perror("Failed to open file\n");
    }

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

    while(1){

        fprintf(fptr, "Now Accepting new connections\n");

        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int new_socket = accept(socketfd, (struct sockaddr *)&client_address, &client_len);

        if (new_socket < 0){
            perror("Failed to accept\n");
            return -1;
        }

        char *ip = inet_ntoa(client_address.sin_addr);

        //message ini
        char command[10];
        memset(&command, 0, sizeof(command[10]));
        recv(new_socket, &command, sizeof(char)*10, 0);
        fprintf(fptr, "Command code: %s\n", command);

        //command parsing
        if (strcmp(command, "stats") == 0){
            char *message = get_stats("/");
            char *temp = get_temp();
            strcat(message, temp);
            send(new_socket, message, strlen(message), 0);
            fprintf(fptr, "Served one client from IP adress: %s\n\n", ip);
            free(message);
            free(temp);
        }
        else if(strcmp(command, "ip") == 0){
            send(new_socket, ip, strlen(ip), 0);
            fprintf(fptr, "Served one client from IP adress: %s\n\n", ip);
        }
        else if(strcmp(command, "files") == 0){
            char *message2 = get_files("/home");
            send(new_socket, message2, strlen(message2), 0);
            fprintf(fptr, "Served one client from IP adress: %s\n\n", ip);
            free(message2);
        }
        else if(strcmp(command, "quit") == 0){
            fprintf(fptr, "Served one client from IP adress: %s\n", ip);
            fprintf(fptr, "Closing server\n");
            close(new_socket);
            close(socketfd);
            break;
        }
        else {
            fprintf(fptr, "Served one client from IP adress: %s\n\n", ip);
            fprintf(fptr, "Invalid command number\n");
            close(new_socket);
        }
    }
    close(socketfd);
    fclose(fptr);
}
