#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.in>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char* argv[])
{
  int k;
  int sock_desc;
  struct sockaddr_in server,client;
  char buf[100];
  socklen_t len;
  if(argc!=2)
  {
    printf("Input format is not correct\n");
    exit(0);
  }
  sock_desc=socket(AF_INET,SOCK_DGRAM,0);
  if(sock_desc==-1)
  {
    printf("Error in creating socket\n");
    return -1;
  }
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(atoi(argv[1]));
  k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
  if(k==-1)
  {
    printf("Error in creating bind\n");
    return -1;
  }
  printf("Sending message.........\n");
  len=sizeof(client);
  k=recvfrom(sock_desc,buf,100,0,(struct sockaddr*)&client,&len);
  if(k==-1)
  {
    printf("Error in receiving from client\n");
    return -1;
  }
  printf("The message received from client is %s\n",buf);
  close(sock_desc);
  return 0;
}
