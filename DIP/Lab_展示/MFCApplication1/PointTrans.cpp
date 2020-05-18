
/**************************************************************************
 *  文件名：PointTrans.cpp
 *
 *  图像点运算API函数库：
 *
 *  LinerTrans()		- 图像线性变换
 *WindowTrans()		- 图像窗口变换
 *  GrayStretch()		- 图像灰度拉伸
 *  InteEqualize()		－直方图均衡
 *
 *************************************************************************/

#include "stdafx.h"
#include "PointTrans.h"
#include "DIBAPI.h"

#include <math.h>
#include <direct.h>

/*************************************************************************
 *
 * 函数名称：
 *   LinerTrans()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   FLOAT fA		    - 线性变换的斜率
 *   FLOAT fB           - 线性变换的截距
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行灰度的线性变换操作。
 *
 ************************************************************************/

BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 中间变量
	FLOAT	fTemp;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 线性变换
			fTemp = fA * (*lpSrc) + fB;
			
			// 判断是否超出范围
			if (fTemp > 255)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
			else if (fTemp < 0)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 四舍五入
				*lpSrc = (unsigned char) (fTemp + 0.5);
			}
		}
	}
	
	// 返回
	return TRUE;

}

/*************************************************************************
 *
 * 函数名称：
 *   ThresholdTrans()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   BYTE  bThre	    - 阈值
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行阈值变换。对于灰度值小于阈值的象素直接设置
 * 灰度值为0；灰度值大于阈值的象素直接设置为255。
 *
 ************************************************************************/
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 判断是否小于阈值
			if ((*lpSrc) < bThre)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
		}
	}
	
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   WindowTrans()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   BYTE  bLow		    - 窗口下限
 *   BYTE  bUp          - 窗口上限
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行窗口变换。只有在窗口范围内的灰度保持不变，
 * 小于下限的象素直接设置灰度值为0；大于上限的象素直接设置灰度值为255。
 *
 ************************************************************************/
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 判断是否超出范围
			if ((*lpSrc) < bLow)
			{
				// 直接赋值为0
				*lpSrc = 0;
			}
			else if ((*lpSrc) > bUp)
			{
				// 直接赋值为255
				*lpSrc = 255;
			}
		}
	}
	
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   GrayStretch()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *   BYTE bX1			- 灰度拉伸第一个点的X坐标
 *   BYTE bY1			- 灰度拉伸第一个点的Y坐标
 *   BYTE bX2			- 灰度拉伸第二个点的X坐标
 *   BYTE bY2			- 灰度拉伸第二个点的Y坐标
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行灰度拉伸。
 *
 ************************************************************************/
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 灰度映射表
	BYTE	bMap[256];
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 计算灰度映射表
	for (i = 0; i <= bX1; i++)
	{
		// 判断bX1是否大于0（防止分母为0）
		if (bX1 > 0)
		{
			// 线性变换
			bMap[i] = (BYTE) bY1 * i / bX1;
		}
		else
		{
			// 直接赋值为0
			bMap[i] = 0;
		}
	}
	for (; i <= bX2; i++)
	{
		// 判断bX1是否等于bX2（防止分母为0）
		if (bX2 != bX1)
		{
			// 线性变换
			bMap[i] = bY1 + (BYTE) ((bY2 - bY1) * (i - bX1) / (bX2 - bX1));
		}
		else
		{
			// 直接赋值为bY1
			bMap[i] = bY1;
		}
	}
	for (; i < 256; i++)
	{
		// 判断bX2是否等于255（防止分母为0）
		if (bX2 != 255)
		{
			// 线性变换
			bMap[i] = bY2 + (BYTE) ((255 - bY2) * (i - bX2) / (255 - bX2));
		}
		else
		{
			// 直接赋值为255
			bMap[i] = 255;
		}
	}
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// 返回
	return TRUE;
}

/*************************************************************************
 *
 * 函数名称：
 *   InteEqualize()
 *
 * 参数:
 *   LPSTR lpDIBBits    - 指向源DIB图像指针
 *   LONG  lWidth       - 源图像宽度（象素数）
 *   LONG  lHeight      - 源图像高度（象素数）
 *
 * 返回值:
 *   BOOL               - 成功返回TRUE，否则返回FALSE。
 *
 * 说明:
 *   该函数用来对图像进行直方图均衡。
 *
 ************************************************************************/
BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	
	// 指向源图像的指针
	unsigned char*	lpSrc;
	
	// 临时变量
	LONG	lTemp;
	
	// 循环变量
	LONG	i;
	LONG	j;
	
	// 灰度映射表
	BYTE	bMap[256];
	
	// 灰度映射表
	LONG	lCount[256];
	
	// 图像每行的字节数
	LONG	lLineBytes;
	
	// 计算图像每行的字节数
	lLineBytes = WIDTHBYTES(lWidth * 8);
	
	// 重置计数为0
	for (i = 0; i < 256; i ++)
	{
		// 清零
		lCount[i] = 0;
	}
	
	// 计算各个灰度值的计数
	for (i = 0; i < lHeight; i ++)
	{
		for (j = 0; j < lWidth; j ++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			
			// 计数加1
			lCount[*(lpSrc)]++;
		}
	}
	
	// 计算灰度映射表
	for (i = 0; i < 256; i++)
	{
		// 初始为0
		lTemp = 0;
		
		for (j = 0; j <= i ; j++)
		{
			lTemp += lCount[j];
		}
		
		// 计算对应的新灰度值
		bMap[i] = (BYTE) (lTemp * 255 / lHeight / lWidth);
	}
	
	// 每行
	for(i = 0; i < lHeight; i++)
	{
		// 每列
		for(j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + lLineBytes * (lHeight - 1 - i) + j;
			
			// 计算新的灰度值
			*lpSrc = bMap[*lpSrc];
		}
	}
	
	// 返回
	return TRUE;
}


void WINAPI InverseV(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 中间变量
	FLOAT	fTemp;
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + dataSizePerLine * (lHeight - 1 - i) + j;

			fTemp = *lpSrc;
			if (fTemp< point)
			{
				fTemp = (255 / point)*fTemp;
			}
			else
			{
				if(point!=255)
				fTemp = (255 - fTemp) / (255 - point) * 255;
				
			}
				// 四舍五入
				*lpSrc = (unsigned char)(fTemp + 0.5);
		}
	}
}


//正V变换
void WINAPI VTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 中间变量
	FLOAT	fTemp;



	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + dataSizePerLine * (lHeight - 1 - i) + j;

			fTemp = *lpSrc;
			if (fTemp< point)
			{
				fTemp = (point - fTemp) * 255 / point;
			}
			else
			{
				if (point != 255)

					fTemp = 255 * (fTemp - point) / (255 - point);

			}



			// 四舍五入
			*lpSrc = (unsigned char)(fTemp + 0.5);

		}
	}
}


//倒L变换
void WINAPI InverseL(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 中间变量
	FLOAT	fTemp;
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + dataSizePerLine * (lHeight - 1 - i) + j;

			fTemp = *lpSrc;
			if (fTemp< point)
			{
				fTemp =fTemp*255/point;
			}
			else
			{
				if (point != 255)

					fTemp = 255;

			}
			// 四舍五入
			*lpSrc = (unsigned char)(fTemp + 0.5);

		}
	}
}

void WINAPI LTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 中间变量
	FLOAT	fTemp;
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + dataSizePerLine * (lHeight - 1 - i) + j;

			fTemp = *lpSrc;
			if (fTemp< point)
			{
				fTemp = 255 * (point - fTemp) / point;
			}
			else
			{
				if (point != 255)

					fTemp = 0;

			}
			// 四舍五入
			*lpSrc = (unsigned char)(fTemp + 0.5);

		}
	}
}

//位平面分解
void WINAPI BitPlane(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int bitNum)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 中间变量
	int	fTemp;
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + dataSizePerLine * (lHeight - 1 - i) + j;

			fTemp = *lpSrc;
			fTemp >>= bitNum;
			fTemp = fTemp & 1;
			if (0 == fTemp)fTemp = 0;
			else
				fTemp = 255;

			*lpSrc = fTemp;

		}
	}
}

//对数运算
void WINAPI LogTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int m_c)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 中间变量
	int	fTemp;
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + dataSizePerLine * (lHeight - 1 - i) + j;

			fTemp = *lpSrc;
			
			fTemp = m_c*log(1 + fTemp);

			if (fTemp < 0)fTemp = 0;
			if (fTemp > 255)fTemp = 255;

			*lpSrc = fTemp;

		}
	}
}

void WINAPI GammaTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, float m_r)
{
	// 指向源图像的指针
	unsigned char*	lpSrc;
	// 循环变量
	LONG	i;
	LONG	j;
	// 中间变量
	int	fTemp;
	double c = 255 / pow(255, m_r);
	// 每行
	for (i = 0; i < lHeight; i++)
	{
		// 每列
		for (j = 0; j < lWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpDIBBits + dataSizePerLine * (lHeight - 1 - i) + j;

			fTemp = *lpSrc;

			fTemp = c*pow(fTemp, m_r);

			if (fTemp < 0)fTemp = 0;
			if (fTemp > 255)fTemp = 255;

			*lpSrc = fTemp;

		}
	}
}

void WINAPI BinaryShow(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);

	LONG r;
	LONG c;

	int m3[8][8] = {
		0.32,8.40,2,34,10,42,
		48,16,56,24,50,18,58,26,
		12,44,4,36,14,46,6,38,
		60,28,52,20,62,30,54,22,
		3,35,11,43,1,33,9,41,
		51,19,59,27,49,17,57,25,
		15,47,7,39,13,45,5,37,
		63,31,55,23,61,29,53,21
	};



	for (r = 0; r < lHeight; r++)
	{
		for (c = 1; c < lWidth; c++)
		{


			int temp=*(lpDIBBits + r*dataSizePerLine + c);

			int tempr = r;
			int tempc = c;
			tempr = tempr % 8;
			tempc = tempc % 8;
			temp = temp >> 2;
			if (temp > m3[tempr][tempc])
				temp = 255;
			else
				temp = 0;

			*(lpDIBBits + r*dataSizePerLine + c) = temp;

		}
	}
}

void WINAPI BinaryFloyd(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);

	LONG r;
	LONG c;

	int t = 127;

	int e = 0;

	for (r = 0; r < lHeight; r++)
	{
		for (c = 0; c < lWidth; c++)
		{
			int temp = (unsigned char )*(lpDIBBits + r*dataSizePerLine + c);

			if (temp > t)
			{
				e = temp - 255;
				temp = 255;
			}
			else
			{
				e = temp - 0;
				temp = 0;
			}

			*(lpDIBBits + r*dataSizePerLine + c) = temp;

			if (c < lWidth - 1)
			{
				temp=(unsigned char)*(lpDIBBits + r*dataSizePerLine + c + 1);
				temp += e * 3 / 8;
				if (temp < 0)temp = 0;
				if (temp > 255)temp = 255;
				*(lpDIBBits + r*dataSizePerLine + c + 1) = temp;
				
			}
			if (r < lHeight - 1)
			{
				temp = (unsigned char)*(lpDIBBits + (r+1)*dataSizePerLine + c );
				temp += e * 3 / 8;
				if (temp < 0)temp = 0;
				if (temp > 255)temp = 255;
				*(lpDIBBits + (r+1)*dataSizePerLine + c ) = temp;
			}
			if (r < lHeight - 1 && c < lWidth - 1)
			{
				temp = (unsigned char)*(lpDIBBits + (r+1)*dataSizePerLine + c + 1);
				temp += e * 2 / 8;
				if (temp < 0)temp = 0;
				if (temp > 255)temp = 255;
				*(lpDIBBits + (r+1)*dataSizePerLine + c + 1) = temp;
			}




		}
	}
}