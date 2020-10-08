
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main()
{
    int c_sock;
    char buf[40];
    c_sock=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in client;
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;
    socklen_t add;
    add=sizeof(client);
	FILE *fp;
	fp=fopen("udpclient_text.txt","r");
	if(fp==NULL)
	{
	printf("Unable to open file ,exiting ");
	exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int filelen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	int bufsize=40;
	int tosend=filelen;
	printf("\nSending size to servor....\n");
	sprintf(buf,"%d",filelen);
	sendto(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));
	qq:
	if(tosend>bufsize)
	{
	fread(buf,bufsize,1,fp);
	sendto(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));
	tosend=tosend-bufsize;
	goto qq;
	}
	else
	{
	char buf2[40];
	fread(buf2,tosend,1,fp);
	sendto(c_sock,buf2,sizeof(buf2),0,(struct sockaddr*)&client,sizeof(client));
	}
    close(c_sock);
	printf("File send ");
	fclose(fp);
    return 0;
}
