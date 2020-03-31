#include<iostream>
#include<windows.h>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;
unsigned char* pBmpBuf;//读入图像数据的指针

int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD* pColorTable;//颜色表指针
int biBitCount;//图像类型，每像素位数
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool readBmp(char* bmpName)
{
	FILE* fp = fopen(bmpName, "rb");//二进制读方式打开指定的图像文件
	if (fp == 0)
		return 0;

	//跳过位图文件头结构BITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	//定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//获取图像宽、高、每像素所占位数等信息
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	//定义变量，计算图像每行像素所占的字节数（必须是4的倍数）
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//灰度图像有颜色表
	if (biBitCount == 8){
		//申请颜色表所需要的空间，读颜色表进内存
	pColorTable = new RGBQUAD[256];
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);
}
	//申请位图数据所需要的空间，读位图数据进内存
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
	fclose(fp);//关闭文件
	return 1;//读取文件成功
}

//将图像数据保存至image，并进行滤波操作
void ImageData(float** image)
{
	//保存数据
	for (int i = 0; i < bmpHeight; i++)
	{
		for (int j = 0; j < bmpWidth; j++)
		{
			image[i][j] = *(pBmpBuf + i * bmpWidth + j);
		}
	}

	//滤波操作
	for (int i = 1; i < bmpHeight - 1; i++)
	{
		for (int j = 1; j < bmpWidth - 1; j++)
		{
			image[i][j] = (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j]
				+ image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]) / 9;
		}
	}

	//输出图像第一行滤波结果到控制台
	for (int p = 1; p <= 3; p++)
	{
		for (int j = 1; j < bmpWidth; j++)
		{
			cout << image[p][j];
			printf("\t");
		}
		cout << endl;
	}

}


int main()
{
	char readPath[] = "C:/change/mnmnm/bin/homework.bmp";//BMP文件路径
	readBmp(readPath);

	float** Image = new float* [bmpHeight];
	for (int i = 0; i < bmpWidth; i++){
		Image[i] = new float[bmpWidth];
	}
	ImageData(Image);
	return 0;
}