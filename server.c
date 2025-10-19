#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
 
double resultcalc(char *buffer);


int main(void)
{

   int sockfd,portn,newsockfd;
  
   struct sockaddr_in saddr,cliaddr;
   
   char buffer[256];
   
   
   
   sockfd=socket(AF_INET,SOCK_STREAM,0);
   
   if (sockfd<0)
    {
     printf("cant open socket!\n");
     exit(0);
    }
    
    portn=41139;
    
    bzero((char *) &saddr, sizeof(saddr));
    
    saddr.sin_family=AF_INET;
    saddr.sin_addr.s_addr=INADDR_ANY;
    saddr.sin_port=htons(portn);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
     
    if (bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr))<0)
    {
     printf("error bind");
     exit(0);
     }
     
     listen(sockfd,5);
     
     int cl;
     
     cl=sizeof(cliaddr);
     
     newsockfd=accept(sockfd,(struct sockaddr *)&cliaddr,&cl);
     
     if (newsockfd<0)
     {
       printf("error accept");
       exit(1);
     }
     
     
     int n;
     bzero(buffer,sizeof(buffer));
     
     n=read(newsockfd,buffer,sizeof(buffer));
     
     if (n<0)
     {
     printf("socket error");
     exit(1);
     
     }
     
     double res=resultcalc(buffer);
     
     if (res==-1)
     {perror("invalid result"); exit(1);}
     
     char fin[20];
     
     snprintf(fin,sizeof(fin),"%f",res);
     
     
     n=write(newsockfd,fin,strlen(fin));
     
     if (n<0){perror("erroror");exit(1);}
     
     close(newsockfd);
     
     return 0;

}

double resultcalc(char *buffer)
{
  char keno[50];
  int j=0;

  for (int i=0;i<strlen(buffer);i++)
  {
    if (buffer[i]=='+' || buffer[i]=='-' || buffer[i]=='/' || buffer[i]=='*')
    { 
     keno[j++]=' ';
     keno[j++]=buffer[i];
     keno[j++]=' ';
    }
    else
    keno[j++]=buffer[i];
  }
  
  keno[j]='\0';
  
  
  char *token[50];
  int i=0;
  
        token[0]=strtok(keno," ");

        if (token[0]==NULL)
        exit(0);

        for (i=1;i<50;i++)
        {
          token[i]=strtok(NULL," ");
          if (token[i]==NULL)
          break;
        }
  
  int num1,num2;
          
  num1=atoi(token[0]);
  num2=atoi(token[2]);
  
  double result;
  
  if(*token[1]=='+')
  result=num1+num2;
  else if (*token[1]=='*')
  result=num1*num2;
  else if (*token[1]=='-')
  result=num1-num2;
  else if (*token[1]=='/' && num2!=0)
  result=num1/num2;
  else
  return -1.0;
  
  return result;
  
  
       

}
