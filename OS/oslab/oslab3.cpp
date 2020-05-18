
#include<iostream>
#include<stdlib.h>
using namespace std;
#define Free 0 //����״̬
#define Busy 1 //����״̬
#define OK 1    //���
#define ERROR 0 //����
#define MAX_length 1000  //�������������Ϣ640KB
typedef int Status;
int tag;//��־λ  0Ϊ������     1Ϊ�ѷ���Ĺ�����

typedef struct FreAarea//����һ��������˵����ṹ
{
	float address; //������ַ
	float size;   //������С
	int flag;   //״̬
}ElemType;

typedef struct DuLNode// ���Ա��˫������洢�ṹ
{
	ElemType data;
	struct DuLNode* prior; //ǰ��ָ��
	struct DuLNode* next;  //���ָ��
}


DuLNode, * DuLinkList;
DuLinkList block_first; //������ͷ���
DuLinkList block_last;  //������β���
DuLinkList allo_first; //�ѷ�����ͷ���
DuLinkList allo_last;  //�ѷ�����β���
ElemType work[10];
Status Initblock()//������ͷ���Ŀ������ڴ�ռ�����
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
Status Initallo()//������ͷ�����ѷ����ڴ�ռ�����
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
Status Initwork()//������ͷ�����ѷ����ڴ�ռ�����
{
	cout << "��ʼ����ҵ����
		
		" << endl;
	for (int i = 0; i < 10; i++)
	{
		work[i].address= i;														
		work[i].size = rand() % ( MAX_length/ 4) + 1;											//��С����1~L/4
		work[i].flag = 0;															//״̬��0δ���䣬1�ѷ��䣬2�ѽ���
	}
	return OK;
}

Status First_fit(int request)//�״���Ӧ�㷨
{
	//Ϊ������ҵ�����¿ռ��ҳ�ʼ��
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.flag = Busy;

	DuLNode* p = block_first->next;
	while (p)
	{
		if (p->data.flag == Free && p->data.size == request)
		{//�д�Сǡ�ú��ʵĿ��п�
			p->data.flag = Busy;
			return OK;
			break;
		}
		if (p->data.flag == Free && p->data.size > request)
		{//�п��п���������������ʣ��
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


Status Alloc()//��������
{
	int request = 0;
	cout << "��������Ҫ����������С(��λ:KB)��" << endl;
	cin >> request;
	if (First_fit(request) == OK) cout << "����ɹ���" << endl;
	else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
	return OK;
}

Status free(int tag)//�������
{
	DuLNode* p = block_first;
	for (int i = 0; i <= tag; i++)
		if (p != NULL)
			p = p->next;
		else
			return ERROR;

	p->data.flag = Free;
	if (p->prior != block_first && p->prior->data.flag == Free)//��ǰ��Ŀ��п�����
	{
		p->prior->data.size += p->data.size;//�ռ�����,�ϲ�Ϊһ��
		p->prior->next = p->next;//ȥ��ԭ�����ϲ���p
		p->next->prior = p->prior;
		p = p->prior;
	}
	if (p->next != block_last && p->next->data.flag == Free)//�����Ŀ��п�����
	{
		p->data.size += p->next->data.size;//�ռ�����,�ϲ�Ϊһ��
		p->next->next->prior = p;
		p->next = p->next->next;
	}
	if (p->next == block_last && p->next->data.flag == Free)//�����Ŀ��п�����
	{
		p->data.size += p->next->data.size;
		p->next = NULL;
	}

	return OK;
}


void show()//��ʾ����������
{
	int tag = 0;
	cout << "\n����������:\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	DuLNode* p = block_first->next;
	cout << "������\t��ʼ��ַ\t������С\t״̬\n\n";
	while (p)
	{
		cout << "  " << tag++ << "\t";
		cout << "  " << p->data.address << "\t\t";
		cout << " " << p->data.size << "KB\t\t";
		if (p->data.flag == Free) cout << "����\n\n";
		else cout << "�ѷ���\n\n";
		p = p->next;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++\n\n";
}

int main()//������
{
	Initblock(); //�����ռ��
	Initallo();

	int choice;  //����ѡ����

	while (1)
	{
		show();
		cout << "���������Ĳ�����";
		cout << "\n1: �����ڴ�\n2: �����ڴ�\n0: �˳�\n";

		cin >> choice;
		if (choice == 1) Alloc(); // �����ڴ�
		else  // �ڴ����
		{
			int tag;
			cout << "��������Ҫ�ͷŵķ����ţ�" << endl;
			cin >> tag;
			free(tag);
		}
	}
}