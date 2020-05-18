#include<iostream> 
#include<stdlib.h> 
#include<stdio.h> 
using namespace std;
#define buffersize 3

typedef struct PCB {
    int name;		//进程名
    int state;		//状态 
    bool attribute;		//属性, 属于生产者:0 属于消费者:1
   
}pcb;

typedef struct QNode {
    PCB   data;
    struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
    QueuePtr  front;            //队列头
    QueuePtr  rear;             //队列尾
}LinkQueue;



LinkQueue wait, ok, producer, consumer,over;//就绪, 完成, 生产者, 消费者队列
char buffer[buffersize];		//缓冲区:填进程name
int in = 0;						//放入缓冲区指针
int out = 0;						//取走缓冲区指针
int productnum = 0;                //产品数
int full = 0;						//信号量full
int emptys = buffersize;			//信号量emptys
int mutex = 1;					//互斥信号量，确保唯一操作

int InitQueue(LinkQueue& Q) {//初始化队列
    Q.front = Q.rear = new QNode;
    if (!Q.front)
        exit(0);
    Q.front->next = NULL;
    return 1;
}
int EnQueue(LinkQueue& Q, PCB e) {//进队
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

int DeQueue(LinkQueue& Q, PCB& e) {//出队
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

int QueueEmpty(LinkQueue Q) {//判断队列是否为空
    if (Q.front == Q.rear)
        return 0;
    else
        return 1;
}

int P(int& s)					//P操作
{
    return  s >= 1?--s : -1;
}

int V(int& s)					//V操作
{
    return ++s;
}

void wake_con()						//唤醒消费者
{
    if (consumer.front->next != NULL)			//队列不空才能唤醒
    {
        PCB p = consumer.front->next->data;	//等待队头出进程
        DeQueue(consumer, p);
        EnQueue(ok, p);
        p.state = 1;
        cout << "唤醒消费者进程, " << p.name<< "，插入就绪队列" << endl;
    }
    else
        cout << "消费者等待队列为空" << endl;
}
void wake_pror()						//唤醒消费者
{
    if (producer.front->next != NULL)			//队列不空才能唤醒
    {
        PCB  p = producer.front->next->data;
        DeQueue(producer, p);
        EnQueue(ok, p);
        p.state = 1;
        cout << "唤醒生产者进程" << p.name << "，插入就绪队列" << endl;
    }
    else
        cout << "生产者等待队列为空" << endl;
}

void show(QNode* pcb)	//显示队列中的所有进程
{
    if (pcb->next)
    {
        QNode* p = pcb->next;
        while (p){
            cout << "进程" << p->data.name<< "\t进程类型:" << p->data.attribute<< "\t进程状态" << p->data.state << endl;//输出进程信息
            p = p->next;
        }
        cout << "------------------------------" << endl;
    }
    else
    {
        cout << "队列为空" << endl;
        cout << "------------------------------" << endl;
    }
}
int main() {
    bool go;
    do
    {
  
        system("cls");
        InitQueue(ok); InitQueue(wait); InitQueue(producer); InitQueue(consumer); InitQueue(over);//初始化队列
        cout << "进程" << "\t" << "状态" << "\t" << "类型" << endl;
        for (int i = 0; i < 20; ++i)//创建进程
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
            if (pcb->data.attribute == 0)//生产者
            {
                if (P(emptys) >= 0 && P(mutex) >= 0)			//P操作申请临界资源，继续执行本进程，或者等待		
                {
                    buffer[in] = pcb->data.name;			
                    productnum++;						//缓冲区产品数目加1
                    in++;								//放入缓冲区指针加1
                    in = in % buffersize;
                    EnQueue(over, pcb->data);
                    pcb->data.state = 0;						//修改进程状态
                    cout << "生产者进程" << pcb->data.name << "申请资源成功,产品总数为" << productnum << ",进入完成队列" << endl;
                    V(mutex);
                    V(full);							//V操作
                 wake_con();						//唤醒消费者
                }
                else									//等待
                {
                    cout << "生产者进程" << pcb->data.name<< "申请资源失败,进入等待队列" << endl;
                    EnQueue(producer,pcb->data);				//生产者队尾入进程
                    pcb->data.state = 1;						//修改进程状态
                }
            }
            else										//消费者进程
            {
                if (P(full) >= 0 && P(mutex) >= 0)							//P操作，继续执行本进程，否则本进程等待
                {
                    int goods;
                    goods = buffer[out];				
                    productnum--;						//数目减1		
                    out++;								//指针加1
                    out = out % buffersize;
                    EnQueue(over,pcb->data);					//完成队尾入进程
                    pcb->data.state = 0;						//修改进程状态
                    cout << "消费者进程" << pcb->data.name<< "申请资源成功,产品总数为" << productnum << ",进入over队列" << endl;
                    V(mutex);
                    V(emptys);							//V操作
                    wake_pror();						//唤醒生产者
                }
                else									//等待
                {
                    cout << "消费者进程" << pcb->data.name << "申请资源失败,进入等待队列" << endl;
                    EnQueue(consumer,pcb->data);				//消费者队尾入进程
                    pcb->data.state= 1;						//修改进程状态
                }
            }
            DeQueue(wait, pcb->data);
            cout << "缓冲区信息如下" << "放入缓冲区指针:" << in << "，取走缓冲区指针:" << out << "缓冲区产品数目" << productnum << endl;
            cout << "====就绪====" << endl;
            show(ok.front);
            cout << "==生产者等待==" << endl;
            show(producer.front);
            cout << "==消费者等待==" << endl;
            show(consumer.front);
            cout << "====完成====" << endl;
            show(over.front);

        }
        cin >> go;
    }while (go);
    return 0;
}