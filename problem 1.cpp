#include <iostream>
#include <string>
using namespace std;
typedef struct LNode
{
    int coe;    //ϵ��coe
    int exp;    //ָ��exp
    struct LNode *next;
}LNode,*LinkList;
void CreatePolynomial(LinkList &L,int n)
{//��ָ��exp�Ӵ�С�����ʽ
    L=new LNode;
    L->next=NULL;
    for(int i=0;i<n;i++)
    {
        LinkList p=new LNode;
        cin>>p->coe>>p->exp;
        LinkList pre=L,cur=L->next;      //pre��cur�Ƕ���ʽ����Ĺ���ָ�룬�ֱ��ʼ��Ϊͷ������Ԫ���
        while(cur&&p->exp<cur->exp)    //�����������ָ��С�ڵ�ǰ����ָ����ָ��preָ��ǰ��㣬��ǰ����ָ��cur����
        {
            pre=cur;
            cur=cur->next;
        }
        p->next=cur;    //���������ָ����С�ڵ�ǰ����ָ��ʱ����ͷ�巨����ڵ�
        pre->next=p;
    }
}
void OutputPolynomial(LinkList L)
{//�������ʽ
    if(!L||!L->next) cout<<0;
    LinkList p=L->next;     //p�Ƕ���ʽ����Ĺ���ָ��,��ʼ��Ϊ��Ԫ���
    while(p)
    {
        if(p==L->next)     //pָ����Ԫ���ʱ������ָ��������������ʽ
        {
            if (p->exp!=0)
                cout<<p->coe<<"x^"<<p->exp;
            else
                cout<<p->coe;
        }
        else      //pָ���������ʱ������ϵ����������ָ��������������ʽ
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
{//����ʽ�ļӷ�����
    LinkList pa=LA->next;  //pa��pb������LA��LB�Ĺ���ָ�룬����ʼ��Ϊ��Ԫ��㣻
    LinkList pb=LB->next;
    LinkList LC;
    CreatePolynomial(LC, 0);    //Ŀ�����ʽ����LC
    LinkList pc=LC;            //pc������LC�Ĺ���ָ��
    while(pa&&pb)           //��������ָ���δ�����βʱ
    {
        if (pa->exp==pb->exp)    //ָ����ͬ������ϵ����ͺ������ж��Ƿ���Ҫ������������LC��
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
        else if(pa->exp>pb->exp)  //ָ����ͬ����ָ���ϴ������Ȳ�������LC��
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
    pc->next=pa?pa:pb;   //ĳ�������ȱ����꣬����һ�����ʣ�ಿ��ֱ������LC��
    return LC;
}
void Minus(LinkList LA,LinkList LB)
{//����ʽ�ļ���
    LinkList p=LB->next;    //p������LB�Ĺ���ָ�룬��ʼ��Ϊ��Ԫ���
    while(p)         //ÿ��ϵ��ȡ�෴��
    {
        p->coe*=-1;
        p=p->next;
    }
    OutputPolynomial(Add(LA, LB));
}
void Mul(LinkList LA,LinkList LB)
{//����ʽ�ĳ˷�
    LinkList pa=LA->next; //pa��pb������LA��LB�Ĺ���ָ�룬����ʼ��Ϊ��Ԫ��㣻
    LinkList pb=LB->next;
    LinkList LC;    //Ŀ�����ʽ����LC
    CreatePolynomial(LC, 0);
    LinkList temp;    //��¼�м���
    CreatePolynomial(temp, 0);
    while(pa)
    {
        while(pb)
        {
            LinkList p=new LNode;//p�Ǽ�¼�м����ĸ���ָ��
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
{//����ʽ��������
    LinkList p=L->next;  //p������L�Ĺ���ָ�룬��ʼ��Ϊ��Ԫ���
    LinkList r=NULL;  //r��ɾ�������ĸ���ָ��
    while(p)
    {
        p->coe*=p->exp;
        p->exp--;
        if(p->exp<0)  //�������ݵ�ָ�����ڵ���0
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
{//�����ַ�ѡ�����ʽ�ļӷ����������˷���������
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
    int n;    //�ܼ���n������
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
