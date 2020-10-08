#include<cstdlib>
#include<math.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<bits/stdc++.h>

using namespace std;



int main(){
    int c_sock,s_sock;
    char msg[750];
    s_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in  server,other;
    memset(&server,0,sizeof(server));
    memset(&other,0,sizeof(other));
    server.sin_family=AF_INET;
    server.sin_port=htons(9000);
    server.sin_addr.s_addr=INADDR_ANY;
    socklen_t add;
    bind(s_sock,(struct sockaddr*)&server,sizeof(server));
    listen(s_sock,10);
    printf("\tServer Up!!\n");
    add=sizeof(other);
    c_sock=accept(s_sock,(struct sockaddr*)&other,&add);
    recv(c_sock,msg,sizeof(msg),0);
    //cout<<"msg -"<<msg<<endl;
    int i=0;
    while(msg[i]<65||msg[i]>90)
    i++;
    string msg2(msg);
    int istr=i;
    string temp=msg2.substr(0,i);
    //cout<<msg2;
    int v=stoi(temp);
    //cout<<endl<<v<<" <-v "<<msg2.length()<<i<<endl;
    int bit=msg2.length()-i;
    bit=ceil(log2((float)bit));
    int byt=v/8;
    if(v%8!=0)
    byt++;
    char *buf=new char[byt];
    recv(c_sock,buf,byt*sizeof(char),0);
    //cout<<buf<<endl;
    int s=strlen(buf);
    int *encodedValues= new int[v];
    for (int i=0; i<v; i++) {
    encodedValues[i] = 0;
}

for (int i=0; i<v; i++) {
    encodedValues[i] = ((buf[i/8] & (1 << (i % 8)))!=0);
}
//cout<<endl;
//for (int i=0; i<v; i++) {
// printf("%d",encodedValues[i]);
//}


    string outp="";
    for(i=0;i<v;){

       int sum=0;
        for(int j=(bit-1);j>=0;j--){
            sum+=(pow(2,j)*encodedValues[i++]);
        }
        char ch=msg2[istr+sum];
       // cout<<sum<<endl<<ch<<endl;
        
        outp+=ch;


    }
    //cout<<outp<<endl<<msg2<<bit;






cout<<endl;


char outt[outp.length()];
strcpy(outt,outp.c_str());
ofstream fp;
fp.open("Text_received.txt");
fp<<outt;
fp.close();


 printf("Data received from client\nSize of data received : %d bits \nData extracted and saved to file:Text_received.txt\n",byt*8);

    close(s_sock); 

    delete[] encodedValues;

    return 0;
}
