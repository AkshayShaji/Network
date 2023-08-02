#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char* argv[])
{
  int k;
  int sockfd;
  struct sockaddr_in server,client;
  char buf[100];
  if(argc!=3)
  {
    printf("Input format is not correct\n");
    return 1;
  }
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if(sockfd==-1)
  {
    printf("Error in creation of socket\n");
    return 1;
  }
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(atoi(argv[2]));
  printf("Enter the message to be send: ");
  fgets(buf,100,stdin);
  k=sendto(sockfd,buf,100,0,(struct sockaddr*)&server,sizeof(server));
  if(k<0)
  {
    printf("Error in sending message to server\n");
    return 1;
  }
}
