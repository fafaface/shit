#include <GL/glut.h>
#include <stdio.h>
double xmin = 50, ymin = 50, xmax = 100, ymax = 100;
double xvmin = 150, yvmin = 150, xvmax = 400, yvmax = 400;
double x2, y2, x3, y3;
//尝试输入的线条参数是否
//符合梁友栋 - Barsky算法使用的情况
int test(double p, double q, double* t1, double* t2){
    double t = q / p;
    if (p < 0.0)
    {
        if (t > * t1) *t1 = t;
        if (t > * t2) return(false);
    }
    else if (p > 0.0) {
        if (t < *t2) *t2 = t;
        if (t < *t1) return(false);
    }

    else if (p == 0.0)  {
        if (q < 0.0) return(false);
    }
    return(true);
}

//实现梁友栋 - Barsky算法,
//对指定窗口进行裁剪
void LiangBarsky(double x0, double y0, double x1, double y1){
    double dx = x1 - x0, dy = y1 - y0, te = 0.0, tl = 1.0;
    if (test(-dx, x0 - xmin, &te, &tl))
        if (test(dx, xmax - x0, &te, &tl))
            if (test(-dy, y0 - ymin, &te, &tl))
                if (test(dy, ymax - y0, &te, &tl)) {
                    if (tl < 1.0) { x1 = x0 + tl * dx; y1 = y0 + tl * dy; }
                    if (te > 0.0) { x0 = x0 + te * dx; y0 = y0 + te * dy; }
                    double sx = (xvmax - xvmin) / (xmax - xmin);
                    double sy = (yvmax - yvmin) / (ymax - ymin);
                    double vx0 = xvmin + (x0 - xmin) * sx;
                    double vy0 = yvmin + (y0 - ymin) * sy;
                    double vx1 = xvmin + (x1 - xmin) * sx;
                    double vy1 = yvmin + (y1 - ymin) * sy;
                    glColor3f(1.0, 0.0, 0.0);
                    glBegin(GL_LINE_LOOP);
                    glVertex2f(xvmin, yvmin);
                    glVertex2f(xvmax, yvmin);
                    glVertex2f(xvmax, yvmax);
                    glVertex2f(xvmin, yvmax);
                    glEnd();
                    glColor3f(0.0, 0.0, 1.0);
                    glBegin(GL_LINES);
                    glVertex2d(vx0, vy0);
                    glVertex2d(vx1, vy1);
                    glEnd();
                }
}

//创建待裁剪窗口, 线条,
//调用梁友栋 - Barsky算法
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x2, y2);
    glVertex2d(x3, y3);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
    LiangBarsky(x2, y2, x3, y3);
    glFlush();
}
//初始化界面底色等参数
void myinit(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
   glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 499.0, 0.0, 499.0);
}
//用初始化的窗口大小创建窗口和标题
//RGBA显示模式, 管理输入事件
int main(int argc, char* argv[]){
    printf("输入线段的起始点坐标( 四个数字) : ");
    scanf("%lf%lf%lf%lf", &x2, &y2, &x3, &y3);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Line Clipping");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
}