#include<iostream> 
#include<stdlib.h> 
#include<stdio.h> 
using namespace std;
#define buffersize 3

typedef struct PCB {
    int name;		//������
    int state;		//״̬ 
    bool attribute;		//����, ����������:0 ����������:1
   
}pcb;

typedef struct QNode {
    PCB   data;
    struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
    QueuePtr  front;            //����ͷ
    QueuePtr  rear;             //����β
}LinkQueue;



LinkQueue wait, ok, producer, consumer,over;//����, ���, ������, �����߶���
char buffer[buffersize];		//������:�����name
int in = 0;						//���뻺����ָ��
int out = 0;						//ȡ�߻�����ָ��
int productnum = 0;                //��Ʒ��
int full = 0;						//�ź���full
int emptys = buffersize;			//�ź���emptys
int mutex = 1;					//�����ź�����ȷ��Ψһ����

int InitQueue(LinkQueue& Q) {//��ʼ������
    Q.front = Q.rear = new QNode;
    if (!Q.front)
        exit(0);
    Q.front->next = NULL;
    return 1;
}
int EnQueue(LinkQueue& Q, PCB e) {//����
    QueuePtr p;
    p = new QNode;
    if (!p)
        exit(0);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return 1;
}

int DeQueue(LinkQueue& Q, PCB& e) {//����
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (Q.front == Q.rear)
        return 0;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return 1;
}

int QueueEmpty(LinkQueue Q) {//�ж϶����Ƿ�Ϊ��
    if (Q.front == Q.rear)
        return 0;
    else
        return 1;
}

int P(int& s)					//P����
{
    return  s >= 1?--s : -1;
}

int V(int& s)					//V����
{
    return ++s;
}

void wake_con()						//����������
{
    if (consumer.front->next != NULL)			//���в��ղ��ܻ���
    {
        PCB p = consumer.front->next->data;	//�ȴ���ͷ������
        DeQueue(consumer, p);
        EnQueue(ok, p);
        p.state = 1;
        cout << "���������߽���, " << p.name<< "�������������" << endl;
    }
    else
        cout << "�����ߵȴ�����Ϊ��" << endl;
}
void wake_pror()						//����������
{
    if (producer.front->next != NULL)			//���в��ղ��ܻ���
    {
        PCB  p = producer.front->next->data;
        DeQueue(producer, p);
        EnQueue(ok, p);
        p.state = 1;
        cout << "���������߽���" << p.name << "�������������" << endl;
    }
    else
        cout << "�����ߵȴ�����Ϊ��" << endl;
}

void show(QNode* pcb)	//��ʾ�����е����н���
{
    if (pcb->next)
    {
        QNode* p = pcb->next;
        while (p){
            cout << "����" << p->data.name<< "\t��������:" << p->data.attribute<< "\t����״̬" << p->data.state << endl;//���������Ϣ
            p = p->next;
        }
        cout << "------------------------------" << endl;
    }
    else
    {
        cout << "����Ϊ��" << endl;
        cout << "------------------------------" << endl;
    }
}
int main() {
    bool go;
    do
    {
  
        system("cls");
        InitQueue(ok); InitQueue(wait); InitQueue(producer); InitQueue(consumer); InitQueue(over);//��ʼ������
        cout << "����" << "\t" << "״̬" << "\t" << "����" << endl;
        for (int i = 0; i < 20; ++i)//��������
        {
            PCB pcb;
            pcb.name = i + 1;
            pcb.state = 1;
            pcb.attribute= rand() % 2;
            cout << pcb.name << "\t" <<  pcb.state << "\t" <<  pcb.attribute << endl;
            EnQueue(wait, pcb);
        }
        
        while (wait.front->next!=NULL) {
            QNode* pcb = wait.front->next;
            if (pcb->data.attribute == 0)//������
            {
                if (P(emptys) >= 0 && P(mutex) >= 0)			//P���������ٽ���Դ������ִ�б����̣����ߵȴ�		
                {
                    buffer[in] = pcb->data.name;			
                    productnum++;						//��������Ʒ��Ŀ��1
                    in++;								//���뻺����ָ���1
                    in = in % buffersize;
                    EnQueue(over, pcb->data);
                    pcb->data.state = 0;						//�޸Ľ���״̬
                    cout << "�����߽���" << pcb->data.name << "������Դ�ɹ�,��Ʒ����Ϊ" << productnum << ",������ɶ���" << endl;
                    V(mutex);
                    V(full);							//V����
                 wake_con();						//����������
                }
                else									//�ȴ�
                {
                    cout << "�����߽���" << pcb->data.name<< "������Դʧ��,����ȴ�����" << endl;
                    EnQueue(producer,pcb->data);				//�����߶�β�����
                    pcb->data.state = 1;						//�޸Ľ���״̬
                }
            }
            else										//�����߽���
            {
                if (P(full) >= 0 && P(mutex) >= 0)							//P����������ִ�б����̣����򱾽��̵ȴ�
                {
                    int goods;
                    goods = buffer[out];				
                    productnum--;						//��Ŀ��1		
                    out++;								//ָ���1
                    out = out % buffersize;
                    EnQueue(over,pcb->data);					//��ɶ�β�����
                    pcb->data.state = 0;						//�޸Ľ���״̬
                    cout << "�����߽���" << pcb->data.name<< "������Դ�ɹ�,��Ʒ����Ϊ" << productnum << ",����over����" << endl;
                    V(mutex);
                    V(emptys);							//V����
                    wake_pror();						//����������
                }
                else									//�ȴ�
                {
                    cout << "�����߽���" << pcb->data.name << "������Դʧ��,����ȴ�����" << endl;
                    EnQueue(consumer,pcb->data);				//�����߶�β�����
                    pcb->data.state= 1;						//�޸Ľ���״̬
                }
            }
            DeQueue(wait, pcb->data);
            cout << "��������Ϣ����" << "���뻺����ָ��:" << in << "��ȡ�߻�����ָ��:" << out << "��������Ʒ��Ŀ" << productnum << endl;
            cout << "====����====" << endl;
            show(ok.front);
            cout << "==�����ߵȴ�==" << endl;
            show(producer.front);
            cout << "==�����ߵȴ�==" << endl;
            show(consumer.front);
            cout << "====���====" << endl;
            show(over.front);

        }
        cin >> go;
    }while (go);
    return 0;
}