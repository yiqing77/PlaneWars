#pragma once
#include "afx.h"
#include "atltypes.h"
class Cop_com_bomb :
	public CObject
{
public:
	Cop_com_bomb(void);
	~Cop_com_bomb(void);
	CPoint pos;
	void Draw(CDC* pDC);
	bool flag_direction;
	int add_x;
	int add_y;
};

