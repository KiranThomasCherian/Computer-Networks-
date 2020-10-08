#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main()
{
    int s_sock;
    char buf[40];
    s_sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in server,other;
    server.sin_family=AF_INET;
    server.sin_port=htons(9009);
    server.sin_addr.s_addr=INADDR_ANY;
    bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    socklen_t add;
    add=sizeof(other);
	FILE *fp;  
	fp=fopen("udp_server_text.txt","w");
	recvfrom(s_sock,buf,sizeof(buf),0,(struct sockaddr*)&other,&add);
	int lent=atoi(buf);
	//printf("%d\n",lent); 
	while(lent>0)
	{
	recvfrom(s_sock,buf,sizeof(buf),0,(struct sockaddr*)&other,&add);
	//fwrite(buf,sizeof(buf),1,fp);
	fputs(buf,fp);
	lent-=strlen(buf);
	}
	printf("File received, saved as udp_server_text.txt");
	fclose(fp);
    close(s_sock);
    return 0;
}
