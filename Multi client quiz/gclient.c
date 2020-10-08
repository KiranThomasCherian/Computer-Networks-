#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{

int c_sock;
char buf[10];
char msg[900];
c_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in client;
memset(&client,0,sizeof(client));
client.sin_family=AF_INET;
client.sin_port=htons(9009);
client.sin_addr.s_addr=inet_addr("40.88.2.46");
if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
{
printf("error ,server seems to down or game member limit reached,exiting..\n");
exit(0);
}
printf("Establishing connection to game server... \n\n");
strcpy(buf,"hi");
send(c_sock,buf,sizeof(buf),0);
while(recv(c_sock,msg,sizeof(msg),0))
{
printf("%s",msg);
fflush(stdin);
bzero(msg,sizeof(msg));
fgets(buf,100,stdin);
if(strncmp(buf,"end",3)==0){
send(c_sock,buf,sizeof(buf),0);
break;}

send(c_sock,buf,sizeof(buf),0);
bzero(buf,sizeof(buf));
}
close(c_sock);
return 0;
}







