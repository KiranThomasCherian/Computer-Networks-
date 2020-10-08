#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
int main(){
    int c_sock,s_sock;
    char msg[100]="\t\tInteger Calculator\n1)Add\t2)Subtract\t3)Multipily\t4)divide\nElse any to exit \nSelect Option : ";
    char msg1[40]="Enter First Number  :";
    char msg2[40]="Enter Second Number :";
    char msg3[100]="Answer : ";
    char msg4[70]="\nThank you,disconnecting ...Press any key and enter to exit \n";
    char buf[25];
    int z,x1,x2;    //z-option x-variable
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
    send(c_sock,msg,sizeof(msg),0);
    recv(c_sock,buf,sizeof(buf),0);
    if(buf){
        printf("A connection is established");
    }
    z=atoi(buf);
    if(z>=1&&z<=4)  {
    send(c_sock,msg1,sizeof(msg1),0);
    recv(c_sock,buf,sizeof(buf),0);
    x1=atoi(buf);
    send(c_sock,msg2,sizeof(msg2),0);
    recv(c_sock,buf,sizeof(buf),0);
    x2=atoi(buf);
    switch (z)
    {
    case 1:x1=x1+x2;
    break;
    case 2:x1=x1-x2;
    break;
    case 3:x1=x1*x2;
    break;
    case 4:x1=x1/x2;
    break;
    default:
    break;
    }
    char ans[10];
    sprintf(ans,"%d",x1);
    strcat(msg3,ans);
    strcat(msg3,msg4);
    send(c_sock,msg3,sizeof(msg3),0);
    }
    else
    send(c_sock,msg4,sizeof(msg3),0);
    printf("\nDisconnected with client");
    close(s_sock);
    return 0;
}