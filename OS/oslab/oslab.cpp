// oslab.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* file;
bool flag = 1;

//现场
typedef struct sce {
    int midresult;
    int times;
}scen;

//PCB
typedef struct pcb_type {
    char name[20];
    int pid;
    int (*fp)();
    scen scene;
    int priority;
    int status;
    struct pcb_type* next;
}pcb;

//按优先级入列
pcb* inqueue(pcb* head, pcb* apcb) {
    pcb* p = head;
    while (p->next !=NULL)
    {
        if (p->next->priority < apcb->priority)
            break;
        p = p->next;
    }
    if (p->next == NULL)
        p->next = apcb;
    else {
        apcb->next = p->next;
        p->next = apcb;
    }
    return head;
}

//出队列
pcb* outqueue(pcb* head){
    pcb* p = head->next;
    head->next = p->next;
    p->next = NULL;
    return p;
}

//判断队列是否空
bool emptyqueue(pcb* head) {
    if (head->next == NULL)
        return 0;
    else return 1;
}

//生成随机数
int Random()
{
    srand(time(0));
    return rand() % 10 + 1;
}
int main()
{
  //  printf("%d\n", 181002222 % 3); 做任务0 :先进先出调度算法

}

