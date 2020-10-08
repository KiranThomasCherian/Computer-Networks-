
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

int s_sock,c_client;
char buf[100];
pid_t childpid;
socklen_t addr_size;
s_sock=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server,other;
memset(&server,0,sizeof(server));
memset(&other,0,sizeof(other));
server.sin_family=AF_INET;
server.sin_port=htons(9009);
server.sin_addr.s_addr=INADDR_ANY;
if(bind(s_sock,(struct sockaddr*)&server,sizeof(server))==-1)
{
printf("error ,exiting \n");
exit(0);
}
printf("Server up!awaiting connections\n");
listen(s_sock,10);
addr_size=sizeof(other);
while(1)
{
usleep(1000);
c_client=accept(s_sock,(struct sockaddr*)&other,&addr_size);
printf("\nconnection accepterd from %s  and port : %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
if(c_client==-1)
{
printf("some error occured,exiting.. \n");
exit(0);
}
if((childpid=fork())==0)
{
close(s_sock);
recv(c_client,buf,sizeof(buf),0);
strcpy(buf,"Your details have been recorded, the connection will close now");
printf("\nClient is given aknowledgement,and that connection will be closed.\n");
send(c_client,buf,sizeof(buf),0);
bzero(buf,sizeof(buf));
close(c_client);
exit(0);
}
close(c_client);
}
close(s_sock);
return 0;
}

