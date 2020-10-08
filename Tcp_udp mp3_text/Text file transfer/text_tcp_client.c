
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
    int c_sock;
    char buf[25];
    c_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in  client;
    memset(&client,0,sizeof(client));
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;
    if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1){
        printf("\nServer busy/down");
        return 0;
    }
	printf("sending file to server..\n ");
	FILE *fp;
	fp=fopen("tcpclient_text.txt","r");
	if(fp==NULL)
	{
	printf("Unable to open file ,exiting ");
	exit(0);
	}
	fgets(buf,25,fp);
	while(!feof(fp))
	{
	//printf("%s",buf);
    write(c_sock,buf,sizeof(buf));
	fgets(buf,25,fp);
	}
    printf("\nFile sent to server ");
    close(c_sock);
	fclose(fp);
    return 0;
}
