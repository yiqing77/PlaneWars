#pragma once
#include "afx.h"
#include "atltypes.h"
class Cmebomb :
	public CObject
{
public:
	Cmebomb(void);
	~Cmebomb(void);
	CPoint pos;
	void Draw(CDC* pDC);
	int add_x;
	int add_y;
};

