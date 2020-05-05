#include<iostream> 
#include<stdlib.h> 
#include<stdio.h> 
using namespace std;

typedef struct PCB {
    int name;		//进程名
    int state;		//状态 
    int prior;		//优先级
    int time;		//执行时间
}PCB;

typedef struct QNode {
    PCB   data;
    struct QNode* next;
}QNode, * QueuePtr;
typedef struct {
    QueuePtr  front;            //队列头
    QueuePtr  rear;             //队列尾
}LinkQueue;

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

void Print(LinkQueue& wait, LinkQueue& ok) {
    QueuePtr p;

    if (QueueEmpty(ok)) {     //非空
        p = ok.front->next;    
        cout << "就绪队列: ";
        while (p != NULL) {
            cout << p->data.name << "   ";
            p = p->next;
        }
    }
    else
        cout << endl << "执行完毕";

    if (QueueEmpty(wait)) {   //非空   
        p = wait.front->next;
        cout << endl << "等待队列: ";
        while (p != NULL) {
            cout << p->data.name << "   ";
            p = p->next;
        }
    }
    else
        cout << endl << "执行完毕";
}
void FCFS(LinkQueue& wait, LinkQueue& ok) {
    int i = 1;
    PCB e, f;

    Print(wait, ok);

    while (QueueEmpty(wait) && QueueEmpty(ok)) {
        cout << endl << "第" << i << "次: ";
        int j = rand() % 3;
        if (j == 0) {
            DeQueue(ok, e);
            cout << "进程" << e.name << "出队" << endl;
        }
        else if (j == 1) {
            DeQueue(ok, e);
            EnQueue(ok, e);
            cout << "进程" << e.name << "进队" << endl;
        }
        else if (j == 2) {
            DeQueue(ok, e);
            EnQueue(wait, e);
            DeQueue(wait, f);
            EnQueue(ok, f);
            cout << "进程" << e.name << "进队" << endl;
        }

        Print(wait, ok);

        i++;
        cout << endl;
    }
}



int main() {
    int i;
    LinkQueue wait, ok;    

    system("cls"); 
    InitQueue(ok);  
    InitQueue(wait);
    for (i = 0; i < 10; i++) {
        PCB p;
        p.name = i + 1;
        p.prior = rand() % 10;  //0-9
        p.state = rand() % 2;   //
        p.time = rand() % 50+1;
        if (p.state)
            EnQueue(ok, p);
        else
            EnQueue(wait, p);

        cout << "进程名" << "\t" << p.name << "\t";
        cout << "优先级" << p.prior << "\t";
        if (p.state)
            cout << "状态为1" << "   ";
        else
            cout << "状态为0" << "   ";
        cout<<"所需时间" << p.time << "ms" << endl << endl;
    }
    cout << endl;
        FCFS(wait, ok);
    cout << "结束了" << endl;
    exit(0);
}