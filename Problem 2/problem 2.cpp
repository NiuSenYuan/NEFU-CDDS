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
		memset(answer,INF,sizeof answer);
		memset(vis,false,sizeof vis);
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
	//更新景点 
	void UpdateSpot(int id)
	{
		string data;
		cin>>data;
		ScenicSpot[id].pro=data;
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
int stk[MAXNUM],top;
void DFS(int start,int end)
{
    stk[top]=start;
    top++;
    G.vis[start]=true;//标记入栈
	for(int i=1; i<=G.vexnum; i++)
    {
        if(G.arcs[start][i]!=INF&&G.arcs[start][i]>0&& !G.vis[i])
        {
            //表明两点可达且未被访问
            if(i==end)//DFS到了终点，打印路径
            {
                for(int j=0; j<top; j++)
                {
                	cout<<G.ScenicSpot[stk[j]].name<<"->";
                }
                cout<<G.ScenicSpot[end].name<<endl;
            }
            else//不是终点接着DFS
            {
                DFS(i,end);
                top--;//支路全被访问一遍,顶点出栈
                G.vis[i]=0;//出栈点标记为已出栈，允许下次访问
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
	string view1,view2;
	cin>>view1>>view2;
	int start=G.GetNum(view1);
	int end=G.GetNum(view2);
	DFS(start,end);	 
    return 0;
}
/*
10 15
1 行政楼 办公 
2 食堂 吃饭 
3 赛博楼 信息分院办公室所在地
4 求是楼 实验楼计算机中心
5 格致楼 法学管理学院
6 工程实习中心 金工实习
7 仰仪楼 机电计测分院
8 体育馆 旁边有篮球场、足球场、还有网球场
9 一号教学楼 主要以阶梯教室为主
10 二号教学楼 小教室为多
行政楼 食堂 300
行政楼 仰仪楼 200
体育馆 一号教学楼 150
二号教学楼 仰仪楼 350
一号教学楼 二号教学楼 400
工程实习中心 格致楼 500
行政楼 工程实习中心 200
求是楼 仰仪楼 100
体育馆 工程实习中心 150
食堂 体育馆 100
体育馆 赛博楼 450
格致楼 二号教学楼 50
求是楼 赛博楼 150
一号教学楼 食堂 300
二号教学楼 工程实习中心  70
*/ 
