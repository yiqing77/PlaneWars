#include "stdafx.h"
#include "Cop_com_bomb.h"
#include "resource.h"

Cop_com_bomb::Cop_com_bomb(void)
	: pos(0)
	, flag_direction(false)//���Ƶл��ӵ����ַ���
	, add_x(0)
	, add_y(0)
{
}


Cop_com_bomb::~Cop_com_bomb(void)
{
}


void Cop_com_bomb::Draw(CDC* pDC)
{
	CDC memDC;//����һ������DC
	memDC.CreateCompatibleDC(pDC);//����DC
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_op_com_bomb);//װ��DDB
	memDC.SelectObject(&bmpDraw);//����ԭ��DDB����ѡ����DDB��DC
	pDC->TransparentBlt(pos.x, pos.y,8, 8, &memDC, 0, 0, 8, 8, RGB(0, 0, 0));
}
