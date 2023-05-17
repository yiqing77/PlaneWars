#include "stdafx.h"
#include "Cequip.h"
#include "resource.h"

Cequip::Cequip()
: pos(0)
, equip_kind(0)
{
}


Cequip::~Cequip()
{
}


void Cequip::Draw(CDC* pDC)
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pDC);//创建DC
	CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_equip_AddHP);//装入DDB
		memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
		pDC->TransparentBlt(pos.x, pos.y, 21, 19, &memDC, 0, 0, 21, 19, RGB(0, 0, 0));
	
}
