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
struct node* groot=new node('*',0);

struct comp{
bool operator()(node* p1,node*p2){
return p1->freq>p2->freq ;}
};

    char ch[30];
    int fre[30];
    int cfcount=0;
  
void printtree(struct node* rot, string str) 
{ 
  
    if (!rot) 
        return; 
  
    if (rot->c != '*') {
        cout << rot->c << ": " << str << "\n"; 


    }
    printtree(rot->left, str + "0"); 
    printtree(rot->right, str + "1"); 
} 
//



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
    string temp=msg2.substr(0,i);
    int v=stoi(temp);
    //cout<<v<<" <-v"<<msg2.length()<<endl;

    for(;i<msg2.length();){
        if(msg2[i]>=65&&msg2[i]<=90){
            ch[cfcount]=msg2[i];
            int j;
            for(j=i+1;;j++){
                if(j==msg2.length())
                break;
                if(msg2[j]<=90&&msg2[j]>=65)
                break;

                
            }
            temp=(msg2.substr(i+1,j-(i+1)));
            fre[cfcount++]=stoi(temp);
            i=j;
        }
       // cout<<i<<endl;
    }
    //for(int i=0;i<cfcount;i++)
   // cout<<ch[i]<<" "<<fre[i]<<endl;
   // huffmantree();

    struct node *lf,*rt,*root;

    priority_queue<node*, vector<node*>,comp> minheap; 
  
    for (int i = 0; i < cfcount; ++i) 
        minheap.push(new node(ch[i], fre[i])); 
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
        

groot=minheap.top();
//printtree(groot,"");
groot->left=minheap.top()->left;
groot->right=minheap.top()->right;





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
// for (int i=0; i<v; i++) {
//  printf("%d ",encodedValues[i]);
// }
cout<<endl;
struct node*ptr=groot;
int aa=0;
string outputstr="";
string ans="";
while(aa<=v){
        if(ptr->c!='*'){
        //aa++;
        //cout<<aa<<(ptr->c)<<endl;
        outputstr=outputstr+  (ptr->c);
        ptr=groot;

    }
    else if(encodedValues[aa]==0){
        aa++;
        ptr=ptr->left;
    }else
    {
        aa++;
        ptr=ptr->right;

    }
   // aa++;
    
}
//  struct node* curr = new node;
//  curr=groot; 
//     for (int i=0;i<v;i++) 
//     { 
//         if (encodedValues[i] == '0') 
//            curr = curr->left; 
//         else
//            curr = curr->right; 
  
//         // reached leaf node 
//         if (curr->left==NULL and curr->right==NULL) 
//         { 
//             ans += curr->c; 
//             curr = groot; 
//         } 
//     } 
    // cout<<ans<<endl; 
// ans=ans+"\0"; 



//cout<<groot->c<<groot->freq<<groot->left->freq<<groot->right->freq<<groot->right->c;
// printtree(groot,"");
// cout<<"string"<<outputstr<<endl;
// printtree(groot,"_");

char outt[outputstr.length()];
strcpy(outt,outputstr.c_str());
ofstream fp;
fp.open("Text_received.txt");
fp<<outt;
fp.close();


 printf("Data received from client\nSize of data received : %d bits \nData extracted and saved to file:Text_received.txt\n",byt*8);

    close(s_sock); 

    delete[] encodedValues;

    return 0;
}
