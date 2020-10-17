#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h> 
int main() {
	int c_sock;
	c_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in client;
	memset(&client, 0, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_port = htons(9009);
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	

	if(connect(c_sock, (struct sockaddr*)&client, sizeof(client)) == -1) {
	printf("Connection failed");
	return 0;
	}
	char msg[50]="akwnowledgement";
	char buff[100];

	for(int i=0;i<10;i++) {
		bzero(buff,sizeof(buff));
		int n = read(c_sock, buff, sizeof(buff));
		printf("Message received from server : %s \n",buff);
		printf("Aknowledgement sent \n");
		write(c_sock,msg, sizeof(msg));
	}
	
	close(c_sock);
	return 0;
}
