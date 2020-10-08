#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
int linecount(){
FILE *ptr;
int count=0;
ptr=fopen("doc.txt","r");
for(char c = getc(ptr); c != EOF; c = getc(ptr)) 
        if (c == '\n')
        count = count + 1; 
fclose(ptr); 
return count;
}

void sort(int number[6])
{
int a;
for (int i = 0; i < 5; ++i) 
        {
 
            for (int j = i + 1; j < 5; ++j)
            {
 
                if (number[i] > number[j]) 
                {
 
                    a =  number[i];
                    number[i] = number[j];
                    number[j] = a;
 
                }
 
            }
 
        }

}
int gettimes(int times[6]){
FILE *ptr=fopen("doc.txt","r");
int i=0,d;
//fseek(ptr,0,SEEK_SET);
while (fscanf(ptr,"%d",&d)==1) {
        times[i++]=d; 
		//printf(" %d ",d);
		}
sort(times);
fclose(ptr);
}

int main()
{

int s_sock,c_client;
char buf[10];
int times[6];
FILE *ptr=fopen("doc.txt","w");
fclose(ptr);

pid_t childpid;
socklen_t addr_size;
s_sock=socket(AF_INET,SOCK_STREAM,0);

struct sockaddr_in server,other;
memset(&server,0,sizeof(server));
memset(&other,0,sizeof(other));
server.sin_family=AF_INET;
server.sin_port=htons(9009);
server.sin_addr.s_addr=INADDR_ANY;
if(bind(s_sock,(struct sockaddr*)&server,sizeof(server))==-1)
{
printf("error in starting server,exiting\n");
exit(0);
}
printf("Game server online!\nawaiting connections");
listen(s_sock,5);
addr_size=sizeof(other);
//for(int i=0;i<5;i++)
//times[i]=1000;
//int i=0;
while(1)
{
c_client=accept(s_sock,(struct sockaddr*)&other,&addr_size);
printf("A connection accepterd from %s port %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));

if(c_client==-1)
{
printf("some error occued exiting \n");
exit(0);
}



if((childpid=fork())==0)
{

close(s_sock);
while(1)
{
recv(c_client,buf,sizeof(buf),0);

//printf("cli msg : %s",buf);
char q1[900],q2[900],q3[900],q4[900],q5[900],ans[20],wrong[80],end[80],exp[80],waitend[200],wonend[80];
/*
strcpy(q1,"rules (use end to exit) \nq1 :");
strcpy(q2,"q2 :");
strcpy(q3,"q3 :");
strcpy(q4,"q4 :");
strcpy(q5,"q5 :");
*/
strcpy(q1,"\t\t\tWelcome to the Game!  \n\nThis game consists of five MCQ questions. For which the answer will be one uppercase letter(A/B/C/D).Only one chance will be given for each question and you have one minute each. If you get the answer right you will be able to attempt the next question. After completing all questions you may wait to know whether you have won. To exit the game type 'end' at anytime.\n\nQ1: Which country is know as the 'bread basket' of the Soviet Union? \n(A) Ukraine (B) Belarus (C) Albania (D) Georgia  : ");//A
strcpy(q2, "Q2: Who was Queen Elizabeth II’s predecessor?\n(A) Elizabeth I (B) George VI (C) Henry VIII (D) Victoria III  : " );
strcpy(q3, "Q3:  What is the name of Elon Musk’s  chain of satellites which have been seen in the skies over Britain, which some people thought were UFOs? \n(A) Skylink (B) Interwebs (C) Starlink (D) Spacedots  : ");//C
strcpy(q4, "Q4: In which year was Concorde officially taken out of commission? \n(A) 1999 (B) 2001 (C) 1989 (D) 2003  : ");//D
strcpy(q5, "Q5: Which country has the longest coastline in the world? \n(A) Canada (B) Russia (C) Denmark (D) Austrialia  : ");//A


strcpy(end,"sorry you lost by responsetime margin -use end to exit :");
strcpy(waitend,"waiting for others to finish, press any key and press enter or use end to exit:");
strcpy(wonend,"congrats,you won!! -use end to exit :");
strcpy(wrong,"You entered wrong answer,better luck next time,use end to exit: ");
strcpy(exp,"Sorry time has expired, use end to exit :");
time_t t1,t2,t3;
int t_total=0;
int flag=0;
send(c_client,q1,sizeof(q1),0);
t1=time(NULL);
bzero(ans,sizeof(ans));
recv(c_client,ans,sizeof(ans),0);
t2=time(NULL);
if(t2-t1 >60)
{
printf("Disconnected from %s on port %d -Time expired for question \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,exp,sizeof(exp),0);
exit(0);
}
t_total=t_total +(t2-t1);
if(strncmp(ans,"A",1)!=0){
printf("Disconnected from %s on port %d -> wrong answer for question 1\n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,wrong,sizeof(wrong),0);
exit(0);
}else if(strncmp(ans,"end",3)==0){
printf("Disconnected from %s on port %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
exit(0);
}

send(c_client,q2,sizeof(q2),0);
t1=time(NULL);
bzero(ans,sizeof(ans));
recv(c_client,ans,sizeof(ans),0);
t2=time(NULL);
if(t2-t1 >60)
{
printf("Disconnected from %s on port %d -Time expired for question \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,exp,sizeof(exp),0);
exit(0);
}
t_total=t_total +(t2-t1);

if(strncmp(ans,"B",1)!=0){
printf("Disconnected from %s on port %d -> wrong answer for question 2\n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,wrong,sizeof(wrong),0);
exit(0);
}else if(strncmp(ans,"end",3)==0){
printf("Disconnected from %s on port %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
exit(0);
}

send(c_client,q3,sizeof(q3),0);
t1=time(NULL);
bzero(ans,sizeof(ans));
recv(c_client,ans,sizeof(ans),0);
t2=time(NULL);
if(t2-t1 >60)
{
printf("Disconnected from %s on port %d -Time expired for question \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,exp,sizeof(exp),0);
exit(0);
}
t_total=t_total +(t2-t1);

if(strncmp(ans,"C",1)!=0){
printf("Disconnected from %s on port %d -> wrong answer for question 3\n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,wrong,sizeof(wrong),0);
exit(0);
}else if(strncmp(ans,"end",3)==0){
printf("Disconnected from %s on port %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
exit(0);
}

send(c_client,q4,sizeof(q4),0);
t1=time(NULL);
bzero(ans,sizeof(ans));
recv(c_client,ans,sizeof(ans),0);
t2=time(NULL);
if(t2-t1 >60)
{
printf("Disconnected from %s on port %d -Time expired for question \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,exp,sizeof(exp),0);
exit(0);
}

t_total=t_total +(t2-t1);
if(strncmp(ans,"D",1)!=0){
printf("Disconnected from %s on port %d -> wrong answer for question 4\n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,wrong,sizeof(wrong),0);
exit(0);
}else if(strncmp(ans,"end",3)==0){
printf("Disconnected from %s on port %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
exit(0);
}

send(c_client,q5,sizeof(q5),0);
t1=time(NULL);
bzero(ans,sizeof(ans));
recv(c_client,ans,sizeof(ans),0);
t2=time(NULL);
if(t2-t1 >60)
{
printf("Disconnected from %s on port %d -Time expired for question \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,exp,sizeof(exp),0);
exit(0);
}
t_total=t_total +(t2-t1);

if(strncmp(ans,"A",1)!=0){
printf("Disconnected from %s on port %d -> wrong answer for question 5\n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
send(c_client,wrong,sizeof(wrong),0);
exit(0);
}else if(strncmp(ans,"end",3)==0){
printf("Disconnected from %s on port %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port));
exit(0);
}
FILE *ptr=fopen("doc.txt","a");
//fprintf(ptr,"%s %d\n",inet_ntoa(other.sin_addr),t_total);
fprintf(ptr,"%d\n",t_total);
fclose(ptr);
int c=linecount();
if(c<5){
send(c_client,waitend,sizeof(waitend),0);
while(c!=5)
{
c=linecount();
}
//printf(" c is 3 \n");
usleep(1000);
}
int i=0,d;
int *timz =(int*)malloc(6*sizeof(int));
gettimes(timz);


//for(int i=0;i<3;i++)
//printf(" %d ",times[i]);
//printf("\n");

if(timz[0]==t_total)
send(c_client,wonend,sizeof(end),0);
else
send(c_client,end,sizeof(end),0);
//for(int i=0;i<3;i++)
//printf(" %d ",times[i]);
//printf("\n");
if(timz[0]==t_total)
printf("Winner of this round is : %s \n",inet_ntoa(other.sin_addr));
printf("Disconnected from %s on port %d --total time = %d \n",inet_ntoa(other.sin_addr),ntohs(other.sin_port),t_total);

free(timz);
exit(t_total);

}

////////
FILE *fp= fopen("doc.txt","w");
fclose(fp);

}
//int time;
//wait(&time);
//if(time!=0)
//times[i]=time;
//close(c_client);
//printf("\n");
//for(int i=0;i<6;i++)
//printf(" %d ",times[i]);
//printf("\n");
}

close(s_sock);
return 0;
}

