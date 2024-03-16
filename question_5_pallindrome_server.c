#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<pthread.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<strings.h>

#define max 80
#define PORT 8080
#define SA struct sockaddr

int pallindrome(char *str){
    int len=strlen(str);
    for(int i=0;i<len/2;i++){
        if(str[len-i-1]!=str[i]){
		return 0;
        }
	else{
		return 1;
	}
    }
}

void func(int connfd){
    char buff[max];
    int n;
    for(;;){
        bzero(buff,max);
        read(connfd,buff,sizeof(buff));
        printf("from client: %s\t to client: ",buff);
	for(int i=0;i<strlen(buff);i++){
		if(buff[i]=='\n'){
			buff[i]='\0';
			break;
		}
	}
        
        // Check if the received string is a palindrome
        int result = pallindrome(buff);

        // Send result back to client
        if (result)
            write(connfd, "Palindrome\n", strlen("Palindrome")+1);
	else
            write(connfd, "Not Palindrome\n", strlen("Not Palindrome")+1);
        
        // If client sends "exit", terminate server
        if(strncmp("exit",buff,4)==0){
            printf("server exit.....\n");
            break;
        }
    }
}

int main(){
    int sockfd,connfd,len;
    struct sockaddr_in servaddr,cli;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1){
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("socket created successfully created..\n");
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(PORT);
    
    if((bind(sockfd,(SA*)&servaddr,sizeof(servaddr)))!=0){
        printf("socket bind failed..\n");
        exit(0);
    }
    else
        printf("socket succesfully bined\n");
    
    if((listen(sockfd,5))!=0){
        printf("listen failed\n");
        exit(0);
    }
    else
        printf("server listening\n");
    
    len=sizeof(cli);
    connfd=accept(sockfd,(SA*)&cli,&len);
    if(connfd<0){
        printf("server accept failed\n");
        exit(0);
    }
    else
        printf("server accepted the client\n");
    
    func(connfd);
    close(sockfd);
}
