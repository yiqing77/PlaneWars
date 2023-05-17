#include "stdafx.h"
#include "Cop_com_bomb.h"
#include "resource.h"

Cop_com_bomb::Cop_com_bomb(void)
	: pos(0)
	, flag_direction(false)//控制敌机子弹出现方向
	, add_x(0)
	, add_y(0)
{
}


Cop_com_bomb::~Cop_com_bomb(void)
{
}


void Cop_com_bomb::Draw(CDC* pDC)
{
	CDC memDC;//定义一个兼容DC
	memDC.CreateCompatibleDC(pDC);//创建DC
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_op_com_bomb);//装入DDB
	memDC.SelectObject(&bmpDraw);//保存原有DDB，并选入新DDB入DC
	pDC->TransparentBlt(pos.x, pos.y,8, 8, &memDC, 0, 0, 8, 8, RGB(0, 0, 0));
}
