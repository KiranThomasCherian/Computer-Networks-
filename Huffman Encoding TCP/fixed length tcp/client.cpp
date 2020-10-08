#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<bits/stdc++.h>
#include <unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>




using namespace std;

int main(){
    ifstream fp;
    fp.open("f.txt");
    char c;
    int a[26] ={0};     //count frequencies.
    //memset(a, 0, 26);
    int ccount=0;
    while(!fp.eof()){
		fp.get(c);
		if(fp.eof())
        break;
        int aval=c;    //ascii of A is 41
        //printf("%d ",aval);
        aval=(aval-65);
        a[aval]++;
        //printf("%d ",aval);
        ccount++;
    }
    string present="";
    for(int i=0;i<26;i++){
        if(a[i]!=0){
			char ch=i+65;
			present+=ch;
            //printf("%d  %d\n",i,a[i]);
        }
    }
fp.close();
	int bit=ceil(log2((float)present.length()));
	//cout<<bit<<present.length()<<log(present.length()); //<<" "<<ceil(log(present.length()))<<endl<<" "<<log(4)<<ceil(1.2)<<""<<log(17)<<endl;
fp.open("f.txt");
    int encoded[900]={0};
    int v=0,ccc=0;
while(!fp.eof()){
fp.get(c);
if(fp.eof())
        break;
int pos=present.find(c);
//cout<<pos<<endl;
if(pos!=-1)
for(int i=bit-1;i>=0;i--){
    int k=pos>>i;
    if(k&1)
    encoded[v++]=1;
    else
    encoded[v++]=0;

}
}
fp.close();


    //for(int i=0;i<v;i++){
    //    cout<<encoded[i];
    //}
    int byt=v/8;
    if(v%8!=0)
    byt++;
    char *packedValues= new char[byt];      //((8*ll/l)
    int i;
    for(i=0;i<byt;i++){
    packedValues[i]='\0';
    }
    for (i=0; i<v; i++) {
    if (encoded[i]) {
        packedValues[i/8] |= (1 << (i % 8));
    }
   

}
    string present2=to_string(v)+present;
    //cout<<present2;
	// string buf="";
	// buf+=to_string(v);
    // for(int i=0;i<ccount;i++){
    //     buf+=ch[i];
    //     buf+=to_string(f[i]);
    // }
    //cout<<"buf "<<buf;
    int c_sock;
    c_sock = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in  client;
    memset(&client,0,sizeof(client));
    client.sin_family=AF_INET;
    client.sin_port=htons(9000);
    client.sin_addr.s_addr=INADDR_ANY;
    if(connect(c_sock,(struct sockaddr*)&client,sizeof(client))==-1){
        printf("\nServer busy/down");
    	free(packedValues);
        return 0;
    }
    char buf1[present2.length()];
    strcpy(buf1,present2.c_str());
    send(c_sock,buf1,sizeof(buf1),0);
    send(c_sock,packedValues,byt*sizeof(char),0);
    cout<<"File succesfully transfered to server (file name : f.txt)"<<endl;
    printf("\nSize of file : %d bits\nsize transfered(without intial handshakesize) :%d bits",ccount*8,8*byt);

    //printf("\n%s",packedValues);
   // recv(c_sock,buf,sizeof(buf),0);
    close(c_sock);

    // printf("%d %d %d %d %d %d",sizeof(*packedValues),sizeof(*vals),ll,l,v,sizeof(char));
    

    //cout<<"\n\nos-\n"<<os<<endl;
    //cout<<packedValues<<" "<<sizeof(packedValues)<<" "<<strlen(packedValues)<<" "<<v;
    delete[] packedValues;
    return 0;
}
