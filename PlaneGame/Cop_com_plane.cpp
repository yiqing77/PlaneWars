#include "stdafx.h"
#include "Cop_com_plane.h"
#include "resource.h"

CImageList Cop_com_plane::imglist;
Cop_com_plane::Cop_com_plane(void)
	: pos(0)
	, flag_direction(false)
{

}


Cop_com_plane::~Cop_com_plane(void)
{
}


void Cop_com_plane::Draw(CDC* pDC)
{
	if (this->flag_direction)
	{
		imglist.Draw(pDC, 0, pos, ILD_TRANSPARENT);
	}
	else 
	{
		imglist.Draw(pDC, 1, pos, ILD_TRANSPARENT);
	}

}


void Cop_com_plane::loadimage(void)
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_op_com_plane);
	imglist.Create(35, 35, ILC_COLOR24 | ILC_MASK, 2, 0);
	imglist.Add(&bmp, RGB(0, 0, 0));
}
