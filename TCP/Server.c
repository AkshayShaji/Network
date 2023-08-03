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
  int sock_desc,temp_sock_desc;
  socklen_t len;
  struct sockaddr_in server,client;
  char buf[100];
  sock_desc=socket(AF_INET,SOCK_STREAM,0);
  if(sock_desc==-1)
  {
    printf("Error in creating socket\n");
    return 1;
  }
  server.sin_family=AF_INET;
  server.sin_addr.s_addr=INADDR_ANY;
  server.sin_port=htons(3005);
  k=bind(sock_desc,(struct sockaddr*)&server,sizeof(server));
  if(k==-1)
  {
    printf("Error in creating bind\n");
    return 1;
  }
  k=listen(sock_desc,5);
  if(k==-1)
  {
    printf("Error in creating listen\n");
    return 1;
  }
  len=sizeof(client);
  temp_sock_desc=accept(sock_desc,(struct sockaddr*)&client,len);
  if(k==-1)
  {
    printf("Error in creating temporary socket\n");
    return 1;
  }
  k=recv(temp_sock_desc,buf,sizeof(buf),0);
  if(k==-1)
  {
    printf("Error in receiving message\n");
    return 1;
  }
  printf("Message received from client is %s\n",buf);
  close(temp_sock_desc);
  close(sock_desc);
  return 0;
}
  
