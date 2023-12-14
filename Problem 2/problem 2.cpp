#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>    
#define MAXNUM 1001   //最大景点数                      
using namespace std;
const int INF=0x3f3f3f3f;
typedef struct message
{
	int num;       //景点代码 
	string name;   //景点名称 
	string pro;    //简介 
}Ciceroni;    
struct Graph{
	int vexnum;
	int arcnum;
	int dis[MAXNUM];     //纪录Dijkstra求出的单源最短路径 
	int arcs[MAXNUM][MAXNUM];
	int answer[MAXNUM][MAXNUM];  //最短路径 
	Ciceroni ScenicSpot[MAXNUM]; //景点信息 
	bool vis[MAXNUM];  //标记景点 
	int path[MAXNUM];  //纪录路径 
	//初始化 
	Graph()
	{
		vexnum=0;
		arcnum=0;
		memset(arcs,INF,sizeof arcs);
		memset(vis,false,sizeof vis);
		memset(answer,INF,sizeof answer);
	}
	//得到景点编号 
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
 	//添加道路 
	void AddEdge(int vex1,int vex2,int dis)
	{
		arcs[vex1][vex2]=arcs[vex2][vex1]=dis;
		answer[vex1][vex2]=answer[vex2][vex1]=dis;
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
		Floyd();
	} 
	//查询各景点信息 
	void query(string& Name)
	{
		int id=GetNum(Name);
		cout<<"景点编号："<< ScenicSpot[id].num<<endl;
		cout<<"景点名称："<< ScenicSpot[id].name<<endl;
		cout<<"景点简介："<< ScenicSpot[id].pro<<endl;
		cout<<"与"<< ScenicSpot[id].name<<"直接相邻的景点有："<<endl;
		for(int i=1;i<=vexnum;i++)
		{
			if(arcs[id][i]!=INF)cout<<ScenicSpot[i].name<<endl;
		}
	}
	//更新景点 
	void UpdateSpot(int id)
	{
		string data;
		cin>>data;
		ScenicSpot[id].pro=data;
	} 
	//用Dijkstra算法计算两点之间的最短路 
	int Dijkstra(int start,int end)
	{
		memset(dis,INF,sizeof dis);
		memset(vis,false,sizeof vis);
		dis[start]=0;
		vis[start]=true;
		int ans = 0;
    	for (int i = 1; i < vexnum; i++)
    	{
        	int t = -1;
       	 	for (int j = 1; j <= vexnum; j++)
        	{
           		if ((dis[t] > dis[j]||t==-1) && vis[j])
            	{
                	t = j;
            	}
        	}
        	vis[t] = false;
        	ans += dis[t];
        	for (int j = 1; j <= vexnum; j++)
        	{
            	if (vis[j])dis[j] = min(dis[j], dis[t]+arcs[t][j]);
        	}
    	}
    	if (dis[end] == INF)return -1;
    	return dis[end];
	} 
	//弗洛伊德算法求景点之间的最短路 
	void Floyd()
	{
		for(int k=1;k<=this->vexnum;k++)
		{
			for(int i=1;i<=this->vexnum;i++)
			{
				for(int j=1;j<=this->vexnum;j++)
				{
					answer[i][j]=min(answer[i][j],answer[i][k]+answer[k][j]);
				}
			}
		}
	}
	//打印景点之间的最短路 
	void PrintMinDis()
	{
		cout<<"-------各景点之间最短路径如下-------"<<endl;
		for(int i=1;i<=vexnum;i++)
		{
			for(int j=i+1;j<=vexnum;j++)
			{
				cout<<ScenicSpot[i].name<<"到"<<ScenicSpot[j].name<<"最短距离为:";
				cout<<answer[i][j]<<endl;
			}
		}
	}
};
struct Graph G;
int stk[MAXNUM];
int top;
//深度优先遍历得到两点之间的所有路径 
void DFS(int start,int end)
{
    stk[top]=start;
    top++;
    G.vis[start]=true;//标记入栈
	for(int i=1; i<=G.vexnum; i++)
    {
        if(G.arcs[start][i]!=INF&&G.arcs[start][i]>0&& !G.vis[i])
        {
            if(i==end)
            {
                for(int j=0; j<top; j++)
                {
                	cout<<G.ScenicSpot[stk[j]].name<<"->";
                }
                cout<<G.ScenicSpot[end].name<<endl;
            }
            else
            {
                DFS(i,end);
                top--; 
                G.vis[i]=0;
            }
        }
    }
}
int main()
{
	//输入景点数和道路数 
    cin>>G.vexnum>>G.arcnum;
    for(int i=1;i<=G.vexnum;i++)
    {
    	cin>>G.ScenicSpot[i].num>>G.ScenicSpot[i].name>>G.ScenicSpot[i].pro;
	}
	cout<<"输入景点名称和景点之间的距离："<<endl; 
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
				cout<<"景点名称有误"<<endl;
			}
		}			
	}
	//弗洛伊德算法求最短路 
	G.Floyd(); 
	//输出景点之间的最短路 
	G.PrintMinDis();
	//输出两个景点之间的所有路径
	cout<<"输出两个景点之间的所有路径！"<<endl;
	string view1,view2;
	cin>>view1>>view2;
	int start=G.GetNum(view1);
	int end=G.GetNum(view2);
	DFS(start,end);	 
    	return 0;
}
