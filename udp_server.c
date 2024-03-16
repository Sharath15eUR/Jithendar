#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<signal.h>
#include<netdb.h>
#include<netinet/in.h>
#include<pthread.h>

#define max 80
#define port 55000
#define SA struct sockaddr

void func(int sockfd){
    char buff[max];
    int n;
    struct sockaddr_in cli;
    socklen_t len;

    for(;;){
        bzero(buff, max);
        len = sizeof(cli);
        n = recvfrom(sockfd, buff, sizeof(buff), MSG_WAITALL, (SA*)&cli, &len);
        buff[n] = '\0';
        printf("from client:%s\n", buff);

        if(strncmp("exit", buff, 4) == 0){
            printf("server exit\n");
            break;
        }

        printf("to client:");
        n = 0;
        while((buff[n++] = getchar()) != '\n');
        sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (SA*)&cli, len);
    }
}

int main(){
    int sockfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1){
        printf("socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("socket created successfully\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if(bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0){
        printf("socket bind failed\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("socket bind success\n");
    }

    func(sockfd);
    close(sockfd);

    return 0;
}
