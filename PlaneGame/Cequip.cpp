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
	CDC memDC;//����һ������DC
	memDC.CreateCompatibleDC(pDC);//����DC
	CBitmap bmpDraw;
		bmpDraw.LoadBitmap(IDB_equip_AddHP);//װ��DDB
		memDC.SelectObject(&bmpDraw);//����ԭ��DDB����ѡ����DDB��DC
		pDC->TransparentBlt(pos.x, pos.y, 21, 19, &memDC, 0, 0, 21, 19, RGB(0, 0, 0));
	
}
