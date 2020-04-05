//多项式计算器
//因为C++兼容c，考虑到与
//课本上的算法形式的一致性，所以在C++夹杂了C语言的使用
//同时实现了与本计算器功能无关的链表定义函数

#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
//状态值
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OK 1
#define INFEASIBLE -1

using namespace std;
typedef int Status; //函数返回值状态
//结点结构
typedef struct LNode
{
    float coef;         
    int expn;           
    struct LNode *next; 
} Node, *Link;

typedef struct
{
    Link head, tail; 
    int len;         
} LinkList;

Status InitList(LinkList &L)
{
    //初始化链表
    L.head = (Link)malloc(sizeof(LNode)); //初始化头结点
    L.head->next = NULL;
    L.head->coef = 0.0;
    L.head->expn = -1; //头结点指数为-1
    L.len = 0;
    L.tail = NULL; //空表时尾指针为NULL
    return OK;
}
Status DestroyList(LinkList &L)
{
    //已知线性链表存在
    //摧毁L
    while (L.head || L.tail)
    {
        Link p;
        while (L.head->next)
        {
            p = L.head->next;
            L.head->next = p->next;
            free(p);
        }
        L.tail = NULL;
        free(L.head);
        L.head = NULL;
    }
    L.len = -1;
    return OK;
}
Status ClearList(LinkList &L)
{
    //已知L存在
    //将L清空
    Link p;
    while (L.head->next)
    {
        p = L.head->next;
        L.head->next = p->next;
        free(p);
    }
    L.tail = NULL;
    L.len = 0;
    return OK;
}
Status Remove(LinkList &L, Link &q)
{
    //删除线性链表L中的尾结点并以q返回，改变链表L的尾指针指向新的尾结点
    Link p = L.head;
    if (L.tail==NULL)
        return ERROR;
    while ((p->next)->next != NULL)
        p = p->next;
    q = L.tail;
    L.tail = p;
    return OK;
}
Status InsBefore(LinkList &L, Link &p, Link s)
{
    //已知p指向线性链表L中的一个结点，将S所指结点插入在p所指结点之前
    //并修改指针p指向新插入的结点
    Link q = L.head;
    while (q->next != p)
        q = q->next;
    s->next = p;
    q->next = s;
    p = s;
    return OK;
}
Status InsAfter(LinkList &L, Link &p, Link s)
{
    //已知p指向线性链表L中的一个结点，将s所指的结点插入在p所指结点之后
    //并修改指针p指向新插入的结点
    s->next = p->next;
    p->next = s;
    p = p->next;
    return OK;
}
/*
int ListLength(LinkList L)
{
    //好像没啥用
    return L.len;
}*/
Link PriorPos(LinkList L, Link p)
{
    //已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置
    //无前驱返回NULL
    Link q = L.head->next;
    if (q == p)
        return NULL;
    else
    {
        while (q->next != p)
            q = q->next;
    }
    return q;
}
Link NextPos(LinkList L, Link p)
{
    //已知p指向线性链表中的一个结点，返回p所指结点的直接后继的位置
    //若无后继，返回NULL
    return p->next;
} 
Status LocatePos(LinkList L, int i, Link &p){
    //返回p指示线性链表L中第i个结点的位置并返回OK，i值不合法时返回ERROR
    Link q=L.head;int j=0;
    if(i<1||i>L.len)return ERROR;
    while(j!=i){
        q=q->next;
        j++;
    }
    p=q;
    return OK;
}
Status CoefMinus(Link &L){
    //系数取反
    L->coef=-(L->coef);
    return OK;
}
Status ListTraverse(LinkList L, Status(*visit)(Link &)){
    //依次对L的每个元素调用函数visit().一旦visit()失败，则操作失败
    Link p=L.head->next;
    while(p){
        if(!visit(p))break;
        p=p->next;
    }
    if(!p)return OK;
    else return FALSE;
}
Status InsFirst(LinkList &L, Link h, Link s)
{
    //已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
    
    s->next = h->next;
    h->next = s;
    L.len++;
    if(L.tail==NULL)L.tail=s;
}
int compare(int a, int b){
   //比较两个数大小
    if (a > b)
        return 1;
    if (a == b)
        return 0;
    if (a < b)
        return -1;
}
Status DelFirst(LinkList &L, Link h, Link &q)
{   //已知第一个多项式第一个结点存在
    //h是L的头结点，删除第一个结点并以q返回
    if(h->next==NULL)exit(INFEASIBLE);
    else{
        q=h->next;
        h->next=h->next->next;
        q->next=NULL;//删除的结点的指针与置NULL,以防出现不必要的问题
        L.len--;
    }
    return OK;
}
void FreeNode(Link &p)
{
    free(p);
}
Status ListEmpty(LinkList L)
{
    if (L.len == 0)
        return OK;
    else
        return FALSE;
}
Status Append(LinkList &L, Link S){
    //将指针s所指向（彼此以指针相连）的一串结点链接在线性链表L的最后一个结点
    //需要遍历s以求得长度和尾指针
    Link p=S;
    int i=1;
    if(L.tail==NULL)L.head->next=S;//如果L为空表，直接连链接到头结点后面
    else L.tail->next = S;
    while(p->next){
        i++;
        p=p->next;
    }
    L.tail=p;
    L.len=L.len+i;
    return OK;
}
Link GetHead(LinkList L)
{
    //返回P的头结点L
    return L.head;
} 
Link GetLast(LinkList L){
    //返回L 的尾结点
    return L.tail;
}
Status SetCurElem(Link &m, Node n){
    //已知m指向线性链表中的一个结点，用n更新m所指结点中数据元素的值

    m->coef = n.coef;
    m->expn = n.expn;
    return OK;
}
bool Equal(Node a, Node b){
    //判断两个结点中数据元素的值是否相等
    if (a.coef == b.coef && a.expn == b.expn)
        return OK;
    else
        return FALSE;
}
float GetCurCoef(Link p){
    //已知结点p存在
    //返回p所指的系数的值
    if (p != NULL)
        return p->coef;
    else
        exit(INFEASIBLE);
}
int GetCurExpn(Link p){
    //已知结点p存在
    //返回p所指向的指数的值
    if (p != NULL)
        return p->expn;
    else
        exit(INFEASIBLE);
}
int LocateElem(LinkList L, Node e, bool (*cmp)(Node, Node)){
    //如果线性表中又与e相等的结点，返回true
    //否则返回false
    Link p = GetHead(L);
    p = p->next;
    while (p)
    {
        if ((*cmp)(*p, e))
            return TRUE;
        else
            p = p->next;
    }
    return FALSE;
}
Link MakeNode(Node e)
{
    //制造结点数据值等于e，返回指向该节点的指针
    Link p = (Link)malloc(sizeof(LNode));
    p->coef = e.coef;
    p->expn = e.expn;
    //p->next = e.next;
    return p;
}
void Sort(LinkList &L)
{
    //对多项式进行排序，这里注意尾指针也要跟着进行变化
    Link r;
    Link p = L.head;
    p = p->next;
    r = L.head;
    int j;
    for (int i = 1; i < L.len; i++)
    {
        for (j = 1; j <= L.len - i; j++)
        {
            if (p->expn >= (p->next)->expn)
            {
                r->next=p->next;
                p->next=p->next->next;
                r->next->next=p;
                r=r->next;
            }
            else
            {
                r = r->next;
                p = p->next;
            }

        }
        if(i==1)L.tail=p;
        p = L.head->next;
        r = L.head;
    }
    while(p&&p->next){
        if(p->expn==p->next->expn){
            r=p->next;
            p->coef+=r->coef;
            p->next=r->next;
            free(r);
            L.len--;
        }
        else{
            p=p->next;
        }
    }
}
void CreatPolyn(LinkList &L, int m)
{
    //创建多项式LL
    Node e;
    Link h, s;
    InitList(L);
    h = GetHead(L);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%f,%d", &(e.coef), &(e.expn));
        if (!LocateElem(L, e, Equal)&&e.coef)
        {
            s = MakeNode(e);
            if(L.tail==NULL)L.tail=s;
            InsFirst(L, h, s); 
        }
    }
    Sort(L);
}
void PrintPolyn(LinkList L)
{ //输出多项式L
    int i = 1;
    Link p = GetHead(L);
    Sort(L);

    cout << "Pn(x)=";
    while (p->next)
    {
        if (i == 1)
        {
            printf("%.1fX^%d", p->next->coef, p->next->expn);
            p = p->next;
            i = 0;
        }
        else
        {
            if(p->next->coef<0)printf(" %.1fX^%d", p->next->coef, p->next->expn);
            else printf(" + %.1fX^%d", p->next->coef, p->next->expn);
            p = p->next;
        }
    }
    
    if(!L.head->next)cout<<"NULL";
    cout<<endl;
}
int PolynLength(LinkList P)
{ //返回一元多项式P中的项数
    return P.len;
}

void AddPolyn(LinkList &Pa, LinkList &Pb)
{   //两个多项式升幂排列，多项式相加
    //Pa=Pa+Pb，清空Pb
    float sum;
    Link ha = GetHead(Pa);
    Link hb = GetHead(Pb); 
    Link qa = NextPos( Pa , ha );
    Link qb = NextPos( Pb , hb ); 
    while (qa && qb)
    { 
        switch (compare(GetCurExpn(qa), GetCurExpn(qb)))
        {
        case -1: //qa->Expn < qb-<Expn
            ha = qa;
            qa = NextPos(Pa, qa);
            break; 
        case 0: //qa->Expn = qb->Expn
            sum = GetCurCoef(qa) + GetCurCoef(qb); //系数相加
            if (sum != 0.0)
            {
                qa->coef = sum;
                ha = qa; 
            }
            else
            {
                DelFirst(Pa, ha, qa);
                FreeNode(qa); 
            }
            DelFirst(Pb, hb, qb);

            FreeNode(qb);
            qb = NextPos(Pb, hb);
            qa = NextPos(Pa, ha);
            break;
        case 1: //qa->Expn < qb-<Expn
            DelFirst(Pb, hb, qb);
            InsFirst(Pa, ha, qb);
            qb = NextPos(Pb, hb);
            ha = NextPos(Pa, ha);
            break; 
        }
    }
    
    if (!ListEmpty(Pb)){//Pb如果不为空，把Pb连接到Pa后面
        Append(Pa, qb);
        qb=NULL;
    }
    Pb.head->next=NULL;
    ClearList(Pb);
}
void SubtractPolyn(LinkList &Pa, LinkList &Pb){
    //多项式相减 Pa = Pa - Pb 
    //完成后删除多项式Pb
    ListTraverse(Pb,CoefMinus);//对Pb取负操作
    AddPolyn(Pa,Pb);//减法转化为加法
}
void MultiplyLink(LinkList Pa,Link r, LinkList &Pb){
    //多项式Pb = Pa × r
    Link p=Pa.head->next;
    Link q=Pb.head->next;
    while(p){
        q->coef=(p->coef)*(r->coef);//系数相乘
        q->expn=(p->expn)+(r->expn);//指数相加
        p=p->next;
        q=q->next;
    }
}
void CopyList(LinkList &Pa, LinkList Pb){
    //复制多项式Pb 到Pa
    Link r=Pa.head;
    Link s,p=Pb.head->next;
    while(p){
        s=MakeNode(*p);
        InsFirst(Pa, r, s); 
        p=p->next;
        r=r->next;
    }
    Sort(Pa);
}
void MultiplyPolyn(LinkList &Pa, LinkList &Pb){
    //Pa,Pb两个链表升幂不重复排列
    //求:Pa = Pa × Pb, 完成后删除多项式Pb
    int i=1;
    LinkList M,SUM;
    InitList(SUM);
    InitList(M);//保存相乘的结果
    CopyList(M,Pa);
    Link p=Pb.head->next;
    while(p){
        MultiplyLink(Pa,p,M);
        AddPolyn(SUM,M);
        p=p->next; 
        CopyList(M,Pa);
        i++;
    }
    ClearList(Pa);
    Pa.head->next=SUM.head->next;
    Pa.len=SUM.len;
    Pa.tail=SUM.tail;
    SUM.head->next=NULL;
    DestroyList(SUM);DestroyList(M);
}
float evaluation(LinkList L, float x){
    float sum=0.0;
    Link p=L.head->next;
    while(p){
        sum += (p->coef) * powf( x , p->expn );
        p=p->next;
    }
    return sum;
}
int main()
{    
    LinkList L, M;
    int i=0;
    float X;
    while(i==0){
	
 		cout<<"****************calculator*****************************"<<endl;
 		cout<<"*                                                     *"<<endl;
    	cout<<"* your function: 1.Plus                               *"<<endl;
		cout<<"*                2.Sub                                *"<<endl;
		cout<<"*                3.Multiply                           *"<<endl;
		cout<<"*                4.evaluation                         *"<<endl;
		cout<<"*                5.exit                               *"<<endl;
		cout<<"*                                                     *"<<endl;
		cout<<"*******************************************************"<<endl; 
		cout<<"Please chose one:";
		cin>>i;
		switch(i){
			case 1:
				cout<<"Enter your first polynome:"<<endl;
				CreatPolyn(L,5);       //在这里规定加法中第一个多项式的项数
                cout<<"Your first polynome: ";
                PrintPolyn(L);
				cout<<"Enter your second polynome:"<<endl;
				CreatPolyn(M,2);       //在这里规定加法中第二个多项式的项数
                cout<<"Your second polynome: ";
                PrintPolyn(M);
				AddPolyn(L,M);
				cout<<"The result: ";
				PrintPolyn(L);
				break;
			case 2:
				cout<<"Enter your first polynome:"<<endl;
				CreatPolyn(L,5);       //在这里规定减法中第一个多项式的项数
                cout<<"Your first polynome: ";
                PrintPolyn(L);
				cout<<"Enter your second polynome:"<<endl;
				CreatPolyn(M,4);       //在这里规定减法中第二个多项式的项数
                cout<<"Your second polynome: ";
                PrintPolyn(M);
				SubtractPolyn(L,M);
				cout<<"The result: ";
				PrintPolyn(L);
				break;
			case 3:
				cout<<"Enter your first polynome:"<<endl;
				CreatPolyn(L,5);       //在这里规定乘法中第一个多项式的项数
                cout<<"Your first polynome: ";
                PrintPolyn(L);
				cout<<"Enter your second polynome:"<<endl;
				CreatPolyn(M,2);       //在这里规定乘法中第二个多项式的项数
                cout<<"Your second polynome: ";
                PrintPolyn(M);
				MultiplyPolyn(L, M);
				cout<<"The result: ";
				PrintPolyn(L);
				break;
            case 4:
                cout<<"Enter your polynome:"<<endl;
				CreatPolyn(L,5);       //在这里规定多项式的项数
                cout<<"Your polynome: ";
                PrintPolyn(L);
                cout<<"Enter the X: ";
                cin>>X;
                cout<<"Pn("<<X<<")= ";
                cout<<evaluation(L,X)<<endl; 
                break;
			case 5:
				return 0;
			default: cout<<"ERROR"; 
    	}
    	
    	i=0;
    	system("pause");
    	system("cls");
    }
    return 0;
}
