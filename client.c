
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char** argv){

    if (argc < 2){
        printf("Need to Give command number\n");
        return -1;
    }
    
    int sock = 0;
    struct sockaddr_in serv_addr;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\nSocket failed to create\n");
        return -1;
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8888);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        perror("\nInvalid address\n");
        return -1;
    }

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        perror("\nConnection failed\n");
        return -1;
    }

    char buf[150];
    send(sock, argv[1], sizeof(char[1]), 0);
    int recieve = recv(sock, buf, sizeof(buf) - 1, 0);
    if (recieve < 0){
        perror("Failed to recieve\n");
        return -1;
    }
    else{
        printf("%d\n", recieve);
    }
    buf[recieve] = '\0';
    printf("%s\n", buf);
    close(sock);
}
