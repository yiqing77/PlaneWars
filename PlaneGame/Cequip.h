#pragma once
#include "afx.h"
#include "atltypes.h"
class Cequip :
	public CObject
{
public:
	Cequip();
	~Cequip();
	CPoint pos;
	int equip_kind;
	void Draw(CDC* pDC);
};

