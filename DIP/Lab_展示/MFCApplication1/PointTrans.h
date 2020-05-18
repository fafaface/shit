// PointTrans.h


#ifndef _INC_PointTransAPI
#define _INC_PointTransAPI

// ����ԭ��
BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB);
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre);
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp);
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2);
BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

//��V�任
void WINAPI InverseV(LPSTR lpDIBBits,LONG lWidth,LONG lHeight,  LONG dataSizePerLine,int point);
//��V�任
void WINAPI VTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point);
//��L�任
void WINAPI InverseL(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point);
//L�任
void WINAPI LTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point);
//λƽ��ֽ�
void WINAPI BitPlane(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int bitNum);
//��������
void WINAPI LogTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int m_c);
//GAMMA����
void WINAPI GammaTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, float m_r);


//��Ӱ����ʾM3
void WINAPI BinaryShow(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
//��Ӱ����ʾ
void WINAPI BinaryFloyd(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
#endif //!_INC_PointTransAPI