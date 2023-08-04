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
#define nofile "File not found"

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

int sendFile(FILE* fp,char* buf,int s)
{
  int i,len;
  if(fp==NULL)
  {
    strcpy(buf,nofile);
    len=strlen(nofile);
    buf[len]=EOF;
    for(i=0;i<=len;i++)
      {
        buf[i]=Cipher(buf[i]);
      }
    return 1;
  }
  char ch,ch2;
  for(i=0;i<s;i++)
    {
      ch=fgetc(fp);
      ch2=Cipher(ch);
      buf[i]=ch2;
      if(ch==EOF)
      {
        return 1;
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
  if(bind(sockfd,(struct sockaddr*)&addr_con,sizeof(addr_con))==0)
  {
    printf("\nSuccessfully binded\n");
  }
  else
  {
    printf("\nBinding failed\n");
  }
  while(1)
    {
      printf("\nWaiting for file name\n");
      clearBuf(net_buf);
      nBytes=recvfrom(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,&addrlen);
      fp=fopen(net_buf,"r");
      printf("\nFile name received: %s\n",net_buf);
      if(fp==NULL)
      {
        printf("\nFile open failed\n");
      }
      else
      {
        printf("\nSuccessfully opened file\n");
      }
      while(1)
        {
          if(sendFile(fp,net_buf,NET_BUF_SIZE))
          {
            sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
            break;
          }
          sendto(sockfd,net_buf,NET_BUF_SIZE,sendrecvflag,(struct sockaddr*)&addr_con,addrlen);
          clearBuf(net_buf);
        }
      if(fp!=NULL)
      {
        fclose(fp);
      }
    }
  return 0;
}
