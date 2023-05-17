
// PlaneGameView.h : CPlaneGameView ��Ľӿ�
//

#pragma once


class CPlaneGameView : public CView
{
protected: // �������л�����
	CPlaneGameView();
	DECLARE_DYNCREATE(CPlaneGameView)

// ����
public:
	CPlaneGameDoc* GetDocument() const;

// ����
public:
	CDC MemDC;//˫����
	CBitmap MemBitmap;//˫����
	CBrush m_brush;//ˢ����
	CRect rect_insect;
	CRect rect_mebomb;
	CRect rect_op_com_plane;
	CRect rect_op_com_bomb;
	CRect rect_meplane;
// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CPlaneGameView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // PlaneGameView.cpp �еĵ��԰汾
inline CPlaneGameDoc* CPlaneGameView::GetDocument() const
   { return reinterpret_cast<CPlaneGameDoc*>(m_pDocument); }
#endif

