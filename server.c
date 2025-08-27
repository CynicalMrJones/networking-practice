
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include "lib/stats.h"
/*
 * Potential Feat: Writing output to a file for logging (Research how logging is typically done)
 */


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

        //message ini
        char command[1];
        char buf2[21] = "Hello, World server 2";
        int recieve = recv(new_socket, &command, sizeof(char[1]), 0);
        fprintf(fptr, "Recieve code: %d\n", recieve);
        fprintf(fptr, "Command code: %d\n", atoi(command));

        //command parsing
        if (atoi(command) == 1){
            char *message = get_stats();
            send(new_socket, message, strlen(message), 0);
            fprintf(fptr, "Served one client\n");
            free(message);
        }
        else if(atoi(command) == 2){
            send(new_socket, buf2, 21, 0);
            fprintf(fptr, "Served one client\n");
        }
        else if(atoi(command) == 3){
            fprintf(fptr, "Closing server\n");
            close(new_socket);
            close(socketfd);
            break;
        }
        else{
            fprintf(fptr, "Invalid command number\n");
            fprintf(fptr, "\n");
            close(new_socket);
        }
    }
    close(socketfd);
    fclose(fptr);
}
