#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
  int k;
  int sock_desc;
  struct sockaddr_in client;
  char buf[100];
  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  if(sock_desc==-1)
  {
    printf("Error in creating socket\n");
    return -1;
  }
  client.sin_family=AF_INET;
  client.sin_addr.s_addr=INADDR_ANY;
  client.sin_port=htons(3005);
  k=connect(sock_desc,(struct sockaddr*)&client,sizeof(client));
  if(k==-1)
  {
    printf("Error in creating connection\n");
    return -1;
  }
  printf("Enter the message to be send: ");
  fgets(buf,sizeof(buf),stdin);
  k=send(sock_desc,buf,100,0);
  if(k==-1)
  {
    printf("Error in sending message to server\n");
    return -1;
  }
  return 0;
}
