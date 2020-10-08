
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
int c_sock;
char buf[500];
c_sock = socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in  client;
memset(&client,0,sizeof(client));
client.sin_family=AF_INET;
client.sin_port=htons(9009);
client.sin_addr.s_addr=INADDR_ANY;
socklen_t add;
add=sizeof(client);
FILE *fp;
fp=fopen("song.mp3","rb");
if(fp==NULL){
printf("Unable to open file ,exiting ");
exit(0);
}
fseek(fp, 0, SEEK_END);
int filelen = ftell(fp);
fseek(fp, 0, SEEK_SET);
int bufsize=500;
int tosend=filelen;
printf("\nSending size to servor....\n");
sprintf(buf, "%d",tosend);
//printf("%s",buf);
sendto(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));
//printf("%d\n",filelen);
qq:
if(tosend>bufsize)
{
fread(buf,bufsize,1,fp);
sendto(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));
tosend=tosend-bufsize;
//printf("%d\n",tosend);
goto qq;
}
else
{
fread(buf,tosend,1,fp);
sendto(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,sizeof(client));
}
printf("File send ");
close(c_sock);
fclose(fp);
    return 0;
}
