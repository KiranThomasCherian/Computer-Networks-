#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/time.h>
#include<sys/wait.h>
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
	char msg1[50]="akwnowledgement-0";
    char msg2[50]="akwnowledgement-1";

	char buff[100];
	int flag=1,flg=1,flag2=1;
	for(int i=0;i<10;i++) {
		flg=1;
		bzero(buff,sizeof(buff));
        if((i==3&&flag==1)||(i==7&&flag2==1)){
			printf("\nproblem/corruption simulation\n");
			if(i==3&&flag==1)
			flag=0;
			else if(flag==0)
			flag2=0;            
			i--;
			read(c_sock,buff,sizeof(buff));
			//printf("aa %s \n",buff);
			continue;
        }
		int n = read(c_sock, buff, sizeof(buff));
		//buff[n] = '\0';
        if(buff[strlen(buff)-1]!=i+'0'){          //akw not received at server,so discard
        printf("\nDiscarding packet\n");
        //printf("%c, %c, -- %s\n",buff[strlen(buff)-1],'0'+i,buff);
        //flg=0;
		i--;
		continue;
        //goto qq;
        }
		printf("Message received from server : %s \n",buff);
        printf("Aknowledgement sent \n");
        qq:
        if(i%2==0)
		write(c_sock,msg2, sizeof(msg2));
        else 
 		write(c_sock,msg1, sizeof(msg1));    
		if(flg==0)
		i--;   
	}
	
	close(c_sock);
	return 0;
}
