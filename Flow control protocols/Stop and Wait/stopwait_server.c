#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h> 
int main() {
	int s_sock, c_sock;
	s_sock = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server, other;
	memset(&server, 0, sizeof(server));
	memset(&other, 0, sizeof(other));
	server.sin_family = AF_INET;
	server.sin_port = htons(9009);
	server.sin_addr.s_addr = INADDR_ANY;
	socklen_t add;
	

	if(bind(s_sock, (struct sockaddr*)&server, sizeof(server)) == -1) {
		printf("Binding failed\n");
		return 0;
	}
	printf("\tServer Up\n Stop and wait protocol used to send 10 messages \n\n");
	listen(s_sock, 10); 
	add = sizeof(other);
	c_sock = accept(s_sock, (struct sockaddr*)&other, &add);
	char msg[50]="server message : ";
	char buff[50];

	for(int i=0;i<10;i++) {
		usleep(1000);
		char buff2[60];
		bzero(buff2,sizeof(buff2));
		strcpy(buff2,msg);
		buff2[strlen(msg)]=(i+48);
		buff2[strlen(buff2)]='\0';
		printf("Message sent to client \n");
		write(c_sock, buff2, strlen(buff2));
		int n = read(c_sock, buff, sizeof(buff));
		buff[n] = '\0';
		printf("Message from Client: %s\n", buff);



	}
	
	close(c_sock);
	close(s_sock);
	return 0;
}
