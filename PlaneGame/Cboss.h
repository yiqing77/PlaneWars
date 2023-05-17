#pragma once
#include "afx.h"
#include "atltypes.h"
class Cboss :
	public CObject
{
public:
	Cboss();
	~Cboss();
	
	int HP;
	void Draw(CDC* pDC);
	CPoint pos;
	int HP_old;
	int guan;
};

