#include "stdafx.h"
#include "Cmebomb.h"
#include "resource.h"

Cmebomb::Cmebomb(void)
	: pos(0)
	, add_x(0)
	, add_y(0)
{
}


Cmebomb::~Cmebomb(void)
{
}


void Cmebomb::Draw(CDC* pDC)
{
	CDC memDC;//����һ������DC
	memDC.CreateCompatibleDC(pDC);//����DC
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_mebomb);//װ��DDB
	memDC.SelectObject(&bmpDraw);//����ԭ��DDB����ѡ����DDB��DC
	pDC->TransparentBlt(pos.x, pos.y, 10, 20, &memDC, 0, 0, 10, 20, RGB(0, 0, 0));
}
