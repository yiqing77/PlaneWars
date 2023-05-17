
// PlaneGameView.h : CPlaneGameView 类的接口
//

#pragma once


class CPlaneGameView : public CView
{
protected: // 仅从序列化创建
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// 特性
public:
	CPlaneGameDoc* GetDocument() const;

// 操作
public:
	CDC MemDC;//双缓存
	CBitmap MemBitmap;//双缓存
	CBrush m_brush;//刷背景
	CRect rect_insect;
	CRect rect_mebomb;
	CRect rect_op_com_plane;
	CRect rect_op_com_bomb;
	CRect rect_meplane;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	bool intersect(CRect r1, CRect r2);
	void HandleEXP(int score);
	void print_message();
	void Add_meplanebomb();
	void rand_op_plane();
	void draw_delete_explode();
	void handle_keydown();
	void op_com_bomb_handle(void);
	void op_com_plane_handle(void);
	void Add_op_bomb(void);
	void control_flash();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void mebomb_print();
	void check_print_equip(void);
	void boss_handle(void);
	void boss_apper_delete(void);
	void boss_handle_pos(void);
	void Gameover(void);
	void boss_dead(void);
};

#ifndef _DEBUG  // PlaneGameView.cpp 中的调试版本
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

