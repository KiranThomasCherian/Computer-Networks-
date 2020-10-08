#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
int s_sock;
char buf[500];
s_sock = socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in  server,other;
memset(&server,0,sizeof(server));
memset(&other,0,sizeof(other));
server.sin_family=AF_INET;
server.sin_port=htons(9009);
server.sin_addr.s_addr=INADDR_ANY;
socklen_t add;
bind(s_sock,(struct sockaddr*)&server,sizeof(server));
add=sizeof(other);
FILE *fp;
fp=fopen("song_recv_udp.mp3","wb");  
int recved=0;
recvfrom(s_sock,buf,sizeof(buf),0,(struct sockaddr*)&other,&add);
int len=atoi(buf);  
while(len>0)
{
recvfrom(s_sock,buf,sizeof(buf),0,(struct sockaddr*)&other,&add);
fwrite(buf,sizeof(buf),1,fp);
len-=sizeof(buf);
}
//printf("%d",recved);
printf("file received from client, saved as song_recv_udp.mp3" );
fclose(fp);
close(s_sock);
return 0;
}
