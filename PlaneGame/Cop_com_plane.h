#pragma once
#include "afx.h"
#include "atltypes.h"
#include "afxwin.h"
class Cop_com_plane :
	public CObject
{
public:
	Cop_com_plane(void);
	~Cop_com_plane(void);
	CPoint pos;
	void Draw(CDC* pDC);
	bool flag_direction;
	static CImageList imglist;
	static void loadimage(void);
};

