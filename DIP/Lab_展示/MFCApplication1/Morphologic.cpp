#include"stdafx.h"
//读取r行c列的像素索引值
int readPixel(unsigned char * bitMapData, LONG r, LONG c,int dataSizePerLine)
{
	return *(bitMapData + r*dataSizePerLine + c);
}

void Erosion(int type, int StructElem[10], LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);

	LONG r;
	LONG c;
	

	//水平方向腐蚀1*3
	if (0 == type)
	{
		for (r = 0; r < lHeight; r++)
		{
			for (c = 1; c < lWidth-1; c++)
			{
				int temp = readPixel(bitMapData, r, c, dataSizePerLine);
				int tempLeft = readPixel(bitMapData, r, c - 1, dataSizePerLine);
				int tempRight = readPixel(bitMapData, r, c + 1, dataSizePerLine);
				if (temp == 255 && tempLeft == 255 && tempRight == 255)
					temp = 255;
				else
					temp = 0;

				*(lpDIBBits + r*dataSizePerLine + c) = temp;
			}
		}
	}
	//垂直方向3*1
	if (1 == type)
	{
		for (r = 1; r < lHeight-1; r++)
		{
			for (c = 0; c < lWidth; c++)
			{
				int temp = readPixel(bitMapData, r, c, dataSizePerLine);
				int tempUp = readPixel(bitMapData, r+1, c, dataSizePerLine);
				int tempDown = readPixel(bitMapData, r-1, c, dataSizePerLine);

				if (temp == 255 && tempUp == 255 && tempDown == 255)
					temp = 255;
				else
					temp = 0;

				*(lpDIBBits + r*dataSizePerLine + c) = temp;
			}
		}
	}
	if (2 == type)
	{
		for (r = 1; r < lHeight - 1; r++)
		{
			for (c = 1; c < lWidth-1; c++)
			{
				int temp[10];
				int num = 1;
				//9颗像素都填充到数组里面了
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						temp[num] = readPixel(bitMapData, r + i, c + j,dataSizePerLine);
						num++;
					}
				}
				//进行“模板”运算
				int result = 1;
				for (int i = 1; i < 10; i++)
				{
					//模板是1，像素不是1
					if (1 == StructElem[i])
					{
						if (temp[i] != 255)
							result = 0;
					}
				}
				//得出结果
				if (0 == result)
					*(lpDIBBits + r*dataSizePerLine + c) = 0;
				else
					*(lpDIBBits + r*dataSizePerLine + c) = 255;

			
			}
		}
	}
}
//膨胀
void Expand(int type, int StructElem[10], LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);

	LONG r;
	LONG c;
	
	//先对称
	 //水平方向膨胀1*3
	if (0 == type)
	{
		for (r = 0; r < lHeight; r++)
		{
			for (c = 1; c < lWidth - 1; c++)
			{
				int temp = readPixel(bitMapData, r, c, dataSizePerLine);
				int tempUp = readPixel(bitMapData, r , c+1, dataSizePerLine);
				int tempDown = readPixel(bitMapData, r , c-1, dataSizePerLine);
				if (temp == 255 || tempUp == 255 || tempDown == 255)
					temp = 255;
				else
					temp = 0;

				*(lpDIBBits + r*dataSizePerLine + c) = temp;
			}
		}
	}
	//垂直方向3*1
	if (1 == type)
	{
		for (r = 1; r < lHeight - 1; r++)
		{
			for (c = 0; c < lWidth; c++)
			{
				int temp = readPixel(bitMapData, r, c, dataSizePerLine);
				int tempLeft = readPixel(bitMapData, r, c - 1, dataSizePerLine);
				int tempRight = readPixel(bitMapData, r, c + 1, dataSizePerLine);

				if (temp == 255 || tempLeft == 255 || tempRight == 255)
					temp = 255;
				else
					temp = 0;

				*(lpDIBBits + r*dataSizePerLine + c) = temp;
			}
		}
	}
	//自定义
	if (2 == type)
	{
		//反转结构元素
		int temp = 0;
		temp = StructElem[1]; StructElem[1] = StructElem[9]; StructElem[9] = temp;
		temp = StructElem[2]; StructElem[2] = StructElem[6]; StructElem[6] = temp;
		temp = StructElem[4]; StructElem[4] = StructElem[8]; StructElem[8] = temp;

		for (r = 1; r < lHeight - 1; r++)
		{
			for (c = 1; c < lWidth - 1; c++)
			{
				int temp[10];
				int num = 1;
				//9颗像素都填充到数组里面了
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						temp[num] = readPixel(bitMapData, r + i, c + j, dataSizePerLine);
						num++;
					}
				}
				//进行“模板”运算
				int result = 0;
				for (int i = 1; i < 10; i++)
				{
					//模板是1，像素有一个是1
					if (1 == StructElem[i])
					{
						if (temp[i] == 255)
							result = 1;
					}
				}
				//得出结果
				if (0 == result)
					*(lpDIBBits + r*dataSizePerLine + c) = 0;
				else
					*(lpDIBBits + r*dataSizePerLine + c) = 255;


			}
		}
	}
}


void XOR(LPSTR lpSrcStartBits, unsigned char * lpSrcStartBitsBackUp, LONG length)
{
	int oldData = 0;
	int newData = 0;
	for (int i = 0; i < length; i++)
	{
		oldData = *(lpSrcStartBits + i);
		newData = *(lpSrcStartBitsBackUp + i);
		//异或
		oldData = oldData^newData;

		*(lpSrcStartBits + i) = oldData;


	}
}