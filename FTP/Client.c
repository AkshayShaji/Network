#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define IP_PROTOCOL 0
#define NET_BUF_SIZE 32
#define cipherKey 'S'
#define PORT_NO 15050
#define sendrecvflag 0
#define IP_ADDRESS "127.0.0.1"

void clearBuf(char* b)
{
  int i;
  for(i=0;i<NET_BUF_SIZE;i++)
    {
      b[i]='\0';
    }
}

char Cipher(char ch)
{
  return ch^cipherKey;
}

int recvFile(char* buf,int s)
{
  int i;
  char ch;
  for(i=0;i<s;i++)
    {
      ch=buf[i];
      ch=Cipher(ch);
      if(ch==EOF)
      {
        return 1;
      }
      else
      {
        printf("%c",ch);
      }
    }
  return 0;
}

int main()
{
  int sockfd,nBytes;
  struct sockaddr_in addr_con;
  char net_buf[NET_BUF_SIZE];
  FILE* fp;
  int addrlen=sizeof(addr_con);
  sockfd=socket(AF_INET,SOCK_DGRAM,IP_PROTOCOL);
  if(sockfd<0)
  {
    printf("\nFile descriptor not rceived\n");
  }
  else
  {
    printf("\nFile descriptor received\n");
  }
  addr_con.sin_family=AF_INET;
  addr_con.sin_addr.s_addr=INADDR_ANY;
  addr_con.sin_port=htons(PORT_NO);
  while(1)
    {
      printf("\nEnter the file name to be received: ");
      scanf("%s",net_buf);
      sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
      printf("\n...............Data Received....................\n");
      while(1)
        {
          clearBuf(net_buf);
          nBytes=recvfrom(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
          if(recvFile(net_buf,NET_BUF_SIZE))
          {
            break;
          }
        }
      printf("\n................................................\n");
    }
  return 0;
}
