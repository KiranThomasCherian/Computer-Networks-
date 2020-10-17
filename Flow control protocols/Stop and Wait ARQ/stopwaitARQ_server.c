#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h> 
#include<fcntl.h>
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
	printf("\tServer Up\n Stop and wait protocol ARQ used to send 10 messages \n\n");
	listen(s_sock, 10); 
	add = sizeof(other);
	c_sock = accept(s_sock, (struct sockaddr*)&other, &add);
    time_t t1,t2;
	char msg[50]="server message : ";
	char buff[50];
    int flag=0;

fd_set set;
  struct timeval timeout;
  int rv;


//   rv = select(filedesc + 1, &set, NULL, NULL, &timeout);
//   if(rv == -1)
//     perror("select"); 
//   else if(rv == 0)
//     printf("timeout"); 
//   else
 //   read( filedesc, buff, len );
//fcntl(c_sock, F_SETFL, O_NONBLOCK);

	for(int i=0;i<10;i++) {
		if(i==6&&flag==0){
		i=15;
		printf("\ncorrupt packet sending simulation\n");		//for simulating corruption
		}
        bzero(buff,sizeof(buff));
		char buff2[60];
		qq:
		bzero(buff2,sizeof(buff2));
		strcpy(buff2,msg);
		buff2[strlen(msg)]=i+'0';
		
		printf("Message sent to client :%s \n",buff2);
  
		FD_ZERO(&set); 
  		FD_SET(c_sock, &set); 

  		timeout.tv_sec = 2;
  		timeout.tv_usec = 0;
		write(c_sock, buff2, sizeof(buff2));
        //t1=time(NULL);
		// while((read(c_sock, buff, sizeof(buff)))==0&&(time(NULL)-t1)<3){
        //     printf("%d\n",time(NULL)-t1);
        // }
          rv = select(c_sock + 1, &set, NULL, NULL, &timeout);
  if(rv == -1)
    perror("select "); // an error accured 
  else if(rv == 0){
      printf("\nResending message \n");
		if(i==15)
		i=6;
        goto qq;
} // a timeout occured 
  else
  read(c_sock, buff, sizeof(buff));
    //     if(strlen(buff)==0){
            
    //   printf("Resending message : %s \n",buff2);
    //     goto qq;
    //     }
	if(buff[strlen(buff)-1]!=(i%2==0)+'0'){
		printf("\nakw problem %s\n",buff);
		goto qq;
	}

		printf("Message from Client: %s\n", buff);



	}
	
	close(c_sock);
	close(s_sock);
	return 0;
}
