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
char buf[100];
c_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in client;
memset(&client,0,sizeof(client));
client.sin_family=AF_INET;
client.sin_port=htons(9009);
client.sin_addr.s_addr=inet_addr("40.88.2.46");
if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1)
{
printf("Error ,server down\nexiting...\n");
exit(0);
}
strcpy(buf,"hello");
printf("Connection to server established");
send(c_sock,buf,sizeof(buf),0);
recv(c_sock,buf,sizeof(buf),0);
printf("\nMessage from server  : \n%s",buf);
//fgets(buf,100,stdin);
close(c_sock);
return 0;
}
