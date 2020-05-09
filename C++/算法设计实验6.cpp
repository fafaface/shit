
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>
#define N 3000  //城市最大数量

struct point {  
    double x;
    double y;
}city[N];
int num;  //城市最大
int path[N];  //路径
double dis(int i, int j) {
    double xd, yd;
    xd = city[i].x - city[j].x;
    yd = city[i].y - city[j].y;
    return(sqrt(xd * xd + yd * yd));//勾股定理求两座城市之间的距离
}
void fun(int begin) {//最近邻的近似算法

    double mindist;//最近距离
    int vismin, temp;//最近城市, 暂时的存储空间
    int i, j=1;//下标存储变量
    path[0] = begin;//路径起点
    for (i = 0; i < num; i++)// 初始化路径
        if (i != begin) {
            path[j] = i;  j++;
        }

    for (i = 1; i < num - 1; i++) {//寻找距离path[i-1]最近的未访问城市
        mindist = 0x7ffffff;//给最近距离赋一个较大值
        vismin = 0;
        for (j = i; j < num; j++)
            if (dis(path[i - 1], path[j]) < mindist) {//找最近的城市
                mindist = dis(path[i - 1], path[j]);
                vismin = j;
            }
        temp = path[i];//交换
        path[i] = path[vismin];
        path[vismin] = temp;//保证下标靠后的城市
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

    starts = (double)clock() / CLOCKS_PER_SEC;//开始计时
    fun(0);//调用近似算法, 寻找
    times = (double)clock() / CLOCKS_PER_SEC - starts;//结束计时
    length = 0.0;    //总距离求和
    for (i = 0; i < num; i++)
        length += dis(path[i % num], path[(i + 1) % num]);
    length = 0.0;
    printf("\n输出路径:\n");
    for (i = 0; i < num; i++) {
        printf("%d:\t%d\n",i+1, path[i]);
        length += dis(path[i], path[(i + 1) % num]);
    }
    printf("\n路径长度 %lf\n", length);
    printf("所用时间: %lf\n", times);

    return 0;
}




