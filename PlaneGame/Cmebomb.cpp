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
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pDC);//创建DC
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_mebomb);//装入DDB
	memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
	pDC->TransparentBlt(pos.x, pos.y, 10, 20, &memDC, 0, 0, 10, 20, RGB(0, 0, 0));
}
