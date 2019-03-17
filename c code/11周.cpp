#include<stdio.h>
#define INF 
#define Max 20
typedef int VertexType;
typedef int ArcType;
typedef struct{
	VertexType vexs[Max];
	ArcType arcs[Max][Max];
    int vexnum,arcnum;
	int kind;
}MGraph;
int LocateVex(MGraph G,VertexType v);
void CreateGraph(MGraph &G){
	int i,j,k,vi,vj;
	scanf("%d%d%d",&G.vexnum,&G.arcnum,&G.kind);
	for(i=0;i<G.vexnum;i++)scanf("%d",&G.vexs[i]);
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++)G.arcs[i][j]=0;}
	    for(k=0;k<G.arcnum;k++){
			scanf("%d%d",&vi,&vj);
			i=LocateVex(G,vi);
			j=LocateVex(G,vj);
			G.arcs[i][j]=1;
			if(G.kind==2)G.arcs[j][i]=1;
		}
}
int LocateVex(MGraph G,VertexType v){
	int i;
	for(i=0;i<G.vexnum;i++)
		if(G.vexs[i]==v)return(i);
	return -1;
}
void InserArc(MGraph &G,VertexType vi,VertexType vj){
	int i,j;
	i=LocateVex(G,vi);
	j=LocateVex(G,vj);
	if(i!=-1&&j!=-1){
		G.arcnum++;
		G.arcs[i][j]=1;
		if(G.kind==2)G.arcs[i][j]=1;
	}
}
int FirstAdjVex(MGraph G,int v){
	int j;
	for(j=0;j<G.vexnum;j++)
		if(G.arcs[v][v]!=0)return j;
	return -1;
}
int NextAdjVex(MGraph G,int v,int w){
	int j;
	for(j=w+1;j<G.vexnum;j++)
		if(G.arcs[v][j]!=0)return j;
	return -1;
}
void main(){
	int i,j,vi,vj;
	MGraph G;
    CreateGraph(G);
	printf("ÁÚ½Ó¾ØÕó£º\n");
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++)
			printf("%3d",G.arcs[i][j]);
	printf("\n");
	}
	printf("\n");
	printf("enter you want to insert:");
	scanf("%d%d",&vi,&vj);
	printf("²åÈëºódeÁÚ½Ó¾ØÕó£º\n");
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++)
			printf("%3d",G.arcs[i][j]);
	printf("\n");
	}
	printf("\n");
}

