// PointTrans.h


#ifndef _INC_PointTransAPI
#define _INC_PointTransAPI

// 函数原型
BOOL WINAPI LinerTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, FLOAT fA, FLOAT fB);
BOOL WINAPI ThresholdTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bThre);
BOOL WINAPI WindowTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bLow, BYTE bUp);
BOOL WINAPI GrayStretch(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, BYTE bX1, BYTE bY1, BYTE bX2, BYTE bY2);
BOOL WINAPI InteEqualize(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

//倒V变换
void WINAPI InverseV(LPSTR lpDIBBits,LONG lWidth,LONG lHeight,  LONG dataSizePerLine,int point);
//正V变换
void WINAPI VTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point);
//倒L变换
void WINAPI InverseL(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point);
//L变换
void WINAPI LTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int point);
//位平面分解
void WINAPI BitPlane(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int bitNum);
//对数运算
void WINAPI LogTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, int m_c);
//GAMMA运算
void WINAPI GammaTrans(LPSTR lpDIBBits, LONG lWidth, LONG lHeight, LONG dataSizePerLine, float m_r);


//半影调显示M3
void WINAPI BinaryShow(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
//半影调显示
void WINAPI BinaryFloyd(LPSTR lpDIBBits, LONG lWidth, LONG lHeight);
#endif //!_INC_PointTransAPI