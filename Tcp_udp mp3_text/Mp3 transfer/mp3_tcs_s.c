#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
	int c_sock,s_sock;
	char buf[500];
	s_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in  server,other;
    memset(&server,0,sizeof(server));
    memset(&other,0,sizeof(other));
    server.sin_family=AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;
    socklen_t add;
    bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    listen(s_sock,10);
    add=sizeof(other);
    c_sock=accept(s_sock,(struct sockaddr*)&other,&add);
	FILE *fp;
	fp=fopen("tcp_song_recv.mp3","wb");  
	int recved=0;  
	while(read(c_sock,buf,sizeof(buf)))
	{
	fwrite(buf,sizeof(buf),1,fp);
	recved+=strlen(buf);
	}
	printf("file received , saved as tcp_song_recv.mp3",recved);
	fclose(fp);
    close(s_sock);
	return 0;
}
