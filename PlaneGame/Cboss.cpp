#include "stdafx.h"
#include "Cboss.h"
#include "resource.h"

Cboss::Cboss()
: pos(200,0)
, HP(150)
, guan(1)
{
	HP_old=HP;
}


Cboss::~Cboss()
{
}


void Cboss::Draw(CDC *pDC)//输出boss
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pDC);//创建DC
	CBitmap bmpDraw;//位图对象
	bmpDraw.LoadBitmap(IDB_boss);//装入DDB
	memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
	pDC->TransparentBlt(pos.x, pos.y, 150, 124, &memDC, 0, 0, 150, 124, RGB(0, 0, 0));
	
}
