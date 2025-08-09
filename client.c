
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
    
    int sock = 0;
    struct sockaddr_in serv_addr;

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("\n Socket failed to create\n");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8690);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        perror("\nInvalid address\n");
        return -1;
    }

    if(connect(sock, &serv_addr, sizeof(serv_addr)) < 0){
        perror("\n connection failed\n");
        return -1;
    }

    char buf[20];
    memset(buf, 0, 20);
    int recieve = recv(sock, buf, 20, 0);
    sleep(5);
    printf("%s\n", buf);
    printf("Done and done bubba\n");
    close(sock);
}
