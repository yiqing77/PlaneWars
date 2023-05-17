
// PlaneGameView.cpp : CPlaneGameView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PlaneGame.h"
#endif

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CPlaneGameView 构造/析构

CPlaneGameView::CPlaneGameView()
{
	// TODO: 在此处添加构造代码
	CBitmap bmp;
	bmp.LoadBitmap(IDB_back);
	m_brush.CreatePatternBrush(&bmp);//刷背景初始化
}

CPlaneGameView::~CPlaneGameView()
{
}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView 绘制

void CPlaneGameView::OnDraw(CDC* pDC)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 在此处为本机数据添加绘制代码
}


// CPlaneGameView 诊断

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG



// CPlaneGameView 消息处理程序


void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	Cexplode::loadimage();
	Cop_com_plane::loadimage();//分割和加载爆炸图和敌机的函数

	this->SetTimer(1,100,0);
	this->SetTimer(2, 30,0);
	this->SetTimer(3, 500,0);

	if (MemDC.m_hDC == NULL)
	{
		MemDC.CreateCompatibleDC(NULL);
		CClientDC DC(this);
		CRect rect;
		this->GetClientRect(rect);
		MemBitmap.CreateCompatibleBitmap(&DC, rect.Width(), rect.Height());
		MemDC.SelectObject(&MemBitmap);
	}


	// TODO: 在此添加专用代码和/或调用基类
}


void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//=============获取窗口矩形的信息==================
	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);
	MemDC.FillSolidRect(rect, RGB(255, 255, 255));//把背景变成纯白的
	MemDC.FillRect(rect, &m_brush);	//画背景图的
	print_message();//输出的生命值之类的函数
	pDoc->meplane.Draw(&MemDC);	//画自己的飞机
	control_flash();

	switch (nIDEvent)
	{
	case 1: 
		{
		MemDC.FillSolidRect(rect, RGB(255, 255, 255));

		MemDC.FillRect(rect, &m_brush);

		print_message();

		pDoc->meplane.Draw(&MemDC);

		boss_handle();

		//普通敌机子弹检测碰撞和输出
		op_com_bomb_handle();
		
		//普通敌机检测碰撞和输出
		op_com_plane_handle();

		//战机炸弹输出
		mebomb_print();
		//检测和输出装备
		check_print_equip();
		
		break;
		}
	case 2:
		handle_keydown();
		draw_delete_explode();
		break; 
	case 3:
		rand_op_plane();
		Add_op_bomb();
		break;
	default: ;
	}

	DC.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0,SRCCOPY);
	CView::OnTimer(nIDEvent);
}



void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	MemBitmap.DeleteObject();
	MemDC.DeleteDC();


	// TODO: 在此处添加消息处理程序代码
}

//变换窗口大小
void CPlaneGameView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if (MemDC.m_hDC != NULL) {
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
	}
	MemDC.CreateCompatibleDC(NULL);
	//这时还不能绘图，因为没有地方画
	//下面建立一个与屏幕显示兼容的位图，至于位图的大小嘛，可以用窗口的大小
	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);
	MemBitmap.CreateCompatibleBitmap(&DC, rect.Width(), rect.Height());
	MemDC.SelectObject(&MemBitmap);
	// TODO:  在此处添加消息处理程序代码
}



//处理经验和改变等级
void CPlaneGameView::HandleEXP(int score)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->EXP+=score;
	int t=pDoc->meplane_level_increment;
	if (pDoc->EXP >= pDoc->meplane_level_increment)
	{
		if (pDoc->EXP>=100)
		{
			pDoc->meplane_level = 3;
			pDoc->meplane_level_increment=100;
		}
		else if (pDoc->EXP >= 50)
		{
			pDoc->meplane_level = 2;
			pDoc->meplane_level_increment=100;
		}
		else if (pDoc->EXP>=25)
		{
			pDoc->meplane_level = 1; 
			pDoc->meplane_level_increment=50;
		}
		else 
		{
			pDoc->meplane_level = 0;
			pDoc->meplane_level_increment=25;
		}
		pDoc->EXP -= t;
	}
}

//输出生命值等的信息
void CPlaneGameView::print_message()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CString str;
	
	str.Format(_T("战机等级：%d"), pDoc->meplane_level);
	MemDC.TextOutW(0, 40, str);
	str.Format(_T("战机得分：%d"), pDoc->score);
	MemDC.TextOutW(0, 20, str);
	str.Format(_T("BOSS生命值：%d"),pDoc->boss.HP);
	MemDC.TextOutW(0, 80, str);
	str.Format(_T("关卡：%d"),pDoc->boss.guan);
	MemDC.TextOutW(0, 60, str);
	str.Format(_T("战机生命值：%d"), pDoc->meplane_hp);
	MemDC.TextOutW(0, 0, str);
	
}

//根据等级添加自己飞机的炸弹
void CPlaneGameView::Add_meplanebomb()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	switch (pDoc->meplane_level)
	{
	
		case 0:
		{
			  Cmebomb *temp0 = new Cmebomb();
			  temp0->pos.x = pDoc->meplane.pos.x + 24;
			  temp0->pos.y = pDoc->meplane.pos.y - 5;
			  temp0->add_y=pDoc->mebomb_speed*10;
			  temp0->add_x = 0;
			  pDoc->mebomblist.AddHead(temp0);
		}
		break;
		case 1:
		{
			  Cmebomb *temp = new Cmebomb();
			  Cmebomb *temp1 = new Cmebomb();
			  temp->pos = pDoc->meplane.pos;
			  temp->pos.y -= 5;
			  temp->add_y = pDoc->mebomb_speed * 10;
			  temp->add_x = 0;

			  temp1->pos.x = pDoc->meplane.pos.x + 50;
			  temp1->pos.y = pDoc->meplane.pos.y - 5;
			  temp1->add_y = pDoc->mebomb_speed * 10;
			  temp1->add_x = 0;

			  pDoc->mebomblist.AddHead(temp);
			  pDoc->mebomblist.AddHead(temp1);
		}
		break;
		case 2:
		{
			  Cmebomb *temp0 = new Cmebomb();
			  temp0->pos.x = pDoc->meplane.pos.x + 25;
			  temp0->pos.y = pDoc->meplane.pos.y - 15;
			  temp0->add_y = pDoc->mebomb_speed * 10;
			  temp0->add_x = 0;

			  pDoc->mebomblist.AddHead(temp0);
			  Cmebomb *temp = new Cmebomb();
			  Cmebomb *temp1 = new Cmebomb();
			  temp->pos = pDoc->meplane.pos;
			  temp->pos.y -= 5;
			  temp->add_y = pDoc->mebomb_speed * 10;
			  temp->add_x = 0;

			  temp1->pos.x = pDoc->meplane.pos.x + 50;
			  temp1->pos.y = pDoc->meplane.pos.y - 5;
			  temp1->add_y = pDoc->mebomb_speed * 10;
			  temp1->add_x = 0;

			  pDoc->mebomblist.AddHead(temp);
			  pDoc->mebomblist.AddHead(temp1);
		}
		break;

		case 3:
		{
			  Cmebomb *temp = new Cmebomb();
			  Cmebomb *temp1 = new Cmebomb();
			  temp->pos = pDoc->meplane.pos;
			  temp->pos.y -= 5;
			  temp->add_y = pDoc->mebomb_speed * 10;
			  temp->add_x = -1*pDoc->mebomb_speed * 5;

			  temp1->pos.x = pDoc->meplane.pos.x + 50;
			  temp1->pos.y = pDoc->meplane.pos.y - 5;
			  temp1->add_y = pDoc->mebomb_speed * 10;
			  temp1->add_x = pDoc->mebomb_speed * 5;

			  pDoc->mebomblist.AddHead(temp);
			  pDoc->mebomblist.AddHead(temp1);

			  Cmebomb *temp2 = new Cmebomb();
			  Cmebomb *temp3 = new Cmebomb();
			  temp2->pos.x = pDoc->meplane.pos.x+15;
			  temp2->pos.y = pDoc->meplane.pos.y-15;
			  temp2->add_y = pDoc->mebomb_speed * 10;
			  temp2->add_x = -1*5;

			  temp3->pos.x = pDoc->meplane.pos.x + 35;
			  temp3->pos.y = pDoc->meplane.pos.y - 15;
			  temp3->add_y = pDoc->mebomb_speed * 10;
			  temp3->add_x = 5;

			  pDoc->mebomblist.AddHead(temp2);
			  pDoc->mebomblist.AddHead(temp3);

			  Cmebomb *temp4 = new Cmebomb();
			  temp4->pos.x = pDoc->meplane.pos.x + 25;
			  temp4->pos.y = pDoc->meplane.pos.y - 5;
			  temp4->add_y = pDoc->mebomb_speed * 10;
			  temp4->add_x = 0;

			  pDoc->mebomblist.AddHead(temp4);

		}
		break;
		default:;
	}
	
	
}

//随机添加敌机
void CPlaneGameView::rand_op_plane()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);

	int t;
	t = rand() % pDoc->op_com_plane_chance + 1;
	//
	if (t>1)
	{
		bool direction=false;
		int flag, x = -35;
		flag = rand() % 2 + 1;
		if (flag==1)
			direction=true;
		
		x = rand() % (rect.Width() - 35) + 1;
			Cop_com_plane *temprand = new Cop_com_plane();
			if (flag == 1)
			{
				temprand->flag_direction = true;
				temprand->pos.y = 0;
			}
			else
			{
				temprand->flag_direction = false;
				temprand->pos.y = rect.Height() - 35;
			}
			temprand->pos.x = x;
			pDoc->op_com_planelist.AddHead(temprand);
	
		 pDoc->total_op_plane++;

	}

}

//输出爆炸
void CPlaneGameView::draw_delete_explode()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	POSITION pospos1, pospos2;
	for (pospos1 = pDoc->explodelist.GetHeadPosition(); (pospos1) != NULL;)
	{
		pospos2 = pospos1;
		Cexplode *tempexplode = (Cexplode *)pDoc->explodelist.GetNext(pospos1);
		tempexplode->Draw(&MemDC, true);
		Cexplode *explodedelete = (Cexplode *)pDoc->explodelist.GetAt(pospos2);

		if (explodedelete->index == 8)
		{
			pDoc->explodelist.RemoveAt(pospos2);
			delete explodedelete;
		}
	}
}

//处理键盘事件
void CPlaneGameView::handle_keydown()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);

	if (GetKeyState(VK_UP)<0)
	{
		if (pDoc->meplane.pos.y >= pDoc->meplane_speed)
			pDoc->meplane.pos.y -= pDoc->meplane_speed;
		else
			pDoc->meplane.pos.y = 0;
	}
	if (GetKeyState(VK_DOWN)<0)
	{
		if (rect.Height() - 60 - pDoc->meplane.pos.y >= pDoc->meplane_speed)
			pDoc->meplane.pos.y += pDoc->meplane_speed;
		else
			pDoc->meplane.pos.y = rect.Height() - 60;
	}
	if (GetKeyState(VK_LEFT)<0)
	{
		if (pDoc->meplane.pos.x >= pDoc->meplane_speed)
			pDoc->meplane.pos.x -= pDoc->meplane_speed;
		else
			pDoc->meplane.pos.x = 0;
	}
	if (GetKeyState(VK_RIGHT)<0)
	{
		if (rect.Width() - 50 - pDoc->meplane.pos.x>pDoc->meplane_speed)
			pDoc->meplane.pos.x += pDoc->meplane_speed;
		else
			pDoc->meplane.pos.x = rect.Width() - 50;
	}
	if (GetKeyState(VK_SPACE)<0 )
	{
		Add_meplanebomb();


	}
}

//敌机子弹的检测碰撞 出屏幕 和输出
void CPlaneGameView::op_com_bomb_handle(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);
	

	POSITION pos,pos_del,pos_i,pos_i_del;
	
	for (pos = pDoc->op_com_bomblist.GetHeadPosition();  pos != NULL;)
		{
			pos_del = pos;
			Cop_com_bomb *temp = (Cop_com_bomb *)pDoc->op_com_bomblist.GetNext(pos);
			if (temp->pos.y>rect.Height())
			{
				Cop_com_bomb *pa = (Cop_com_bomb *)pDoc->op_com_bomblist.GetAt(pos_del);
				pDoc->op_com_bomblist.RemoveAt(pos_del);
				delete pa;
				continue;
			}
			CPoint point0;
			point0.x = temp->pos.x + 8;
			point0.y = temp->pos.y + 8;
			bool flag = true;

			rect_op_com_bomb.SetRect(temp->pos,point0);
			
			CPoint point2;
			point2.x = pDoc->meplane.pos.x + 50;
			point2.y = pDoc->meplane.pos.y + 60;
			rect_meplane.SetRect(pDoc->meplane.pos, point2);
			if (rect_insect.IntersectRect(rect_meplane, rect_op_com_bomb) != 0)
			{
				Cexplode *explodetemp = new Cexplode();
				explodetemp->pos = pDoc->meplane.pos;
				pDoc->explodelist.AddHead(explodetemp);

				Cop_com_bomb *pa = (Cop_com_bomb *)pDoc->op_com_bomblist.GetAt(pos_del);
				pDoc->op_com_bomblist.RemoveAt(pos_del);
				delete pa;

				pDoc->meplane_hp-=1;
				if (pDoc->meplane_hp<=0)
				{
					Gameover();
					
				}//游戏结束模块

				continue;
			}
			temp->pos.x+=temp->add_x;
			if (temp->flag_direction == true)
			{
				temp->pos.y += temp->add_y;
				temp->Draw(&MemDC);
			}
			else
			{
				temp->pos.y -= temp->add_y;
				temp->Draw(&MemDC);
			}
		}
}

//敌机的检测碰撞 出屏幕 和输出
void CPlaneGameView::op_com_plane_handle(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);
	

	POSITION pos,pos_del,pos_i,pos_i_del;

	for (pos = pDoc->op_com_planelist.GetHeadPosition(); (pos) != NULL;)
		{
			pos_del = pos;
			Cop_com_plane *temp = (Cop_com_plane *)pDoc->op_com_planelist.GetNext(pos);
			if (temp->pos.y<-35||temp->pos.y>rect.Height())
			{
				Cop_com_plane *pa = (Cop_com_plane *)pDoc->op_com_planelist.GetAt(pos_del);
				pDoc->op_com_planelist.RemoveAt(pos_del);
				delete pa;
				continue;
			}
			CPoint point0;
			point0.x = temp->pos.x + 35;
			point0.y = temp->pos.y + 35;
			bool flag = true;

			rect_op_com_plane.SetRect(temp->pos, point0);

			for (pos_i = pDoc->mebomblist.GetHeadPosition(); (pos_i) != NULL;)
			{
				pos_i_del = pos_i;
				Cmebomb *temptemp = (Cmebomb *)pDoc->mebomblist.GetNext(pos_i);
				CPoint point1;
				point1.x = temptemp->pos.x + 10;
				point1.y = temptemp->pos.y + 20;
				rect_mebomb.SetRect(temptemp->pos, point1);

				if (rect_insect.IntersectRect(rect_mebomb, rect_op_com_plane) != 0)
				{
					Cexplode *explodetemp = new Cexplode();
					explodetemp->pos = temp->pos;
					pDoc->explodelist.AddHead(explodetemp);
   //=================掉加血装备的几率==============
					int t=rand()%15;
					if (t==0)
					{
						Cequip *equiptemp=new Cequip();
						equiptemp->pos=temp->pos;
						equiptemp->equip_kind=0;
						pDoc->equiplist.AddHead(equiptemp);
					}
 // ========================================================
					Cop_com_plane *pa = (Cop_com_plane *)pDoc->op_com_planelist.GetAt(pos_del);
					pDoc->op_com_planelist.RemoveAt(pos_del);
					delete pa;

					Cmebomb *paa = (Cmebomb *)pDoc->mebomblist.GetAt(pos_i_del);
					pDoc->mebomblist.RemoveAt(pos_i_del);
					delete paa;

					HandleEXP(1);//经验加1 
					pDoc->score += 10;

					flag = false;
					break;
				}
			}

			if (!flag) continue;


			CPoint point2;
			point2.x = pDoc->meplane.pos.x + 50;
			point2.y = pDoc->meplane.pos.y + 60;
			rect_meplane.SetRect(pDoc->meplane.pos, point2);

			

			if (rect_insect.IntersectRect(rect_meplane, rect_op_com_plane) != 0)
			{
				Cexplode *explodetemp = new Cexplode();
				explodetemp->pos = pDoc->meplane.pos;
				pDoc->explodelist.AddHead(explodetemp);

				Cop_com_plane *pa = (Cop_com_plane *)pDoc->op_com_planelist.GetAt(pos_del);
				pDoc->op_com_planelist.RemoveAt(pos_del);
				delete pa;

				pDoc->meplane_hp -= 1;
				if (pDoc->meplane_hp<=0)
				{
					Gameover();
				}
				//游戏结束模块

				continue;
			}


			if (temp->flag_direction==true)
			{
				temp->pos.y +=pDoc->op_com_planespeed;
				temp->Draw(&MemDC);
			}
			else 
			{
				temp->pos.y -=pDoc->op_com_planespeed;
				temp->Draw(&MemDC);
			}
		}
}

//随机添加敌方炸弹
void CPlaneGameView::Add_op_bomb(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	 POSITION pos;
	for (pos = pDoc->op_com_planelist.GetHeadPosition(); (pos) != NULL;)
	{
		if ( pDoc->op_com_planelist.GetCount()>50)
			break;
		int t = rand()%pDoc->op_com_bomb_chance;//概率1/n
		Cop_com_plane *tempplane = (Cop_com_plane *)pDoc->op_com_planelist.GetNext(pos);
		if (t == 0)
		{
					  
			Cop_com_bomb *tempbomb = new Cop_com_bomb();
			if (tempplane->flag_direction)
				tempbomb->pos.y = tempplane->pos.y + 35;
			else
				tempbomb->pos.y = tempplane->pos.y;
			tempbomb->pos.x = tempplane->pos.x + 18;
			tempbomb->add_y=pDoc->op_com_bombspeed+pDoc->op_com_planespeed;
			tempbomb->add_x=0;

			tempbomb->flag_direction = tempplane->flag_direction;
			pDoc->op_com_bomblist.AddHead(tempbomb);
		}
	}
	
}

//控制飞机闪烁问题
void CPlaneGameView::control_flash()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	POSITION pos;
	for (pos = pDoc->mebomblist.GetHeadPosition(); pos != NULL;)
	{
		Cmebomb *temp = (Cmebomb *)pDoc->mebomblist.GetNext(pos);
		temp->Draw(&MemDC);
	}
	for (pos = pDoc->op_com_planelist.GetHeadPosition(); pos != NULL;)
	{
		Cop_com_plane *temp = (Cop_com_plane *)pDoc->op_com_planelist.GetNext(pos);
		temp->Draw(&MemDC);
	}
	for (pos = pDoc->op_com_bomblist.GetHeadPosition(); pos != NULL;)
	{
		Cop_com_bomb *temp = (Cop_com_bomb *)pDoc->op_com_bomblist.GetNext(pos);
		temp->Draw(&MemDC);
	}
	for (pos = pDoc->explodelist.GetHeadPosition(); (pos) != NULL;)
	{
		Cexplode *tempexplode = (Cexplode *)pDoc->explodelist.GetNext(pos);
		tempexplode->Draw(&MemDC, false);
	}
	for (pos = pDoc->equiplist.GetHeadPosition();pos!=NULL;)
	{
		Cequip *temp=(Cequip *)pDoc->equiplist.GetNext(pos);
		temp->Draw(&MemDC);
	}
	if (pDoc->total_op_plane > pDoc->appear_boss_count_plane)
	{
		KillTimer(3);
		pDoc->boss.Draw(&MemDC);
	}
}



BOOL CPlaneGameView::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	;
	return CView::PreTranslateMessage(pMsg);
}

//自己炸弹的输出和检测自己炸弹是否与boss相撞

void CPlaneGameView::mebomb_print()
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	POSITION pos,pos_del;
	CRect rect_boss;
	CPoint point1;
	//创建boss矩形
	point1.x=pDoc->boss.pos.x+150;
	point1.y=pDoc->boss.pos.y+124;
	rect_boss.SetRect(pDoc->boss.pos,point1);
	//
	for (pos = pDoc->mebomblist.GetHeadPosition(); (pos) != NULL;)
	{
		pos_del = pos;
		Cmebomb *temp = (Cmebomb *)pDoc->mebomblist.GetNext(pos);
		if (temp->pos.y<-35)
		{
			Cmebomb *pa = (Cmebomb *)pDoc->mebomblist.GetAt(pos_del);
			pDoc->mebomblist.RemoveAt(pos_del);
			delete pa;
			continue;
		}
		if (pDoc->total_op_plane > pDoc->appear_boss_count_plane)
		{
			CPoint point2;
			point2.x = temp->pos.x + 10;
			point2.y = temp->pos.y + 20;
			rect_mebomb.SetRect(temp->pos, point2);

			if (rect_insect.IntersectRect(rect_mebomb, rect_boss) != 0)//判断自己的炸弹和BOSS是否相撞
			{
				Cexplode *explodetemp = new Cexplode();
				explodetemp->pos = temp->pos;
				pDoc->explodelist.AddHead(explodetemp);

				Cmebomb *pa = (Cmebomb *)pDoc->mebomblist.GetAt(pos_del);
				pDoc->mebomblist.RemoveAt(pos_del);
				delete pa;

				pDoc->boss.HP-=1;
				if (pDoc->boss.HP<=0)
					boss_dead();
				continue;
			}
		}
		//如果子弹没爆炸，让它继续飞
		temp->pos.y -= temp->add_y;
		temp->pos.x += temp->add_x;
		temp->Draw(&MemDC);
	}
}//

//处理装备的碰撞 输出
void CPlaneGameView::check_print_equip(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);

	POSITION pos,pos_del;
	for (pos=pDoc->equiplist.GetHeadPosition();pos!=NULL;)
	{
		pos_del=pos;
		Cequip *temp=(Cequip *)pDoc->equiplist.GetNext(pos);
		if (temp->pos.y>rect.Height())
		{
			pDoc->equiplist.RemoveAt(pos_del);
			delete temp;
			continue;
		}
		CPoint point0;
		point0.x = temp->pos.x + 20;
		point0.y = temp->pos.y + 22;
		rect_op_com_bomb.SetRect(temp->pos,point0);
		CPoint point2;
		point2.x = pDoc->meplane.pos.x + 50;
		point2.y = pDoc->meplane.pos.y + 60;
		rect_meplane.SetRect(pDoc->meplane.pos, point2);
		if (rect_insect.IntersectRect(rect_meplane, rect_op_com_bomb) != 0)
		{
			pDoc->meplane_hp+=1;
		
			pDoc->equiplist.RemoveAt(pos_del);
			delete temp;

			continue;
		}
		temp->pos.y+=7;
		temp->Draw(&MemDC);
	}
}

//处理BOSS输出
void CPlaneGameView::boss_handle(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);

	if (pDoc->total_op_plane > pDoc->appear_boss_count_plane)
	{
		KillTimer(3);
		
		boss_handle_pos();//处理BOSS的位置
		
		
		pDoc->boss.Draw(&MemDC);//输出BOSS
	}
}

//处理BOSS移动和与战机碰撞
void CPlaneGameView::boss_handle_pos(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->boss.pos.x+75<pDoc->meplane.pos.x+25)
	{
		pDoc->boss.pos.x+=3;
		
	}
	else 
	{
		pDoc->boss.pos.x-=3;
		if(pDoc->boss.pos.x<0)
			pDoc->boss.pos.x=0;
	}

	if (pDoc->boss.pos.y<pDoc->meplane.pos.y)
	{
		pDoc->boss.pos.y+=3;
	}
	else if(pDoc->boss.pos.y>pDoc->meplane.pos.y)
	{
		pDoc->boss.pos.y-=3;
		if (pDoc->boss.pos.y<0)
			pDoc->boss.pos.y = 0;
	}

	if (pDoc->op_com_bomblist.GetCount()<12)//敌机屏幕炸弹的数量
	{
		for (int i=0;i<12;i++)
		{
			Cop_com_bomb *temp=new Cop_com_bomb();
			temp->pos.y=pDoc->boss.pos.y+150;
			temp->pos.x=pDoc->boss.pos.x+5+12*i;
			temp->add_y=pDoc->op_com_bombspeed;
			temp->flag_direction=true;
			//=========让BOSS子弹斜着走==========
			if (i<4)
			{
				temp->add_x=-1*(4-i);
			}
			else if (i>=7)
			{
				temp->add_x=i-5;
			}
			pDoc->op_com_bomblist.AddHead(temp);
		}
	}
	//===============检测爆炸和碰撞================
	CRect rect_boss;
	CPoint point1;
	point1.x=pDoc->boss.pos.x+150;
	point1.y=pDoc->boss.pos.y+124;
	rect_boss.SetRect(pDoc->boss.pos,point1);

	CPoint point2;
	point2.x = pDoc->meplane.pos.x + 50;
	point2.y = pDoc->meplane.pos.y + 60;
	rect_meplane.SetRect(pDoc->meplane.pos, point2);
	if (rect_insect.IntersectRect(rect_meplane, rect_boss) != 0)//判断两个矩形是否相交
	{
		Cexplode *explodetemp = new Cexplode();
		explodetemp->pos = pDoc->meplane.pos;
		pDoc->explodelist.AddHead(explodetemp);
		pDoc->meplane_hp-=2;
		if (pDoc->meplane_hp<=0)
		{
			Gameover();
		}
	}

}
//=============输出gameover==============

void CPlaneGameView::Gameover(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC DC(this);
	CRect rect;
	this->GetClientRect(&rect);

	KillTimer(1);
	KillTimer(2);
	KillTimer(3);
	KillTimer(4);
	CString str;

	str.Format(_T("战机生命值：%d"), 0);
	DC.TextOutW(0, 0, str);

	str="game over!";
	MessageBox(str,str);
	exit(0);
}

//BOSS死了
void CPlaneGameView::boss_dead(void)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->boss.HP=pDoc->boss.HP_old +100;
	pDoc->boss.HP_old=pDoc->boss.HP;
	if (pDoc->boss.HP > 1000)
		pDoc->boss.HP = 1000;
	pDoc->boss.guan++;
	pDoc->appear_boss_count_plane+=100;
	pDoc->total_op_plane=0;
	this->SetTimer(3,500,0);
}
