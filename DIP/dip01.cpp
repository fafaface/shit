
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
/*********************************
*====================*
*==BMP文件结构定义开始===*
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
/*********************************
*====================*
*==BMP文件结构定义结束===*
*====================*
**********************************/

/*********************************
*====================*
*==各个功能函数定义开始===*
*====================*
**********************************/

int read(const char* input) {// 1.读取图像
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
    }
    char header[122];
    fread(&header, sizeof(char), 122, inputFile); //获得图像头部信息
    int width = *(int*)&header[18]; //获得图像宽度
    int height = abs(*(int*)&header[22]); //获得图像高度
    printf("宽度=%d\t长度=%d\n", width, height);//功能1实现
    return 1;//成功,返回1
}

int save(const char* input) {// 2.保存图像
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
    }

    outputFile = fopen("C:/Users/yuehan lian/Desktop/save.bmp", "wb");
    if (outputFile == NULL) {
        printf("输出图像文件创建失败!\n");//文件创建失败
        return 0;//函数执行失败,返回0
    }
    char header[122];
    fread(&header, sizeof(char), 122, inputFile); //获得输入图像头部信息
    fwrite(&header, sizeof(char), 122, outputFile);//写进输出图像头部信息

    int width = *(int*)&header[18]; //获得图像宽度
    int height = abs(*(int*)&header[22]);//获得图像高度
    int stride = ((4 * ((8 * 3) * width) + 31) / 32); //计算行的数量
    int paddingCheck = (stride % 4);
    int padding;
    if (paddingCheck != 0) { //如果行数不能被4整除
        int padCalc = 0;
        for (int i = 1; padCalc < stride; i++) {
            padCalc = i * 4;
        }
        padding = padCalc - stride;
    }
    else
        padding = 0;

    char pad;
    char pixel[3];
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(char), 3, inputFile); //读取RBG信息,并写入pixel中
            fwrite(&pixel, (sizeof(char)), 3, outputFile);//pixel中的信息写入输出图像中
        }
        for (int l = 0; l < padding; l++) { 
            fread(&pad, 1, 1, inputFile); //读取末尾填充的图像信息
            fwrite(&pad, 1, 1, outputFile); //向输出图像写入末尾填充的图像信息
        }
    }
    int elms_read; //确保没有空像素被读取 
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

int show(const char* input) {//3. 显示图像信息
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
    }

    char header[54];
    fread(&header, sizeof(char), 54, inputFile);//获得输入图像头部信息

    int width = *(int*)&header[18];//获得图像宽度
    int height = abs(*(int*)&header[22]); //获得图像高度
    int stride = (4 * ((8 * 3) * width) / 32);//计算行的数量
    int paddingCheck = (stride % 4);
    int padding;
    if (paddingCheck != 0) { //如果行数不能被4整除
        int padCalc = 0;
        for (int i = 1; padCalc < stride; i++) {
            padCalc = i * 4;
        }
        padding = padCalc - stride;
    }
    else
        padding = 0;
  
    char pad;
    char pixel[3];
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(char), 3, inputFile); //读取RBG信息,并写入pixel中
        }
        for (int l = 0; l < padding; l++) {//pixel中的信息写入输出图像中
            fread(&pad, 1, 1, inputFile);  //读取填充的图像信息
        }
    }
    int elms_read;//确保没有空像素被读取 
    while (1) {
        elms_read = fread(&pad, 1, 1, inputFile);
        if (elms_read == 0) {
            break;
        }
    }

    for (int i = 0; i < 100; ++i)
    {
        printf("%d\t", abs((int)pixel[i]));
        if ((i + 1) % 10 == 0)
            printf("\n");
    }
    fclose(inputFile);
    return 1;
}

int reverse(const char* input) {// 6.图像反色
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
        return 0;//函数执行失败,返回0
    }
    outputFile = fopen("C:/Users/yuehan lian/Desktop/reverse.bmp", "wb");
    if (outputFile == NULL) {
        printf("输出图像文件创建失败!\n");//文件创建失败
        return 0;//函数执行失败,返回0
    }
    char header[54];
    fread(&header, sizeof(char), 54, inputFile); //获得输入图像头部信息
    fwrite(&header, sizeof(char), 54, outputFile);//写进输出图像头部信息

    int width = *(int*)&header[18];  //获得图像宽度
    int height = abs(*(int*)&header[22]);  //获得图像高度
    int stride = (4 * ((8 * 3) * width) / 32); //计算行的数量
    int paddingCheck = (stride % 4);
    int padding;
    if (paddingCheck != 0) { //计算行的数量
        int padCalc = 0;
        for (int i = 1; padCalc < stride; i++) {
            padCalc = i * 4;
        }
        padding = padCalc - stride;
    }
    else
        padding = 0;

    char pad;
    char pixel[3];
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(char), 3, inputFile); //读取RBG信息,并写入pixel中
            //pixel[0] =~pixel[0];//进行取反运算,得到反色后的像素值
            //pixel[1] = ~pixel[1];
            //pixel[2] = ~pixel[2];
            pixel[0] = 255 - pixel[0];
            pixel[1] = 255 - pixel[1];
            pixel[2] = 255 - pixel[2];
            fwrite(&pixel, (sizeof(char)), 3, outputFile);//向输出图像写入末尾填充的图像信息
        }
        for (int l = 0; l < padding; l++) { 
            fread(&pad, 1, 1, inputFile); //读取末尾填充的图像信息
            fwrite(&pad, 1, 1, outputFile);  //向输出图像写入末尾填充的图像信息
        }
    }
    int elms_read;  //确保没有空像素被读取 
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

int intense(const char* input) {//5.图像增强或减暗
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
    int op;
    printf("1.增强\n");
    printf("2.减暗\n");
    printf("input your choice:\n");
    scanf("%d", &op);
    if(op==1)
     outputFile = fopen("C:/Users/yuehan lian/Desktop/intense.bmp", "wb");//需要修改路径
    if (op == 2)
     outputFile = fopen("C:/Users/yuehan lian/Desktop/reduce.bmp", "wb");//需要修改路径
    if (outputFile == NULL) {
        printf("the file cannot be found\n");
    }
    fwrite(header, sizeof(char), 122, outputFile);
    char pad;
    unsigned char pixel[3];
    unsigned char pixeledit[3];
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(unsigned char), 3, inputFile); //读取RBG信息,并写入pixel中
            if (op == 1) {//图像增强    RGB分量 +50,如果超出255,则等于255
                pixel[0] +50 >=255 ? pixel[0]=255 : pixel[0]= pixel[0] + 50;
                pixel[1] +50>= 255 ? pixel[1] = 255 : pixel[1] = pixel[1] + 50;
                pixel[2] +50 >=255 ? pixel[2] = 255 : pixel[2] = pixel[2] + 50;
            }
            if (op == 2) {//图像减暗   RGB分量 *0.6
                pixel[0] *= 0.6;
                pixel[1] *= 0.6;
                pixel[2] *= 0.6;
            }
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

int map(int r, int c, int width) {
    return r * width + c;
}

int pixeldata(const char* input) {
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
        return 0;
    }

    char header[54];
    fread(&header, sizeof(char), 54, inputFile); //获得输入图像头部信息

    int width = *(int*)&header[18]; //获得图像宽度
    int height = abs(*(int*)&header[22]); //获得图像高度
    int stride = (4 * ((8 * 3) * width) / 32); //计算行的数量
    int paddingCheck = (stride % 4);
    int padding;
    if (paddingCheck != 0) { //如果行数不能被4整除
        int padCalc = 0;
        for (int i = 1; padCalc < stride; i++) {
            padCalc = i * 4;
        }
        padding = padCalc - stride;
    }
    else
        padding = 0;

    char pad;
    char pixel[3];
    int merge[256];
    int count[256];
    for (int i = 0; i < 256; ++i)
    {
        count[i] = 0;
    }
    printf("像素数据为: \n");
    int cnt = 0; bool flag = 0;
    for (int j = 0; j < height; j++) {
        if (flag) break;
        for (int k = 0; k < width; k++) {
            fread(pixel, sizeof(char), 3, inputFile); //读取RBG信息,并写入pixel中
            if (cnt < 256)
            {
               merge[cnt]= abs((int)pixel[0])*0.3+ abs((int)pixel[1])*0.59+abs((int)pixel[2])*0.11;//归一化
                cnt++;
            }
            else {
                flag = 1;
                break;
            }
           
        }
        for (int l = 0; l < padding; l++) {//读取末尾填充的图像信息
            fread(&pad, 1, 1, inputFile); 
        }
    }
    int elms_read;  //确保没有空像素被读取 
    while (1) {
        elms_read = fread(&pad, 1, 1, inputFile);
        if (elms_read == 0) {
            break;
        }
    }

    printf("\n归一化后的直方图数据为: \n");
    for (int i = 0; i < 256; ++i)
    {
        printf("%3d\t", merge[i]);
        count[merge[i]]++;
        if ((i + 1) % 16 == 0)//每输出16个,就换行
            printf("\n");
    }
    printf("\n");
    /*直方图*/
    for (int i = 1; i < 256; ++i)
    {
        if (count[i] == 0)//只输出大于0的直方图
            continue;
        printf("%d :",i);
        for (int j= 1; j<= count[i]; ++j)
        {
            printf("*");
        }
        printf("\n");
    }
    
    fclose(inputFile);
    return 1;
}

int showcolorpad(const char* input) {//8/ 显示调色板
    inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("并无此文件,请检查main函数中定义的路径是否正确!\n");//文件读取失败,重新修改文件路径
        return 0;
    }
    fseek(inputFile, sizeof(BITMAPFILEHEADER), 0);
    BITMAPINFOHEADER head;
    fread(&head, sizeof(BITMAPINFOHEADER), 1, inputFile);
    unsigned int width = head.biWidth;
    unsigned int height = head.biHeight;
    unsigned int bitcount = head.biBitCount;
    int linebyte = (width * bitcount / 8 + 3) / 4 * 4;
    RGBTRIPLE* pcolortable = new RGBTRIPLE[256];
    if (bitcount == 8) {
        fread(pcolortable, sizeof(RGBTRIPLE), 256, inputFile);
    }
    else {
        printf("该图不是8位BMP图像,没有调色盘!\n");
        return 0;
    }
    for (size_t i = 0; i < 256; ++i)
    {
        printf("%3d %3d %3d\t", (unsigned int)(pcolortable[i].rgbBlue), (unsigned int)(pcolortable[i].rgbGreen), (unsigned int)(pcolortable[i].rgbRed));
        if ((i + 1) % 4 == 0) printf("\n");//每输出4个数据,就换行
    }
    fclose(inputFile);
    return 1;
}

int main(void) {//主函数

    while (1)
    {
        int op;
        printf("BMP图像处理作业菜单\n");
        char infile[]= "C:/Users/yuehan lian/Desktop/d1.bmp";//需要修改文件路径
       // 请输入BMP图像所在位置(例如:\"C:/Users/yuehan lian/Desktop/1.bmp
        printf("0.结束啦\n");
        printf("1.读取BMP图像(8/24bit)\n");
        printf("2.保存BMP图像(8/24bit)\n");
        printf("3.显示图像数据\n");
        printf("4.计算直方图\n");
        printf("5.图像增强/减暗\n");
        printf("6.反色\n");
        printf("7.灰度图(同位转换,不改变位数)\n");
        printf("8.显示调色板(8bit)\n");

        printf("\n输入选项: ");
        scanf("%d", &op);
        printf("\n");
        switch (op)
        {
                case 0: {
                    printf("感谢你的使用!\n");
                    return 0;
                    break;
                }
                case 1: {
                    if (read(infile) == 0) {
                        return 0;}// 1  读图像 
                   break; }
                case 2:{
                    if (save(infile) == 0) {
                        return 0; }// 2 保存图像
                    break; }
                case 3: {
                    if (show(infile) == 0) {
                        return 0; }// 3 显示图像数据
                    break;  }
                case 4: {
                    if (pixeldata(infile) == 0) {
                        return 0;}// 4 直方图
                    break; }
                case 5: {
                    if (intense(infile) == 0) {
                        return 0;}// 5 图像增强/减暗
                    break;}
                case 6: {
                    if (reverse(infile) == 0) {
                        return 0; }// 6 反色
                    break; }
                case 7: {
                    if (greyScale(infile) == 0) {
                        return 0;  }// 7 灰度图
                    break; }
                case 8: {
                    if (showcolorpad(infile) == 0) {
                        return 0;
                    }//8 显示调色板
                    break; }
                default:
                    break;
        }
    }

    return 0;
}
