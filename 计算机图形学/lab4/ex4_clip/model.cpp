#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define LEFT_EDGE   1
#define RIGHT_EDGE  2
#define BOTTOM_EDGE 4
#define TOP_EDGE    8

struct Rectangle
{
	float xmin, xmax, ymin, ymax;
};

Rectangle  rect;
int x0, y0, x1, y1;
bool bDrawLine = true;
int width = 640, height = 480;

void LineGL(int x0, int  y0, int x1, int y1)
{
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(x0, y0);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(x1, y1);
	glEnd();
}

//求p点的编码
int CompCode(int x, int y, Rectangle rect)
{
	int code = 0x00;
	if (y < rect.ymin)
		code = code | 4;//即为1000
	if (y > rect.ymax)
		code = code | 8;//即为0100
	if (x > rect.xmax)
		code = code | 2;
	if (x < rect.xmin)
		code = code | 1;
	return code;
}

bool cohensutherlandlineclip(Rectangle  rect, int &x0, int & y0, int &x1, int &y1)
{
	bool accept, done;
	float x, y;
	accept = false;
	done = false;

	int code0, code1, codeout;
	code0 = CompCode(x0, y0, rect);
	code1 = CompCode(x1, y1, rect);
	do {
		if (!(code0 | code1))
		{
			accept = true;
			done = true;
		}
		else if (code0 & code1)
			done = true;
		else
		{
			if (code0 != 0)
				codeout = code0;
			else
				codeout = code1;

			if (codeout&LEFT_EDGE) {
				y = y0 + (y1 - y0)*(rect.xmin - x0) / (x1 - x0);
				x = (float)rect.xmin;
			}
			else if (codeout&RIGHT_EDGE) {
				y = y0 + (y1 - y0)*(rect.xmax - x0) / (x1 - x0);
				x = (float)rect.xmax;
			}
			else if (codeout&BOTTOM_EDGE) {
				x = x0 + (x1 - x0)*(rect.ymin - y0) / (y1 - y0);
				y = (float)rect.ymin;
			}
			else if (codeout&TOP_EDGE) {
				x = x0 + (x1 - x0)*(rect.ymax - y0) / (y1 - y0);
				y = (float)rect.ymax;
			}

			if (codeout == code0)
			{
				x0 = x; y0 = y;
				code0 = CompCode(x0, y0, rect);
			}
			else
			{
				x1 = x; y1 = y;
				code1 = CompCode(x1, y1, rect);
			}
		}
	} while (!done);

	return accept;
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 0.0f);
	glRectf(rect.xmin, rect.ymin, rect.xmax, rect.ymax);

	if (bDrawLine)
		LineGL(x0, y0, x1, y1);

	glFlush();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);

	rect.xmin = 100; //窗口的大小
	rect.xmax = 300;
	rect.ymin = 100;
	rect.ymax = 300;

	x0 = 300, y0 = 50, x1 = 0, y1 = 450;//裁剪前的直线端点
	printf("Press key 'c' to Clip!\n");
	printf("Please Click left button of mouse to input the points of Line!!\n");
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':
		bDrawLine = cohensutherlandlineclip(rect, x0, y0, x1, y1);
		glutPostRedisplay();//重画
		break;
	case 'x':
		exit(0);
		break;
	default:
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			if(bDrawLine)
			{
				x0 = x;
				y0 = height - y;
				bDrawLine = false;
				glutPostRedisplay();//
			}
			else
			{
				x1 = x;
				y1 = height - y;
				bDrawLine = true;				
				glutPostRedisplay();//
			}
		}
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(width, height);
	glutCreateWindow("Hello World!");

	Init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}