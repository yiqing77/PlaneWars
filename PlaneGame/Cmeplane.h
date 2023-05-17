#pragma once
#include "afx.h"
#include "atltypes.h"
class Cmeplane :
	public CObject
{
public:
	Cmeplane(void);
	~Cmeplane(void);
	CPoint pos;
	void Draw(CDC * pDC);
};

