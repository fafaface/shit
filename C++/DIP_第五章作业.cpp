
#include <stdio.h>
#include<cmath>
#include <cstdint>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <vector>
#include <fstream>
#include <cmath>
#include <map>
using namespace std;
/*********************************
*====================*
*==�ٵĴ���,û��ʵ�ֹ���===*
*====================*
**********************************/
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef int LONG;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

typedef struct tagRGBTRIPLE {
    BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
} RGBTRIPLE;
static FILE* inputFile;
static FILE* outputFile;

int gg[256];
int intense(const char* input) {
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("���޴��ļ�,����main�����ж����·���Ƿ���ȷ!\n");//�ļ���ȡʧ��,�����޸��ļ�·��
    }

    char header[122];
    fread(header, sizeof(char), 122, inputFile); //�������ͼ��ͷ����Ϣ

    int width = *(int*)&header[18]; //���ͼ����
    int height = abs(*(int*)&header[22]); //���ͼ��߶�
    int stride = (4 * ((8 * 3) * width) / 32); //�����е�����
    int paddingcheck = (stride % 4);
    int padding;
    if (paddingcheck != 0) { //����������ܱ�4����
        int padcalc = 0;
        for (int i = 1; padcalc < stride; i++) {
            padcalc = i * 4;
        }
        padding = padcalc - stride;
    }
    else
        padding = 0;
    char pad;
    unsigned char pixel[3];
    int g[256];
    int stastic[256];
    BYTE*  temp1 = new BYTE[width* height];
    memset(g, 0, sizeof(g));
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(unsigned char), 3, inputFile); //��ȡRBG��Ϣ,��д��pixel��
            unsigned char temp = temp1[width * j + k];
            g[temp]++;//�Ҷ�ͳ��
        }
        for (int l = 0; l < padding; l++) {
            fread(&pad, 1, 1, inputFile); //��ȡĩβ����ͼ����Ϣ
        }
    }

    for (int i = 0; i < 256; i++)
        stastic[i] = g[i] / (height * width * 1.0f);//����Ҷȷֲ��ܶ�
        // ���о��⻯���� 
    int temp[256];
    memset(gg, 0, sizeof(gg));
    for (int i = 0; i < 256; i++)
    {
        if (i == 0)
        {
            temp[0] = stastic[0];
        }
        else
        {
            temp[i] = temp[i - 1] + stastic[i];
        }
        gg[i] = (int)(255.0f * temp[i] + 0.5f);
    }
    fclose(inputFile);
    return 1;
}

int save(const char* input) {//����
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("���޴��ļ�,����main�����ж����·���Ƿ���ȷ!\n");//�ļ���ȡʧ��,�����޸��ļ�·��
    }

    char header[122];
    fread(header, sizeof(char), 122, inputFile); //�������ͼ��ͷ����Ϣ

    int width = *(int*)&header[18]; //���ͼ����
    int height = abs(*(int*)&header[22]); //���ͼ��߶�
    int stride = (4 * ((8 * 3) * width) / 32); //�����е�����
    int paddingcheck = (stride % 4);
    int padding;
    if (paddingcheck != 0) { //����������ܱ�4����
        int padcalc = 0;
        for (int i = 1; padcalc < stride; i++) {
            padcalc = i * 4;
        }
        padding = padcalc - stride;
    }
    else
        padding = 0;
    outputFile = fopen("C:/Users/yuehan lian/Desktop/ans.bmp", "wb");//��Ҫ�޸�·��
    if (outputFile == NULL) {
        printf("the file cannot be found\n");
    }
    fwrite(header, sizeof(char), 122, outputFile);
    char pad;
    unsigned char pixel[3];
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(unsigned char), 3, inputFile); //��ȡRBG��Ϣ,��д��pixel��
            unsigned char temp = *((unsigned char*)pixel + width * j + k);
           *((unsigned char *)pixel + width * j + k) = gg[temp];
           fwrite(&pixel, (sizeof(char)), 3, outputFile);//pixel�е���Ϣд�����ͼ����
        }
        for (int l = 0; l < padding; l++) {
            fread(&pad, 1, 1, inputFile); //��ȡĩβ����ͼ����Ϣ
            fwrite(&pad, 1, 1, outputFile); //�����ͼ��д��ĩβ����ͼ����Ϣ
        }
    }

    int elms_read;//ȷ��û�п����ر���ȡ 
    while (1) {
        elms_read = fread(&pad, 1, 1, inputFile);
        if (elms_read == 0) {
            break;
        }
        else {
            fwrite(&pad, 1, 1, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);
    return 1;
}


int greyScale(const char* input) {//7. ���ͬһλ��ĻҶ�ͼ��
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("���޴��ļ�,����main�����ж����·���Ƿ���ȷ!\n");//�ļ���ȡʧ��,�����޸��ļ�·��
        return 0;//����ִ��ʧ��,����0
    }

    outputFile = fopen("C:/Users/yuehan lian/Desktop/grey.bmp", "wb");
    if (outputFile == NULL) {
        printf("���ͼ���ļ�����ʧ��!\n");//�ļ�����ʧ��
        return 0;//����ִ��ʧ��,����0
    }

    char header[54];
    fread(&header, sizeof(char), 54, inputFile); //�������ͼ��ͷ����Ϣ
    fwrite(&header, sizeof(char), 54, outputFile);//д�����ͼ��ͷ����Ϣ

    int width = *(int*)&header[18]; //���ͼ����
    int height = abs(*(int*)&header[22]); //���ͼ��߶�
    int stride = (4 * ((8 * 3) * width + 31) / 32);//�����е�����
    int paddingCheck = (stride % 4);
    int padding;
    if (paddingCheck != 0) {//����������ܱ�4����
        int padCalc = 0;
        for (int i = 1; padCalc < stride; i++) {
            padCalc = i * 4;
        }
        padding = padCalc - stride;
    }
    else
        padding = 0;

    char pad;
    unsigned char pixel[3];
    unsigned char pixelEdit[3];
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(unsigned char), 3, inputFile); // ��ȡRBG��Ϣ, ��д��pixel��
            unsigned char avg = (pixel[0] + pixel[1] + pixel[2]) / (unsigned char)3;
            pixelEdit[0] = pixelEdit[1] = pixelEdit[2] = avg;//���Ҫ��Ҷ�ͼ,RGB��������Ҫ���

            fwrite(&pixelEdit, (sizeof(unsigned char)), 3, outputFile);//pixel�е���Ϣд�����ͼ����
        }
        for (int l = 0; l < padding; l++) {// ��ȡĩβ����ͼ����Ϣ
            fread(&pad, 1, 1, inputFile);
            fwrite(&pad, 1, 1, outputFile); //�����ͼ��д��ĩβ����ͼ����Ϣ
        }
    }
    int elms_read;//ȷ��û�п����ر���ȡ 
    while (1) {
        elms_read = fread(&pad, 1, 1, inputFile);
        if (elms_read == 0) {
            break;
        }
        else {
            fwrite(&pad, 1, 1, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);//�ر��ļ�~
    return 1;//ִ�гɹ�����1
}
int main(void) {//������

 int op;
 char infile[] = "C:/Users/yuehan lian/Desktop/grey.bmp";//��Ҫ�޸��ļ�·��
 //greyScale(infile);
 intense(infile);
 //save(infile);
  return 0;
}
