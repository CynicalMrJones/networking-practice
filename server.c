
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <math.h>
#include <sys/statvfs.h>

/*
 * Potential Feat: Writing output to a file for logging (Research how logging is typically done)
 *           Feat: Alloc memory in get_stats and call free later
 */

void get_stats(char *message){
    struct statvfs Stats;

    if(statvfs("/", &Stats) == -1){
        printf("Failed to get stats\n");
    }

    long gb = pow(10, 9);
    long gib = pow(1024, 3);
    long total_GB = (Stats.f_bavail * Stats.f_frsize) / gb;
    long total_GiB = (Stats.f_bavail * Stats.f_frsize) / gib;
    sprintf(message, "Avaliable Free Blocks: %ld\nTotal avaliable: %ld(GB)\nTotal avaliable: %ld(GiB)\n", Stats.f_bavail, total_GB , total_GiB);
}

int main(){
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

        printf("Now Accepting new connections\n");

        struct sockaddr_in client_address;
        socklen_t client_len = sizeof(client_address);
        int new_socket = accept(socketfd, (struct sockaddr *)&client_address, &client_len);

        if (new_socket < 0){
            perror("Failed to accept\n");
            return -1;
        }

        //message ini
        char command[1];
        char message[200];
        char buf2[21] = "Hello, World server 2";
        int recieve = recv(new_socket, &command, sizeof(char[1]), 0);
        printf("Recieve code: %d\n", recieve);
        printf("Command code: %d\n", atoi(command));

        //command parsing
        if (atoi(command) == 1){
            get_stats(message);
            send(new_socket, message, sizeof(message), 0);
            printf("Served one client\n");
        }
        else if(atoi(command) == 2){
            send(new_socket, buf2, 21, 0);
            printf("Served one client\n");
        }
        else if(atoi(command) == 3){
            printf("Closing server\n");
            close(new_socket);
            break;
        }
        else{
            printf("Invalid command number\n");
            printf("\n");
            close(new_socket);
        }
    }
    close(socketfd);
}
