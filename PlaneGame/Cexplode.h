#pragma once
#include "afx.h"
#include "atltypes.h"
#include "afxwin.h"
class Cexplode :
	public CObject
{
public:
	Cexplode();
	~Cexplode();
	CPoint pos;
	int index;
	void Draw(CDC * pDC,bool biaozhi);
	static CImageList imglist;
	static void loadimage();
};

