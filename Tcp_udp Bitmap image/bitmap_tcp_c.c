
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
int main(){
    int c_sock;
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
	FILE *fp;
	fp=fopen("bitmapimage.BMP","rb");
	if(fp==NULL){
	printf("Unable to open file ,exiting ");
	exit(0);
	}
	fseek(fp, 0, SEEK_END);
	int filelen = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char bit=fgetc(fp);
	int sends=0;
	clock_t t1=clock();
	while(sends!=filelen)
	{
		send(c_sock,&bit,sizeof(bit),0);
		bit=fgetc(fp);
		//printf("%c",bit);
		sends++;
	}
	clock_t t2=clock(); 
	double lapse = ((double) (t2 - t1))/ CLOCKS_PER_SEC;
	printf("File send to server \nTotal packets sent : %d \nTime delay faced : %f s \n",sends,lapse);
	close(c_sock);
	fclose(fp);
    return 0;
}
