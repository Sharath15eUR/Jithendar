#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<sys/types.h>
#include<signal.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>

#define max 80
#define port 55000
#define SA struct sockaddr

void func(int sockfd){
    struct sockaddr_in servaddr;
    socklen_t len;
    int n;
    char buff[max];

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    for(;;){
        bzero(buff, sizeof(buff));
        printf("enter the string:");
        n=0;
        while((buff[n++]=getchar())!='\n');
        sendto(sockfd, buff, sizeof(buff), MSG_CONFIRM, (SA*)&servaddr, sizeof(servaddr));

        len = sizeof(servaddr);
        n = recvfrom(sockfd, buff, sizeof(buff), MSG_WAITALL, (SA*)&servaddr, &len);
        buff[n] = '\0';
        printf("from server:%s\n", buff);

        if(strncmp(buff,"exit",4)==0){
            printf("Client exit.....\n");
            break;
        }
    }
}

int main(){
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd == -1){
        printf("socket creation failed\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("socket created successfully\n");
    }

    func(sockfd);
    close(sockfd);

    return 0;
}
