#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
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
  struct sockaddr_in server;
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
    printf("Error in creation of socket\n");
    return -1;
  }
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(atoi(argv[2]));
  printf("Enter the message to be send: ");
  fgets(buf,100,stdin);
  len=sizeof(server);
  k=sendto(sock_desc,buf,100,0,(struct sockaddr*)&server,len);
  if(k==-1)
  {
    printf("Error in sending message to server\n");
    return -1;
  }
  close(sock_desc);
  return 0;
}
