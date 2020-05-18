
#include<iostream>
#include<stdlib.h>
using namespace std;
#define Free 0 //空闲状态
#define Busy 1 //已用状态
#define OK 1    //完成
#define ERROR 0 //出错
#define MAX_length 1000  //定义最大主存信息640KB
typedef int Status;
int tag;//标志位  0为空闲区     1为已分配的工作区

typedef struct FreAarea//定义一个空闲区说明表结构
{
	float address; //分区地址
	float size;   //分区大小
	int flag;   //状态
}ElemType;

typedef struct DuLNode// 线性表的双向链表存储结构
{
	ElemType data;
	struct DuLNode* prior; //前趋指针
	struct DuLNode* next;  //后继指针
}


DuLNode, * DuLinkList;
DuLinkList block_first; //空闲区头结点
DuLinkList block_last;  //空闲区尾结点
DuLinkList allo_first; //已分配区头结点
DuLinkList allo_last;  //已分配区尾结点
ElemType work[10];
Status Initblock()//开创带头结点的空闲区内存空间链表
{
	block_first = (DuLinkList)malloc(sizeof(DuLNode));
	block_last = (DuLinkList)malloc(sizeof(DuLNode));
	block_first->prior = NULL;
	block_first->next = block_last;
	block_last->prior = block_first;
	block_last->next = NULL;
	block_last->data.address = 0;
	block_last->data.size = MAX_length;
	block_last->data.flag = Free;
	return OK;
}
Status Initallo()//开创带头结点的已分配内存空间链表
{
	allo_first = (DuLinkList)malloc(sizeof(DuLNode));
	allo_last = (DuLinkList)malloc(sizeof(DuLNode));
	allo_first->prior = NULL;
	allo_first->next = allo_last;
	allo_last->prior = allo_first;
	allo_last->next = NULL;
	allo_last->data.address = 0;
	allo_last->data.size = 0;
	allo_last->data.flag = Free;
	return OK;
}
Status Initwork()//开创带头结点的已分配内存空间链表
{
	cout << "初始化作业队列
		
		" << endl;
	for (int i = 0; i < 10; i++)
	{
		work[i].address= i;														
		work[i].size = rand() % ( MAX_length/ 4) + 1;											//大小：在1~L/4
		work[i].flag = 0;															//状态：0未分配，1已分配，2已结束
	}
	return OK;
}

Status First_fit(int request)//首次适应算法
{
	//为申请作业开辟新空间且初始化
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.flag = Busy;

	DuLNode* p = block_first->next;
	while (p)
	{
		if (p->data.flag == Free && p->data.size == request)
		{//有大小恰好合适的空闲块
			p->data.flag = Busy;
			return OK;
			break;
		}
		if (p->data.flag == Free && p->data.size > request)
		{//有空闲块能满足需求且有剩余
			temp->prior = p->prior;
			temp->next = p;
			temp->data.address = p->data.address;
			p->prior->next = temp;
			p->prior = temp;
			p->data.address = temp->data.address + temp->data.size;
			p->data.size -= request;
			return OK;
			break;
		}
		p = p->next;
	}
	return ERROR;
}


Status Alloc()//分配主存
{
	int request = 0;
	cout << "请输入需要分配的主存大小(单位:KB)：" << endl;
	cin >> request;
	if (First_fit(request) == OK) cout << "分配成功！" << endl;
	else cout << "内存不足，分配失败！" << endl;
	return OK;
}

Status free(int tag)//主存回收
{
	DuLNode* p = block_first;
	for (int i = 0; i <= tag; i++)
		if (p != NULL)
			p = p->next;
		else
			return ERROR;

	p->data.flag = Free;
	if (p->prior != block_first && p->prior->data.flag == Free)//与前面的空闲块相连
	{
		p->prior->data.size += p->data.size;//空间扩充,合并为一个
		p->prior->next = p->next;//去掉原来被合并的p
		p->next->prior = p->prior;
		p = p->prior;
	}
	if (p->next != block_last && p->next->data.flag == Free)//与后面的空闲块相连
	{
		p->data.size += p->next->data.size;//空间扩充,合并为一个
		p->next->next->prior = p;
		p->next = p->next->next;
	}
	if (p->next == block_last && p->next->data.flag == Free)//与最后的空闲块相连
	{
		p->data.size += p->next->data.size;
		p->next = NULL;
	}

	return OK;
}


void show()//显示主存分配情况
{
	int tag = 0;
	cout << "\n主存分配情况:\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	DuLNode* p = block_first->next;
	cout << "分区号\t起始地址\t分区大小\t状态\n\n";
	while (p)
	{
		cout << "  " << tag++ << "\t";
		cout << "  " << p->data.address << "\t\t";
		cout << " " << p->data.size << "KB\t\t";
		if (p->data.flag == Free) cout << "空闲\n\n";
		else cout << "已分配\n\n";
		p = p->next;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++\n\n";
}

int main()//主函数
{
	Initblock(); //开创空间表
	Initallo();

	int choice;  //操作选择标记

	while (1)
	{
		show();
		cout << "请输入您的操作：";
		cout << "\n1: 分配内存\n2: 回收内存\n0: 退出\n";

		cin >> choice;
		if (choice == 1) Alloc(); // 分配内存
		else  // 内存回收
		{
			int tag;
			cout << "请输入您要释放的分区号：" << endl;
			cin >> tag;
			free(tag);
		}
	}
}