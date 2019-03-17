#include<stdio.h>
#include<malloc.h>
typedef struct BiTNode{
    char data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef char ElementType;
typedef struct LNode{
	BiTree data;
	struct LNode *next;
}LNode,*Linklist;
typedef Linklist Queueptr;
typedef struct{
	Queueptr front;
	Queueptr rear;
}LinkQueue;
void CreateQueue_L(LinkQueue &Q){
	Q.front=Q.rear=new LNode;
	Q.front->next=NULL;
}
void Enqueue_L(LinkQueue &Q,BiTree e){
	Linklist p;
	p=new LNode;
	p->data=e;p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
}
void DeQueue_L(LinkQueue &Q,BiTree &e){
	if(Q.front==Q.rear)printf("Empty\n");
	Linklist p;
	p=Q.front->next;
	Q.front->next=p->next;
	e=p->data;
	if(Q.rear==p)Q.rear=Q.front;
	delete p;
}
void CreateBiTree(BiTree &T){
	char e;
	scanf("%c",&e);
	if(e=='#') T=NULL;
	
	else{
		T=new BiTNode;
		T->data=e;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}
BiTree mirror(BiTree T)
{
	if(!T)
		return NULL;
     else
	 {
		BiTree l,r;
		l=mirror(T->lchild);
		r=mirror(T->rchild);
		T->lchild=r;
		T->rchild=l;
		return T;
	 }
}

void PreOrder(BiTree T){
	if(!T) return;
	else{
		printf("%c",T->data);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}
void InOrder(BiTree T){
	if(!T) return;
	else{
		InOrder(T->lchild);
		printf("%c",T->data);
		InOrder(T->rchild);
	}
}
void PostOrder(BiTree T){
	if(!T) return;
	else{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		printf("%c",T->data);
	}
}
void layerTraveral(BiTree T){
    LinkQueue Q;
	BiTree p;
	p=NULL;
	CreateQueue_L(Q);
	if(T) Enqueue_L(Q,T);
	while(Q.front!=Q.rear){
		DeQueue_L(Q,p);
		printf("%c",p->data);
		if(p->lchild) Enqueue_L(Q,p->lchild);
		if(p->rchild) Enqueue_L(Q,p->rchild);
	}
	
}
int Depth(BiTree T){
	int hl,hr;
	if(!T) return(0);
	else{
		hl=Depth(T->lchild);
		hr=Depth(T->rchild);
		return(hl>hr?hl+1:hr+1);
	}
}
void CountNode(BiTree T,int &n){
	if(T){
		CountNode(T->lchild,n);
		CountNode(T->rchild,n);
		n++;
	}
}
void main(){
	BiTree T;
	CreateBiTree(T);
	mirror(T);
	printf("Pre:");PreOrder(T);printf("\n");

}