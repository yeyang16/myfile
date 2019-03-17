#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define STACK_INIT_SIZE 100
typedef char ElementType;
typedef struct{
	char *elem;
	int stacksize;
	int top;
}SqStack;
typedef struct node{
	ElementType data;
	struct node *next;
}Node,*LinkStack;
typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*Linklist;
typedef Linklist Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue;
void CreatStack_sq(SqStack &S,int msize=STACK_INIT_SIZE){
	S.elem=new ElementType[msize];
	S.stacksize=msize;
    S.top=-1;
	return;
}
void DestroyStack_sq(SqStack &S){
	delete []S.elem;
	S.top=-1;
	S.stacksize=0;
}
void Push_sq(SqStack &S,ElementType e){
	S.elem[++S.top]=e;
}
int Pop_sq(SqStack &S,ElementType &e){
	if(S.top==-1)printf("Empty\n");
	e=S.elem[S.top--];
	return e;
}
int StackEmpty_sq(SqStack &S){
	if(S.top==-1)
	  return 0;
	else return 1;
}
typedef struct{
	int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef HTNode *HuffTree;
void Bubble(int r[],int n){
	int i,j,lastExchange;
	int temp;
	i=n;
	while(i>0){
		lastExchange=0;
		for(j=1;j<i;j++){
			if(r[j-1]<r[j]){
				temp=r[j];r[j]=r[j-1];r[j-1]=temp;
				lastExchange=j;
			}
		}
		i=lastExchange;
	}
}
void Select(HuffTree &HT,int n,int i,int &s1,int &s2){
	int r[50];
	int j;
	for(j=1;j<i;j++){
		r[j-1]=HT[j].weight;
		printf("%d",r[j-1]);
	}
	printf("\n");
	Bubble(r,n+(i-n));
	for(j=1;j<i;j++){
		r[j-1]=HT[j].weight;
		printf("%d",HT[j].weight);
	}
	for(j=1;j<i;j++){
		if(HT[j].weight==r[0])s1=j;
		if(HT[j].weight==r[1])s2=j;
    }printf("\n");
	r[0]=r[1]=100;
}
void HuffmanTree1(HuffTree &HT,int w[],int n){
	int m,i;
	int s1=0,s2=0;
	m=2*n-1;
	HT=(HuffTree)malloc(sizeof(HTNode)*(m+1));
	for(i=1;i<=m;i++){
		HT[i].weight=i<=n?w[i-1]:0;
		HT[i].lchild=HT[i].rchild=HT[i].parent=0;
	}
	for(i=n+1;i<=m;i++){
		Select(HT,5,i,s1,s2);
	    HT[i].lchild=s1;
		HT[i].rchild=s2;	
		HT[i].weight=HT[s1].weight+HT[s2].weight;
		HT[s1].parent=HT[s2].parent=i;
	}
}
void Coding(HuffTree HT,int root,char * *HC,SqStack &S){
	char ch;
	if(root!=0){
		if(HT[root].lchild==0){
			Push_sq(S,'\0');
			HC[root]=(char *)malloc(S.top+1);
			strcpy(HC[root],S.elem);
			Pop_sq(S,ch);
		}
		Push_sq(S,'0');
		Coding(HT,HT[root].lchild,HC,S);
		Pop_sq(S,ch);
		Push_sq(S,'1');
		Coding(HT,HT[root].rchild,HC,S);
		Pop_sq(S,ch);
	}
}
void HuffmanCoding(HuffTree HT,char * *&HC,int n){
	SqStack S;
	CreatStack_sq(S,STACK_INIT_SIZE);
	HC=(char * *)malloc(sizeof(char *)*(n+1));
	Coding(HT,2*n-1,HC,S);
}
void main(){
	HuffTree HT;
    char **HC;
	int w[6]={0},i,j;
	char message[100];
	printf("please enter message:");
	gets(message);
	for(i=0;message[i];i++){
		if(message[i]=='A')w[0]+=1;
		else if(message[i]=='B')w[1]+=1;
		else if(message[i]=='C')w[2]+=1;
		else if(message[i]=='D')w[3]+=1;
		else if(message[i]=='E')w[4]+=1;
		else if(message[i]=='F')w[5]+=1;
	    else printf("error\n");
	}
	HuffmanTree1(HT,w,5);
	HuffmanCoding(HT,HC,5);



}
