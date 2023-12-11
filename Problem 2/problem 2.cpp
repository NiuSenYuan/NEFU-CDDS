#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>    
#define MAXNUM 1001   //最大景点数                      
using namespace std;
const int INF=0x3f3f3f3f;
typedef struct message
{
	int num;       /??? 
	string name;   /??? 
	string pro;    /??? 
}Ciceroni;       
struct Graph{
	int vexnum;
	int arcnum;
	int arcs[MAXNUM][MAXNUM];
	int answer[MAXNUM][MAXNUM];
	Ciceroni ScenicSpot[MAXNUM];
	bool vis[MAXNUM];
	int path[MAXNUM];
	/???? 
	Graph()
	{
		vexnum=0;
		arcnum=0;
		memset(arcs,INF,sizeof arcs);
		memset(vis,false,sizeof vis);
	}
	/??????????? 
	int GetNum(const string& Name)
	{
		for(int i=1;i<=this->vexnum;i++)
    	{
    		if(this->ScenicSpot[i].name==Name)
    		{
    			return i;
			}
		}
		return 0;
	}
 	/???? 
	void AddEdge(int vex1,int vex2,int dis)
	{
		arcs[vex1][vex2]=arcs[vex2][vex1]=dis;
	}
	/???
	void DeleteSpot(int id)
	{
		for(int i=id;i<=vexnum-1;i++)
		{
			ScenicSpot[i]=ScenicSpot[i+1];
		}
		for(int i=1;i<=vexnum;i++)
		{
			if(arcs[i][id]<INF)arcs[i][id]=INF;
		}
		for(int i=1;i<=vexnum;i++)
		{
			if(arcs[id][i]<INF)arcs[id][i]=INF;
		}
		Floyd();
	} 
	/?????
	void UpdateSpot(int id)
	{
		string data;
		cin>>data;
		ScenicSpot[id].pro=data;
	} 
	/????????????? 
	void Floyd()
	{
		for(int k=1;k<=this->vexnum;k++)
		{
			for(int i=1;i<=this->vexnum;i++)
			{
				for(int j=1;j<=this->vexnum;j++)
				{
					arcs[i][j]=min(arcs[i][j],arcs[i][k]+arcs[k][j]);
				}
			}
		}
	}
	/?????????? 
	void PrintMinDis()
	{
		cout<<"-------???????????-------"<<endl;
		for(int i=1;i<=vexnum;i++)
		{
			for(int j=i+1;j<=vexnum;j++)
			{
				cout<<ScenicSpot[i].name<<"?"<<ScenicSpot[j].name<<"??????:";
				cout<<arcs[i][j]<<endl;
			}
		}
	}
	/???????????????
	void DFS(int spot1,int spot2,int order)
	{
		path[order]=spot1;
		vis[spot1]=true;
		if(spot1==spot2)
		{
			for(int i=1;i<order;i++)
			{
				cout<<this->ScenicSpot[i].name<<"->";
			}
			cout<<this->ScenicSpot[order].name<<endl;
			return;
		}
		for(int i=1;i<=this->vexnum;i++)
		{
			if(!vis[i]&&this->arcs[spot1][i]<INF)
			{
				DFS(i,spot2,order+1);
			}
		}
		vis[spot1]=false;
	} 
};
struct Graph G;
int main()
{
	// ??????????????? 
    cin>>G.vexnum>>G.arcnum;
    for(int i=1;i<=G.vexnum;i++)
    {
    	cin>>G.ScenicSpot[i].num>>G.ScenicSpot[i].name>>G.ScenicSpot[i].pro;
	}
	cout<<"?????????????????!"<<endl; 
	for(int i=1;i<=G.arcnum;i++)
	{
		string spot1,spot2;
		int distance;
		while(cin>>spot1>>spot2>>distance)
		{
			int num1=G.GetNum(spot1);
			int num2=G.GetNum(spot2);
			if(num1&&num2)
			{
				G.AddEdge(num1,num2,distance);
				break;
			}
			else
			{
				cout<<"??????,?????!"<<endl;
			}
		}			
	}
	//弗洛伊德算法求最短路 
	G.Floyd(); 
	//输出景点之间的最短路 
	G.PrintMinDis();
	//输出两个景点之间的所有路径
	string view1,view2;
	cin>>view1>>view2;
	int start=G.GetNum(view1);
	int end=G.GetNum(view2);
	G.DFS(start,end,1);	 
    return 0;
}
/*
input
6 10
1 ???  ????? 
2 ??? ????? 
3 ??? ????? 
4 ??? ????? 
5 ???? ????? 
6 ??? ????? 
??? ??? 100
??? ??? 50
??? ??? 400
??? ??? 100
??? ???? 50
??? ???? 200
??? ??? 800
??? ??? 300
??? ??? 100
??? ??? 250
*/
