
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>
#define N 3000  //�����������

struct point {  
    double x;
    double y;
}city[N];
int num;  //�������
int path[N];  //·��
double dis(int i, int j) {
    double xd, yd;
    xd = city[i].x - city[j].x;
    yd = city[i].y - city[j].y;
    return(sqrt(xd * xd + yd * yd));//���ɶ�������������֮��ľ���
}
void fun(int begin) {//����ڵĽ����㷨

    double mindist;//�������
    int vismin, temp;//�������, ��ʱ�Ĵ洢�ռ�
    int i, j=1;//�±�洢����
    path[0] = begin;//·�����
    for (i = 0; i < num; i++)// ��ʼ��·��
        if (i != begin) {
            path[j] = i;  j++;
        }

    for (i = 1; i < num - 1; i++) {//Ѱ�Ҿ���path[i-1]�����δ���ʳ���
        mindist = 0x7ffffff;//��������븳һ���ϴ�ֵ
        vismin = 0;
        for (j = i; j < num; j++)
            if (dis(path[i - 1], path[j]) < mindist) {//������ĳ���
                mindist = dis(path[i - 1], path[j]);
                vismin = j;
            }
        temp = path[i];//����
        path[i] = path[vismin];
        path[vismin] = temp;//��֤�±꿿��ĳ���
    }
}

int main() {

    FILE* input;
    double length, starts, times;
    int i;
    int temps;
    input = fopen("C://Users/yuehan lian/Desktop/123.txt", "r");
    fscanf(input, "%d", &num);
    for (i = 0; i < num; i++) {
        fscanf(input, "%d %lf %lf", &temps,&(city[i].x), &(city[i].y));
    }
    fclose(input);

    starts = (double)clock() / CLOCKS_PER_SEC;//��ʼ��ʱ
    fun(0);//���ý����㷨, Ѱ��
    times = (double)clock() / CLOCKS_PER_SEC - starts;//������ʱ
    length = 0.0;    //�ܾ������
    for (i = 0; i < num; i++)
        length += dis(path[i % num], path[(i + 1) % num]);
    length = 0.0;
    printf("\n���·��:\n");
    for (i = 0; i < num; i++) {
        printf("%d:\t%d\n",i+1, path[i]);
        length += dis(path[i], path[(i + 1) % num]);
    }
    printf("\n·������ %lf\n", length);
    printf("����ʱ��: %lf\n", times);

    return 0;
}




