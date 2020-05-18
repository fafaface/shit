#include"stdafx.h"
//���о���0��ʼ
int readMatrix(int r, int c, int dataSizePerLine,unsigned char* bitMapData)
{
	int temp = bitMapData[r*dataSizePerLine + c];
	return temp;
}



int calc(unsigned char* bitMapData, int WeightOfTemplate, int HeightOfTemplate, float ratio,float *TEMPLATE,int r, int c,int dataSizePerLine)
{
	int sum = 0;
	int excel = 0;
	for (int i =0; i <HeightOfTemplate; i++)
	{
		for (int j = 0; j < WeightOfTemplate; j++)
		{
			sum +=TEMPLATE[excel]* readMatrix(r + i, c + j, dataSizePerLine, bitMapData);
			excel++;
		}
	}
	if (sum*ratio < 0)return 0;
	if (sum*ratio > 255)return 255;
	return sum*ratio;//ϵ��

}


//3*3��ֵ�˲�
void  WINAPI MeanTemplate ( int m_iTempMX,int m_iTempMY, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8/8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);

	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;

	//ģ��ֵ
	float TEMPLATE[9] = {
		1,1,1,
		1,1,1,
		1,1,1
	};

	for (int r = 0; r < lHeight-2; r++)
	{
		for (int c = 0; c < lWidth-2; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + 3 - m_iTempMY - 1) + c + m_iTempMX;
			temp = calc(bitMapData,3,3,1/9.0,TEMPLATE,r,c,dataSizePerLine);
			*pixel = temp;
		}
	}

}

void WINAPI  GaussTemplate(int m_iTempMX, int m_iTempMY, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);

	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;

	//ģ��ֵ
	float TEMPLATE[9] = {
		1,2,1,
		2,4,2,
		1,2,1
	};

	for (int r = 0; r < lHeight - 2; r++)
	{
		for (int c = 0; c < lWidth - 2; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + 3 - m_iTempMY - 1) + c + m_iTempMX;
			temp = calc(bitMapData, 3, 3, 0.0625, TEMPLATE, r, c, dataSizePerLine);
			*pixel = temp;
		}
	}
}

void WINAPI  CustomMadeTemplate(int m_iTempMX, int m_iTempMY, int weightOfTemplate, int heightOfTemplate, float * m_fpArray, float m_fTempC, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);

	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;


	
	//ģ��ֵ
	float TEMPLATE[25];
	int tag = 0;

	for (int r = 0; r < heightOfTemplate; r++)
	{
		for (c = 0; c < weightOfTemplate; c++)
		{
			TEMPLATE[tag] = m_fpArray[r * 5 + c];
			tag++;
		}
	}
	

	for (int r = 0; r < lHeight - heightOfTemplate+1; r++)//�У�ģ��ĸ�/2
	{
		for (int c = 0; c < lWidth - weightOfTemplate+1; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r+heightOfTemplate-m_iTempMY-1) + c+m_iTempMX;
			temp = calc(bitMapData, weightOfTemplate, heightOfTemplate, m_fTempC, TEMPLATE, r, c, dataSizePerLine);
			*pixel = temp;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////

int calcMidFilter(unsigned char* bitMapData, int m_iFilterW, int m_iFilterH, int r, int c, int dataSizePerLine)
{
	int pixel[100];
	int excel = 0;
	for (int i = 0; i <m_iFilterH; i++)
	{
		for (int j = 0; j <m_iFilterW; j++)
		{
			pixel[excel] = readMatrix(r + i, c + j, dataSizePerLine, bitMapData);
			excel++;
		}
	}
	for (int i = 0; i < excel - 1; i++)
	{
		for (int j = 0; j < excel - 1 - i; j++)
		{
			int temp;
			if (pixel[j] > pixel[j + 1])
			{
				temp = pixel[j]; pixel[j] = pixel[j + 1]; pixel[j + 1] = temp;
			}
		}
	}
	return pixel[excel/2];
}

void WINAPI MidFilter3X1(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;



	for (int r = 0; r < lHeight-2; r++)
	{
		for (int c = 0; c < lWidth ; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + m_iFilterH - m_iFilterMX - 1) + c + m_iFilterMY;
			temp = calcMidFilter(bitMapData, 1, 3, r, c, dataSizePerLine);
			*pixel = temp;
		}
	}

}

void WINAPI MidFilter1X3(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;



	for (int r = 0; r < lHeight ; r++)
	{
		for (int c = 0; c < lWidth-2; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + m_iFilterH - m_iFilterMX - 1) + c + m_iFilterMY;
			temp = calcMidFilter(bitMapData, 3, 1, r, c, dataSizePerLine);
			*pixel = temp;
		}
	}
}

void WINAPI MidFilter3X3(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;



	for (int r = 0; r < lHeight - 2; r++)
	{
		for (int c = 0; c < lWidth-2; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + m_iFilterH - m_iFilterMX - 1) + c + m_iFilterMY;
			temp = calcMidFilter(bitMapData, 3, 3, r, c, dataSizePerLine);
			*pixel = temp;
		}
	}
}

void WINAPI MidFilterCustomMade(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;



	for (int r = 0; r < lHeight - m_iFilterW+1; r++)
	{
		for (int c = 0; c < lWidth-m_iFilterH+1; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + m_iFilterH - m_iFilterMX - 1) + c + m_iFilterMY;
			temp = calcMidFilter(bitMapData, m_iFilterW, m_iFilterH, r, c, dataSizePerLine);
			*pixel = temp;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
int calcMaxMinFilter(unsigned char* bitMapData, int m_width, int m_height, int r, int c, int dataSizePerLine, int originalPixel, int type)
{
	int pixel[100];
	int excel = 0;
	for (int i = 0; i <m_height; i++)
	{
		for (int j = 0; j <m_width; j++)
		{
			if (i != m_height / 2 || j != m_width / 2)
			{
				pixel[excel] = readMatrix(r + i, c + j, dataSizePerLine, bitMapData);
				excel++;
			}

		}
	}
	for (int i = 0; i < excel - 1; i++)
	{
		for (int j = 0; j < excel - 1 - i; j++)
		{
			int temp;
			if (pixel[j] > pixel[j + 1])
			{
				temp = pixel[j]; pixel[j] = pixel[j + 1]; pixel[j + 1] = temp;
			}
		}
	}
	if (0 == type)//���ֵ�˲�
	{
		if (originalPixel > pixel[excel - 1])
			return pixel[excel - 1];
		else
			return originalPixel;
	}
	if (1 == type)//��Сֵ�˲�
	{
		if (originalPixel < pixel[0])
			return pixel[0];
		else
			return originalPixel;
	}
	if (2 == type)//�е�ֵ�˲�
		return (pixel[0] + pixel[excel - 1]) / 2;

}
void WINAPI MaxMinFilter(int m_width, int m_height, int type, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;



	for (int r = 0; r < lHeight - m_width + 1; r++)
	{
		for (int c = 0; c < lWidth - m_height + 1; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + m_height - m_height / 2 - 1) + c + m_width / 2;
			temp = *pixel;
			temp = calcMaxMinFilter(bitMapData, m_width, m_height, r, c, dataSizePerLine, temp, type);
			*pixel = temp;
		}
	}
}



void WINAPI MidPointFilter(int m_width, int m_height, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;



	for (int r = 0; r < lHeight - m_width + 1; r++)
	{
		for (int c = 0; c < lWidth - m_height + 1; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + m_height - m_height / 2 - 1) + c + m_width / 2;
			temp = *pixel;
			temp = calcMaxMinFilter(bitMapData, m_width, m_height, r, c, dataSizePerLine, temp, 2);
			*pixel = temp;
		}
	}
}


///////////////////////////////////////////////////////////////////////////////////////////
void calcAdaptiveMidFilterRatio(int r, int c, int width,int height,int dataSizePerLine, unsigned char* bitMapData,int &zmin,int &zmax,int &zmid)
{

	int pixel[100];
	int excel = 0;

	for (int i = 0; i <height; i++)
	{
		for (int j = 0; j <width; j++)
		{
			pixel[excel] = readMatrix(r + i, c + j, dataSizePerLine, bitMapData);
			excel++;
		}
	}

	for (int i = 0; i < excel - 1; i++)
	{
		for (int j = 0; j < excel - 1 - i; j++)
		{
			int temp;
			if (pixel[j] > pixel[j + 1])
			{
				temp = pixel[j]; pixel[j] = pixel[j + 1]; pixel[j + 1] = temp;
			}
		}
	}

	zmin = pixel[0];
	zmax = pixel[excel - 1];
	if (excel % 2 == 0)
	{
		zmid = (pixel[excel / 2] + pixel[excel / 2 - 1]) / 2;
	}
	else
		zmid = pixel[excel / 2];
}
int calcAdaptiveMidFilter(unsigned char* bitMapData, int m_width, int m_height, int r, int c, LONG lWidth,LONG lHeight,int dataSizePerLine,int originPixel)
{


	int zmin = 0;
	int zmax = 0;
	int zmid = 0;
	int zxy = originPixel;
	int widthMax = m_width;
	int heightMax = m_height;

	int currentWidth = 3;
	int currentHeight = 3;
	calcAdaptiveMidFilterRatio(r, c, currentWidth, currentHeight, dataSizePerLine, bitMapData, zmin, zmax, zmid);

	while (1)
	{
		if (zmid < zmax&&zmin < zmid)//��������������
		{
			if (originPixel<zmax&&originPixel>zmin)//ԭʼֵ��������
				return originPixel;
			else//ԭʼֵ������
				return zmid;
		}
		else//�����������϶�
		{
			//����ģ��
			currentHeight+=2; currentWidth+=2;
			r--; c--;
			//����ģ��󻹿��Լ�������
			if (currentHeight < m_height&&currentWidth < m_width&&r >= 0 && c >= 0 && r + currentHeight - 1 < lHeight&&c + currentWidth - 1 < lWidth)
				calcAdaptiveMidFilterRatio(r, c, currentWidth, currentHeight, dataSizePerLine, bitMapData, zmin, zmax, zmid);
			else
				return zmid;
		}
	}


}
void WINAPI AdaptiveMidFilter(int m_width, int m_height, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;

	for (int r = 0; r < lHeight - 2; r++)
	{
		for (int c = 0; c < lWidth - 2; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + 3 - 1 - 1) + c + 1;
			temp = *pixel;
			temp = calcAdaptiveMidFilter(bitMapData, m_width,m_height, r, c, lWidth,lHeight,dataSizePerLine,temp);
			*pixel = temp;
		}
	}
}

void WINAPI AddNoise(int type,float m_noisePercent, LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;

	LONG totalPixelNum = dataSizePerLine*lHeight;
	LONG totalNoiseNum = totalPixelNum*m_noisePercent;

	for (int i = 0; i < totalNoiseNum; i++)
	{
		float num = rand()/(RAND_MAX*1.0);
		num = totalPixelNum*num;

		if (0 == type)
		{
			pixel = (unsigned char *)lpDIBBits +(LONG)num;
			*pixel = 0;
		}
		if (1 == type)
		{
			pixel= (unsigned char *)lpDIBBits +(LONG)num;
			*pixel = 255;
		}


	}
}
////////////////////////////////////////////////////////////////////////////////////////
//sobel����
int calcSobel(unsigned char* bitMapData,   int *TEMPLATE, int r, int c, int dataSizePerLine)
{
	int sum = 0;
	int excel = 0;
	for (int i = 0; i <3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			sum += TEMPLATE[excel] * readMatrix(r + i, c + j, dataSizePerLine, bitMapData);
			excel++;
		}
	}

	return abs(sum);
}

void WINAPI Sobel(LPSTR lpDIBBits, LONG lWidth, LONG lHeight)
{
	//ÿ���ֽ���
	int dataSizePerLine = (lWidth * 8 / 8 + 3) / 4 * 4;
	unsigned char * bitMapData = new unsigned char[dataSizePerLine*lHeight];
	memcpy(bitMapData, lpDIBBits, dataSizePerLine*lHeight);


	LONG r;
	LONG c;
	unsigned char* pixel;//����
	int temp;

	int SX[9] = {
		-1,0,1,
		-2,0,2,
		-1,0,1
	};
	int SY[9] = {
		1,2,1,
		0,0,0,
		-1,-2,-1
	};

	for (int r = 0; r < lHeight-2; r++)
	{
		for (int c = 0; c < lWidth-2 ; c++)
		{
			pixel = (unsigned char *)lpDIBBits + dataSizePerLine*(r + 1) + c + 1;

			temp = calcSobel(bitMapData, SX, r, c, dataSizePerLine) + calcSobel(bitMapData, SY, r, c, dataSizePerLine);

			if (temp < 0)temp = 0;
			if (temp > 255)temp = 255;

			*pixel = temp;
		}
	}


}