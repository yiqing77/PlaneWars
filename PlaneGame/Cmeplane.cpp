#include "stdafx.h"
#include "Cmeplane.h"
#include "resource.h"

Cmeplane::Cmeplane(void)
	: pos(500,300)//��ʼ���Լ��ɻ�������
{
}


Cmeplane::~Cmeplane(void)
{
}


void Cmeplane::Draw(CDC * pDC)
{
	CDC memDC;//����һ������DC
	memDC.CreateCompatibleDC(pDC);//����DC
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_meplane);//װ��DDB
	memDC.SelectObject(&bmpDraw);//����ԭ��DDB����ѡ����DDB��DC
	pDC->TransparentBlt(pos.x, pos.y,50, 60, &memDC, 0, 0, 50, 60, RGB(0, 0, 0));
}



