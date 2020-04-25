
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
*==假的代码,没有实现功能===*
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
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
    }

    char header[122];
    fread(header, sizeof(char), 122, inputFile); //获得输入图像头部信息

    int width = *(int*)&header[18]; //获得图像宽度
    int height = abs(*(int*)&header[22]); //获得图像高度
    int stride = (4 * ((8 * 3) * width) / 32); //计算行的数量
    int paddingcheck = (stride % 4);
    int padding;
    if (paddingcheck != 0) { //如果行数不能被4整除
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
            fread(pixel, sizeof(unsigned char), 3, inputFile); //读取RBG信息,并写入pixel中
            unsigned char temp = temp1[width * j + k];
            g[temp]++;//灰度统计
        }
        for (int l = 0; l < padding; l++) {
            fread(&pad, 1, 1, inputFile); //读取末尾填充的图像信息
        }
    }

    for (int i = 0; i < 256; i++)
        stastic[i] = g[i] / (height * width * 1.0f);//计算灰度分布密度
        // 进行均衡化处理 
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

int save(const char* input) {//保存
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
    }

    char header[122];
    fread(header, sizeof(char), 122, inputFile); //获得输入图像头部信息

    int width = *(int*)&header[18]; //获得图像宽度
    int height = abs(*(int*)&header[22]); //获得图像高度
    int stride = (4 * ((8 * 3) * width) / 32); //计算行的数量
    int paddingcheck = (stride % 4);
    int padding;
    if (paddingcheck != 0) { //如果行数不能被4整除
        int padcalc = 0;
        for (int i = 1; padcalc < stride; i++) {
            padcalc = i * 4;
        }
        padding = padcalc - stride;
    }
    else
        padding = 0;
    outputFile = fopen("C:/Users/yuehan lian/Desktop/ans.bmp", "wb");//需要修改路径
    if (outputFile == NULL) {
        printf("the file cannot be found\n");
    }
    fwrite(header, sizeof(char), 122, outputFile);
    char pad;
    unsigned char pixel[3];
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(unsigned char), 3, inputFile); //读取RBG信息,并写入pixel中
            unsigned char temp = *((unsigned char*)pixel + width * j + k);
           *((unsigned char *)pixel + width * j + k) = gg[temp];
           fwrite(&pixel, (sizeof(char)), 3, outputFile);//pixel中的信息写入输出图像中
        }
        for (int l = 0; l < padding; l++) {
            fread(&pad, 1, 1, inputFile); //读取末尾填充的图像信息
            fwrite(&pad, 1, 1, outputFile); //向输出图像写入末尾填充的图像信息
        }
    }

    int elms_read;//确保没有空像素被读取 
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


int greyScale(const char* input) {//7. 获得同一位深的灰度图像
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
        return 0;//函数执行失败,返回0
    }

    outputFile = fopen("C:/Users/yuehan lian/Desktop/grey.bmp", "wb");
    if (outputFile == NULL) {
        printf("输出图像文件创建失败!\n");//文件创建失败
        return 0;//函数执行失败,返回0
    }

    char header[54];
    fread(&header, sizeof(char), 54, inputFile); //获得输入图像头部信息
    fwrite(&header, sizeof(char), 54, outputFile);//写进输出图像头部信息

    int width = *(int*)&header[18]; //获得图像宽度
    int height = abs(*(int*)&header[22]); //获得图像高度
    int stride = (4 * ((8 * 3) * width + 31) / 32);//计算行的数量
    int paddingCheck = (stride % 4);
    int padding;
    if (paddingCheck != 0) {//如果行数不能被4整除
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
            fread(pixel, sizeof(unsigned char), 3, inputFile); // 读取RBG信息, 并写入pixel中
            unsigned char avg = (pixel[0] + pixel[1] + pixel[2]) / (unsigned char)3;
            pixelEdit[0] = pixelEdit[1] = pixelEdit[2] = avg;//如果要变灰度图,RGB三个分量要相等

            fwrite(&pixelEdit, (sizeof(unsigned char)), 3, outputFile);//pixel中的信息写入输出图像中
        }
        for (int l = 0; l < padding; l++) {// 读取末尾填充的图像信息
            fread(&pad, 1, 1, inputFile);
            fwrite(&pad, 1, 1, outputFile); //向输出图像写入末尾填充的图像信息
        }
    }
    int elms_read;//确保没有空像素被读取 
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
    fclose(outputFile);//关闭文件~
    return 1;//执行成功返回1
}
int main(void) {//主函数

 int op;
 char infile[] = "C:/Users/yuehan lian/Desktop/grey.bmp";//需要修改文件路径
 //greyScale(infile);
 intense(infile);
 //save(infile);
  return 0;
}
