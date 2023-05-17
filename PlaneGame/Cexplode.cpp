#include "stdafx.h"
#include "Cexplode.h"
#include "resource.h"

CImageList Cexplode::imglist;//图像列表控制
Cexplode::Cexplode()
: pos(0)
, index(0)//图片的下标
{
}


Cexplode::~Cexplode()
{
}


void Cexplode::Draw(CDC * pDC,bool biaozhi)
{
	imglist.Draw(pDC, index, pos, ILD_TRANSPARENT);
	if (biaozhi)
	index++;
}


void Cexplode::loadimage()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_explode);
	imglist.Create(66, 66, ILC_COLOR24 | ILC_MASK, 8, 0);
	imglist.Add(&bmp, RGB(0, 0, 0));
}
