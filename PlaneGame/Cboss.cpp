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


void Cboss::Draw(CDC *pDC)//���boss
{
	CDC memDC;//����һ������DC
	memDC.CreateCompatibleDC(pDC);//����DC
	CBitmap bmpDraw;//λͼ����
	bmpDraw.LoadBitmap(IDB_boss);//װ��DDB
	memDC.SelectObject(&bmpDraw);//����ԭ��DDB����ѡ����DDB��DC
	pDC->TransparentBlt(pos.x, pos.y, 150, 124, &memDC, 0, 0, 150, 124, RGB(0, 0, 0));
	
}
