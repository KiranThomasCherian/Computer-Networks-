#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
int main(){
	int c_sock,s_sock;
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
	printf("\n\tSERVER UP!\n");
    add=sizeof(other);
    c_sock=accept(s_sock,(struct sockaddr*)&other,&add);
	FILE *fp;
	fp=fopen("tcp_bitimage_recv.bmp","wb");  
	int recved=0;
	char bit;  
	clock_t t1=clock();
     while(recv(c_sock,&bit,sizeof(bit),0))
     {
		fputc(bit,fp);
		recved+=sizeof(bit);	
		 
     }
	clock_t t2=clock();
	double lapse = ((double) (t2 - t1))/ CLOCKS_PER_SEC;
	printf("file received , saved as tcp_bitimage_recv.bmp \nTotal packets received : %d \nTime delay :%f s ",recved,lapse);
	fclose(fp);
    close(s_sock);
	return 0;
}
