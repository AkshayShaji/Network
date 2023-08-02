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
  socklen_t len;
  if(argc!=2)
  {
    printf("Input format is not correct\n");
    return 1;
  }
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(atoi(argv[1]));
  k=bind(sockfd,(struct sockaddr*)&server,sizeof(server));
  if(k<0)
  {
    printf("Error in creating bind\n");
    return 1;
  }
  printf("Sending message.........\n");
  k=recvfrom(sockfd,buf,100,0,(struct sockaddr*)&server,&len);
  if(k<0)
  {
    printf("Error in receiving from client\n");
    return 1;
  }
  printf("The message received from client is %s\n",buf);
  return 0;
}
