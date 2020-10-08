
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
    int c_sock;
    char msg[20]="Hello server";
    char buf[200];
    char var[10];
    c_sock = socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in  client;
    memset(&client,0,sizeof(client));
    client.sin_family=AF_INET;
    client.sin_port=htons(9009);
    client.sin_addr.s_addr=INADDR_ANY;
    printf("\nConnecting to server....\n");
    sendto(c_sock,msg,sizeof(msg),0,(struct sockaddr*)&client,sizeof(client));
    socklen_t add=sizeof(client);
    recvfrom(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,&add);
    qq:
    printf("%s",buf);
    scanf("%s",var);
    sendto(c_sock,var,sizeof(var),0,(struct sockaddr*)&client,sizeof(client));
    if(recvfrom(c_sock,buf,sizeof(buf),0,(struct sockaddr*)&client,&add)){
        goto qq;
    }
    close(c_sock);
    return 0;
}
