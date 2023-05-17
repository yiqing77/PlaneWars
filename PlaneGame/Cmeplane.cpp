#include "stdafx.h"
#include "Cmeplane.h"
#include "resource.h"

Cmeplane::Cmeplane(void)
	: pos(500,300)//初始化自己飞机的坐标
{
}


Cmeplane::~Cmeplane(void)
{
}


void Cmeplane::Draw(CDC * pDC)
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pDC);//创建DC
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_meplane);//装入DDB
	memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
	pDC->TransparentBlt(pos.x, pos.y,50, 60, &memDC, 0, 0, 50, 60, RGB(0, 0, 0));
}



