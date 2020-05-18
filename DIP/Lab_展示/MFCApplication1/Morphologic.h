
#ifndef _INC_MorphologicAPI
#define _INC_MorphologicAPI



void Erosion(int type, int StructElem[10], LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

void Expand(int type, int StructElem[10], LPSTR lpDIBBits, LONG lWidth, LONG lHeight);

void XOR(LPSTR lpSrcStartBits, unsigned char * lpSrcStartBitsBackUp, LONG length);



#endif
