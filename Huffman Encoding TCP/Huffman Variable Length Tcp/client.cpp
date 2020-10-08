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
struct node{
    char c;
    int freq;
    struct node* left;
    struct node* right;
    node(char chr,int fr){
        left=right=NULL;
        c=chr;
        freq=fr;
    }
};

struct comp{
bool operator()(node* p1,node*p2){
return p1->freq>p2->freq ;}
};

char ch[30];
int f[30],fcount,ccount;
void get_chf(){
    ifstream fp;
    fp.open("f.txt");
    if(!fp.is_open()){
        printf("No such file,");
        exit(0);
    }
    char c;
    int afrq[30]={0};
    while (!fp.eof())
    {
		
        fp.get(c);
        if(fp.eof())
        break;
        int aa=c;
        aa-=65;
        afrq[aa]++;
    }
    ccount=0;
    fcount=0;
    for(int i=0;i<26;i++){      //since only 26 alphabets in this case
    if(afrq[i]!=0){
        ch[ccount++]=(i+65);
        f[fcount++]=afrq[i];
    }
    }
    fp.close();
}
char os[750]="";
void printtree(struct node* root, string str) 
{ 
  
    if (!root) 
        return; 
  
    if (root->c != '*') {
        cout << root->c << ": " << str << "\n"; 
        char temp[2];
        temp[0]=root->c;
        temp[1]='\0';
        strcat(os,temp);
        str+=" ";
        int sn = str.length(); 
        char carray[sn + 1]; 
        strcpy(carray, str.c_str());
        strcat(os,carray);

    }
    printtree(root->left, str + "0"); 
    printtree(root->right, str + "1"); 
} 
void huffmantree(){
    struct node *lf,*rt,*root;
    priority_queue<node*, vector<node*>,comp> minheap; 
  
    for (int i = 0; i < ccount; ++i) 
        minheap.push(new node(ch[i], f[i])); 
        while (minheap.size()!=1)
        {
            lf=minheap.top();
            minheap.pop();
            rt=minheap.top();
            minheap.pop();
            root =new node('*',lf->freq+rt->freq);
            root->left=lf;
            root->right=rt;
            minheap.push(root);
        }
        


printtree(root,"");
}

int main(){
    get_chf();
    //for(int i=0;i<ccount;i++)
    //cout<<ch[i]<<" "<<f[i]<<endl;
    //cout<<"aaa-"<<fcount<<endl;
    huffmantree();
    ifstream fin;
    fin.open("f.txt");
    string str(os);
    int encoded[750]={0};
    int v=0,ccc=0;
    while (!fin.eof())
    {
		ccc++;
        char c;
        fin.get(c);
        if(fin.eof()||c<65||c>90)
        break;
        size_t pos,pos2;
        pos=str.find(c);
        pos2=str.find(' ',pos+1);
        string code=str.substr(pos+1,pos2-(pos+1));
       // cout<<code<<" "<<pos<<" "<<pos2<<endl;
       for(int i=0;i<code.size();i++){
           encoded[v++]=code[i]-'0';
       }
    }
    // for(int i=0;i<v;i++){
    //     cout<<encoded[i];
    // }
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

	string buf="";
	buf+=to_string(v);
    for(int i=0;i<ccount;i++){
        buf+=ch[i];
        buf+=to_string(f[i]);
    }
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
    char buf1[buf.length()];
    strcpy(buf1,buf.c_str());
    send(c_sock,buf1,sizeof(buf1),0);
    send(c_sock,packedValues,strlen(packedValues),0);
    cout<<"File succesfully transfered to server (file name : f.txt)"<<endl;
    printf("\nSize of file : %d bits\nsize transfered(without intial handshakesize) :%d bits",ccc*8,8*byt);

    //printf("\n%s",packedValues);
   // recv(c_sock,buf,sizeof(buf),0);
    close(c_sock);

    // printf("%d %d %d %d %d %d",sizeof(*packedValues),sizeof(*vals),ll,l,v,sizeof(char));
    

    //cout<<"\n\nos-\n"<<os<<endl;
    //cout<<packedValues<<" "<<sizeof(packedValues)<<" "<<strlen(packedValues)<<" "<<v;
    delete[] packedValues;
    return 0;
}
