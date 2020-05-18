#include<iostream>
#include<stdlib.h>
using namespace std;
#define Free 0 //����״̬
#define Busy 1 //����״̬
#define OK 1    //���
#define ERROR 0 //����
#define MAX_length 640  //�������������Ϣ640KB
typedef int Status;
int flag;//��־λ  0Ϊ������     1Ϊ�ѷ���Ĺ�����

typedef struct FreAarea//����һ��������˵����ṹ
{
	long size;   //������С
	long address; //������ַ
	int state;   //״̬
}ElemType;


typedef struct DuLNode// ���Ա��˫������洢�ṹ
{
	ElemType data;
	struct DuLNode* prior; //ǰ��ָ��
	struct DuLNode* next;  //���ָ��
}


DuLNode, * DuLinkList;
DuLinkList block_first; //ͷ���
DuLinkList block_last;  //β���
ElemType work[11];//��ҵ����
Status Alloc(int ch , int request);//�ڴ����
Status free(int); //�ڴ����
Status First_fit(int);//�״���Ӧ�㷨
Status Best_fit(int); //�����Ӧ�㷨
//Status Worst_fit(int); //�����Ӧ�㷨
void show();//�鿴����
Status Initblock();//�����ռ��
Status Initwork();//��ʼ����ҵ����


Status Initblock()//������ͷ�����ڴ�ռ�����
{
	block_first = (DuLinkList)malloc(sizeof(DuLNode));
	block_last = (DuLinkList)malloc(sizeof(DuLNode));
	block_first->prior = NULL;
	block_first->next = block_last;
	block_last->prior = block_first;
	block_last->next = NULL;
	block_last->data.address = 0;
	block_last->data.size = MAX_length;
	block_last->data.state = Free;
	return OK;
}

Status Initwork()
{
	work[0].address = 1; work[0].size = 130; work[0].state = 1;//����
	work[1].address = 2; work[1].size = 60; work[1].state = 1;//����
	work[2].address = 3; work[2].size = 100; work[2].state = 1;//����
	work[3].address = 2; work[3].size = 60; work[3].state = 0;//�ͷ�
	work[4].address = 4; work[4].size = 200; work[4].state = 1;//����
	work[5].address = 3; work[5].size = 100; work[5].state = 0;//�ͷ�
	work[6].address = 1; work[6].size = 130; work[6].state = 0;//�ͷ�
	work[7].address = 5; work[7].size = 140; work[7].state = 1;//����
	work[8].address = 6; work[8].size = 60; work[8].state = 1;//����
	work[9].address = 7; work[9].size = 50; work[9].state = 1;//����
	work[10].address = 6; work[10].size = 60; work[10].state = 0;//�ͷ�
	return OK;
}


Status Alloc(int ch, int request)//��������
{
	if (request < 0 || request == 0)
	{
		cout << "�����С�����ʣ������ԣ�" << endl;
		return ERROR;
	}

	if (ch == 2) //ѡ�������Ӧ�㷨
	{
		if (Best_fit(request) == OK) cout << "����ɹ���" << endl;
		else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
		return OK;
	}
	else //Ĭ���״���Ӧ�㷨
	{
		if (First_fit(request) == OK) cout << "����ɹ���" << endl;
		else cout << "�ڴ治�㣬����ʧ�ܣ�" << endl;
		return OK;
	}
}


Status First_fit(int request)//�״���Ӧ�㷨
{
	//Ϊ������ҵ�����¿ռ��ҳ�ʼ��
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;

	DuLNode* p = block_first->next;
	while (p)
	{
		if (p->data.state == Free && p->data.size == request)
		{//�д�Сǡ�ú��ʵĿ��п�
			p->data.state = Busy;
			return OK;
			break;
		}
		if (p->data.state == Free && p->data.size > request)
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


Status Best_fit(int request)//�����Ӧ�㷨
{
	int ch; //��¼��Сʣ��ռ�
	DuLinkList temp = (DuLinkList)malloc(sizeof(DuLNode));
	temp->data.size = request;
	temp->data.state = Busy;
	DuLNode* p = block_first->next;
	DuLNode* q = NULL; //��¼��Ѳ���λ��

	while (p) //��ʼ����С�ռ�����λ��
	{
		if (p->data.state == Free && (p->data.size >= request))
		{
			if (q == NULL)
			{
				q = p;
				ch = p->data.size - request;
			}
			else if (q->data.size > p->data.size)
			{
				q = p;
				ch = p->data.size - request;
			}
		}
		p = p->next;
	}

	if (q == NULL) return ERROR;//û���ҵ����п�
	else if (q->data.size == request)
	{
		q->data.state = Busy;
		return OK;
	}
	else
	{
		temp->prior = q->prior;
		temp->next = q;
		temp->data.address = q->data.address;
		q->prior->next = temp;
		q->prior = temp;
		q->data.address += request;
		q->data.size = ch;
		return OK;
	}
	return OK;
}


Status free(int flag)//�������
{
	DuLNode* p = block_first;
	while (p != NULL) {
		p = p->next;
		if (p->data.size == flag)
			break;
	}
	p->data.state = Free;
	if (p->prior != block_first && p->prior->data.state == Free)//��ǰ��Ŀ��п�����
	{
		p->prior->data.size += p->data.size;//�ռ�����,�ϲ�Ϊһ��
		p->prior->next = p->next;//ȥ��ԭ�����ϲ���p
		p->next->prior = p->prior;
		p = p->prior;
	}
	if (p->next != block_last && p->next->data.state == Free)//�����Ŀ��п�����
	{
		p->data.size += p->next->data.size;//�ռ�����,�ϲ�Ϊһ��
		p->next->next->prior = p;
		p->next = p->next->next;
	}
	if (p->next == block_last && p->next->data.state == Free)//�����Ŀ��п�����
	{
		p->data.size += p->next->data.size;
		p->next = NULL;
	}

	return OK;
}


void show()//��ʾ����������
{
	int flag = 0;
	cout << "\n����������:\n";
	cout << "++++++++++++++++++++++++++++++++++++++++++++++\n\n";
	DuLNode* p = block_first->next;
	cout << "������\t��ʼ��ַ\t������С\t״̬\n\n";
	while (p)
	{
		cout << "  " << flag++ << "\t";
		cout << "  " << p->data.address << "\t\t";
		cout << " " << p->data.size << "KB\t\t";
		if (p->data.state == Free) cout << "����\n\n";
		else cout << "�ѷ���\n\n";
		p = p->next;
	}
	cout << "++++++++++++++++++++++++++++++++++++++++++++++\n\n";
}


void main()//������
{
	int ch;//�㷨ѡ����
	cout << "��������ʹ�õ��ڴ�����㷨��\n";
	cout << "(1)�״���Ӧ�㷨\n(2)�����Ӧ�㷨\n";

	cin >> ch;
	while (ch < 1 || ch>2)
	{
		cout << "�������������������ʹ�õ��ڴ�����㷨��\n";
		cin >> ch;
	}

	Initblock(); //�����ռ��
	int choice;  //����ѡ����
	Initwork(); //�����ռ��
	for(int i=0;i<11;++i)
	{
		show();
		cout << endl << "======================" << endl;
		choice = work[i].state;
		if (choice == 1) {

			Alloc(ch,work[i].size); // �����ڴ�
			cout << "��ҵ" << work[i].address << "������" << work[i].size << "KB" << endl;
		} 
		else  // �ڴ����
		{
			int flag;
			flag = work[i].size;
			free(flag);
			cout << "��ҵ" << work[i].address << "�ͷ���" << work[i].size << "KB" << endl;
		}
	}
	cout <<endl<< "���γ����ѽ���,�����������ڴ�������! " << endl;
	show();
}