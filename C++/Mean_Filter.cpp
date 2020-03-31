#include<iostream>
#include<windows.h>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>

using namespace std;
unsigned char* pBmpBuf;//����ͼ�����ݵ�ָ��

int bmpWidth;//ͼ��Ŀ�
int bmpHeight;//ͼ��ĸ�
RGBQUAD* pColorTable;//��ɫ��ָ��
int biBitCount;//ͼ�����ͣ�ÿ����λ��
//����һ��ͼ��λͼ���ݡ����ߡ���ɫ��ָ�뼰ÿ������ռ��λ������Ϣ,����д��ָ���ļ���
bool readBmp(char* bmpName)
{
	FILE* fp = fopen(bmpName, "rb");//�����ƶ���ʽ��ָ����ͼ���ļ�
	if (fp == 0)
		return 0;

	//����λͼ�ļ�ͷ�ṹBITMAPFILEHEADER
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);
	//����λͼ��Ϣͷ�ṹ��������ȡλͼ��Ϣͷ���ڴ棬����ڱ���head��
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	//��ȡͼ����ߡ�ÿ������ռλ������Ϣ
	bmpWidth = head.biWidth;
	bmpHeight = head.biHeight;
	biBitCount = head.biBitCount;
	//�������������ͼ��ÿ��������ռ���ֽ�����������4�ı�����
	int lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
	//�Ҷ�ͼ������ɫ��
	if (biBitCount == 8){
		//������ɫ������Ҫ�Ŀռ䣬����ɫ����ڴ�
	pColorTable = new RGBQUAD[256];
	fread(pColorTable, sizeof(RGBQUAD), 256, fp);
}
	//����λͼ��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	pBmpBuf = new unsigned char[lineByte * bmpHeight];
	fread(pBmpBuf, 1, lineByte * bmpHeight, fp);
	fclose(fp);//�ر��ļ�
	return 1;//��ȡ�ļ��ɹ�
}

//��ͼ�����ݱ�����image���������˲�����
void ImageData(float** image)
{
	//��������
	for (int i = 0; i < bmpHeight; i++)
	{
		for (int j = 0; j < bmpWidth; j++)
		{
			image[i][j] = *(pBmpBuf + i * bmpWidth + j);
		}
	}

	//�˲�����
	for (int i = 1; i < bmpHeight - 1; i++)
	{
		for (int j = 1; j < bmpWidth - 1; j++)
		{
			image[i][j] = (image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j]
				+ image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]) / 9;
		}
	}

	//���ͼ���һ���˲����������̨
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
	char readPath[] = "C:/change/mnmnm/bin/homework.bmp";//BMP�ļ�·��
	readBmp(readPath);

	float** Image = new float* [bmpHeight];
	for (int i = 0; i < bmpWidth; i++){
		Image[i] = new float[bmpWidth];
	}
	ImageData(Image);
	return 0;
}