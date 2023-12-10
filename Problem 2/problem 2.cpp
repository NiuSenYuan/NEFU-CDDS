/*
校园导游系统 
1.查询图中任意两个景点间的所有路径可以使用弗洛伊德算法;
2.查询图中任意两个景点间的所有路径可以使用图的深度优先遍历 
*/
#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>    
#define MAXNUM 1001   //定义最大顶点数                      
using namespace std;
const int INF=0x3f3f3f3f;
typedef struct message
{
	int num;       //景点编号 
	string name;   //景点名称 
	string pro;    //景点简介 
}Ciceroni;       
struct Graph{
	int vexnum;
	int arcnum;
	int arcs[MAXNUM][MAXNUM];
	Ciceroni ScenicSpot[MAXNUM];
	bool vis[MAXNUM];
	int path[MAXNUM];
	//初始化操作 
	Graph()
	{
		vexnum=0;
		arcnum=0;
		memset(arcs,INF,sizeof arcs);
	}
	//根据景点名称得到景点编号 
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
 	//添加无向边 
	void AddEdge(int vex1,int vex2,int dis)
	{
		arcs[vex1][vex2]=arcs[vex2][vex1]=dis;
	}
	//删除景点
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
	} 
	//更新景点信息
	void UpdateSpot(int id)
	{
		string data;
		cin>>data;
		ScenicSpot[id].pro=data;
	} 
	//求任意两个景点之间的最短距离 
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
	//查询景点之间的最短距离 
	void PrintMinDis()
	{
		cout<<"-------景点之间的最短距离如下-------"<<endl;
		for(int i=1;i<=vexnum;i++)
		{
			for(int j=i+1;j<=vexnum;j++)
			{
				cout<<ScenicSpot[i].name<<"到"<<ScenicSpot[j].name<<"的最短距离为：";
				cout<<arcs[i][j]<<endl;
			}
		}
	}
	//查询图中任意两个景点间的所有路径
	void DFS(string& spot1,string& spot2)
	{
		if(spot1==spot2)
		{
			
			return;
		}
	} 
};
struct Graph G;
int main()
{
	// 输入校园景点的数量以及道路条数 
    cin>>G.vexnum>>G.arcnum;
    for(int i=1;i<=G.vexnum;i++)
    {
    	cin>>G.ScenicSpot[i].num>>G.ScenicSpot[i].name>>G.ScenicSpot[i].pro;
	}
	cout<<"请输入两个景点名称以及景点间的距离！"<<endl; 
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
				cout<<"输入景点有误,请重新输入！"<<endl;
			}
		}			
	}
	G.Floyd(); 
	G.PrintMinDis();
    return 0;
}
/*
input
6 10
1 丹青楼  学习的地方 
2 锦绣楼 学习的地方 
3 田径场 运动的地方 
4 成栋楼 学习的地方 
5 学生公寓 睡觉的地方 
6 老食堂 吃饭的地方 
丹青楼 锦绣楼 100
丹青楼 田径场 50
丹青楼 成栋楼 400
丹青楼 老食堂 100
老食堂 学生公寓 50
田径场 学生公寓 200
老食堂 成栋楼 800
锦绣楼 老食堂 300
锦绣楼 成栋楼 100
田径场 锦绣楼 250
*/ 
