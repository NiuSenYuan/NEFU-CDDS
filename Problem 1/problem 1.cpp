#include <iostream>
#include <string>
using namespace std;
typedef struct LNode
{
    int coe;    //系数coe
    int exp;    //指数exp
    struct LNode *next;
}LNode,*LinkList;
void CreatePolynomial(LinkList &L,int n)
{//按指数exp从大到小存多项式
    L=new LNode;
    L->next=NULL;
    for(int i=0;i<n;i++)
    {
        LinkList p=new LNode;
        cin>>p->coe>>p->exp;
        LinkList pre=L,cur=L->next;      //pre和cur是多项式链表的工作指针，分别初始化为头结点和首元结点
        while(cur&&p->exp<cur->exp)    //若待插入项的指数小于当前结点的指数，指针pre指向当前结点，当前结点的指针cur后移
        {
            pre=cur;
            cur=cur->next;
        }
        p->next=cur;    //待插入项的指数不小于当前结点的指数时，用头插法插入节点
        pre->next=p;
    }
}
void OutputPolynomial(LinkList L)
{//输出多项式
    if(!L||!L->next) cout<<0;
    LinkList p=L->next;     //p是多项式链表的工作指针,初始化为首元结点
    while(p)
    {
        if(p==L->next)     //p指向首元结点时，根据指数的情况输出多项式
        {
            if (p->exp!=0)
                cout<<p->coe<<"x^"<<p->exp;
            else
                cout<<p->coe;
        }
        else      //p指向其他结点时，根据系数的正负和指数的情况输出多项式
        {
            if(p->coe>0) cout<<"+";
            if(p->exp!=0)
                cout<<p->coe<<"x^"<<p->exp;
            else
                cout<<p->coe;
        }
        p=p->next;
    }
    cout<<endl;
}
LinkList Add(LinkList LA,LinkList LB)
{//多项式的加法运算
    LinkList pa=LA->next;  //pa和pb是链表LA和LB的工作指针，均初始化为首元结点；
    LinkList pb=LB->next;
    LinkList LC;
    CreatePolynomial(LC, 0);    //目标多项式链表LC
    LinkList pc=LC;            //pc是链表LC的工作指针
    while(pa&&pb)           //两个工作指针均未到达表尾时
    {
        if (pa->exp==pb->exp)    //指数相同，根据系数求和后的情况判断是否需要将结点插入链表LC中
        {
            int sum=pa->coe+pb->coe;
            if (sum)
            {
                pa->coe=sum;
                pc->next=pa;
                pc=pa;
                pa=pa->next;
                pb=pb->next;
            }
            else
            {
                 pa=pa->next;
                 pb=pb->next;
            }
        }
        else if(pa->exp>pb->exp)  //指数不同，将指数较大者优先插入链表LC中
        {
            pc->next=pa;
            pc=pa;
            pa=pa->next;
        }
        else {
            pc->next=pb;
            pc=pb;
            pb=pb->next;
        }
    }
    pc->next=pa?pa:pb;   //某个链表先遍历完，则将另一链表的剩余部分直接链入LC中
    return LC;
}
void Minus(LinkList LA,LinkList LB)
{//多项式的减法
    LinkList p=LB->next;    //p是链表LB的工作指针，初始化为首元结点
    while(p)         //每项系数取相反数
    {
        p->coe*=-1;
        p=p->next;
    }
    OutputPolynomial(Add(LA, LB));
}
void Mul(LinkList LA,LinkList LB)
{//多项式的乘法
    LinkList pa=LA->next; //pa和pb是链表LA和LB的工作指针，均初始化为首元结点；
    LinkList pb=LB->next;
    LinkList LC;    //目标多项式链表LC
    CreatePolynomial(LC, 0);
    LinkList temp;    //记录中间结果
    CreatePolynomial(temp, 0);
    while(pa)
    {
        while(pb)
        {
            LinkList p=new LNode;//p是记录中间结果的辅助指针
            p->next=NULL;
            p->coe=pa->coe*pb->coe;
            p->exp=pa->exp+pb->exp;
            temp->next=p;
            LC=Add(LC,temp);
            pb=pb->next;
        }
        pb=LB->next;
        pa=pa->next;
    }
    OutputPolynomial(LC);
}
void Diff(LinkList L)
{//多项式的求导运算
    LinkList p=L->next;  //p是链表L的工作指针，初始化为首元结点
    LinkList r=NULL;  //r是删除操作的辅助指针
    while(p)
    {
        p->coe*=p->exp;
        p->exp--;
        if(p->exp<0)  //所有数据的指数大于等于0
        {
            r=p;
            p=p->next;
            delete r;
        }
        else
        {
            p=p->next;
        }
    }
    OutputPolynomial(L);
}
void Opt(LinkList &LA,LinkList &LB,string s)
{//依据字符选择多项式的加法、减法、乘法和求导运算
    if(s=="+") OutputPolynomial(Add(LA, LB));
    if(s=="-") Minus(LA, LB);
    if(s=="*") Mul(LA, LB);
    if(s=="'")
    {
        Diff(LA);
        Diff(LB);
    }
}
int main()
{
    int n;    //总计有n组数据
    cin>>n;
    while(n--)
    {
        int a,b;
        cin>>a>>b;
        LinkList LA,LB;
        CreatePolynomial(LA,a);
        CreatePolynomial(LB,b);
        string s;
        cin>>s;
        Opt(LA,LB,s);
    }
    return 0;
}
