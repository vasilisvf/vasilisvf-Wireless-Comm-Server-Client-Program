#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    struct hostent *server;
    int sockfd,portn;
    
    struct sockaddr_in addr;
    
    char buffer[256];
    
    if (argc<3)
    {
    printf("Not enough arguments! (host,port number..) \n");
    exit(0);
    }
    
    portn=atoi(argv[2]);
    
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    if (sockfd<0)
    {
     printf("cant open socket!\n");
     exit(0);
    }
    
    server=gethostbyname(argv[1]);
    
    if (server==NULL)
    {
    printf("cant open server\n");
    exit(0);
    }
    
 
    
    
    addr.sin_family=AF_INET;
    addr.sin_port=htons(portn);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    int connection=connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
    
    if (connection<0)
    {
    printf("error connecting\n");
    exit(0);
    }
    
    printf("give your expression\n");
    
    fgets(buffer,sizeof(buffer),stdin);
    
    int n;
    
    n=write(sockfd,buffer,strlen(buffer));
    
    if(n<0)
    {
      printf("error writing");
      exit(1);
    }
    
    bzero(buffer,sizeof(buffer));
   
    
    n=read(sockfd,buffer,sizeof(buffer));
    
    if(n<0)
    {
      printf("error reading");
      exit(1);
    }
    
    printf("%s ",buffer);
    
    
    close(sockfd);
    
    return 0;
    
    
}
    
    
   
