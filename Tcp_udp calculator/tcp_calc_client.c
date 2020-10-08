
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

    recv(c_sock,buf,sizeof(buf),0);
    qq:

    printf("%s",buf);
    scanf("%s",var);
    send(c_sock,var,sizeof(var),0);
    if(recv(c_sock,buf,sizeof(buf),0)){
        goto qq;
    }
    close(c_sock);
    return 0;
}
