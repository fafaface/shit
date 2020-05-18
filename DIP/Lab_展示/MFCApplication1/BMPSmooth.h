
#ifndef _INC_BMPSmoothAPI
#define _INC_BMPSmoothAPI

void WINAPI  MeanTemplate(int m_iTempMX, int m_iTempMY, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
void WINAPI  GaussTemplate(int m_iTempMX, int m_iTempMY, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
void WINAPI  CustomMadeTemplate(int m_iTempMX, int m_iTempMY,int weightOfTemplate,int heightOfTemplate,float * m_fpArray, float m_fTempC, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

void WINAPI MidFilter3X1(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
void WINAPI MidFilter1X3(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
void WINAPI MidFilter3X3(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
void WINAPI MidFilterCustomMade(int m_iFilterMX, int m_iFilterMY, int m_iFilterW, int m_iFilterH, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

void WINAPI MaxMinFilter(int m_width, int m_height, int type, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
void WINAPI MidPointFilter(int m_width, int m_height, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
void WINAPI AdaptiveMidFilter(int m_width, int m_height, LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

//ÃÌº”‘Î…˘
void WINAPI AddNoise(int type,float m_noisePercent,LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
//Sobel
void WINAPI Sobel(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);


#endif












