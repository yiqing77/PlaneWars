
// PlaneGameDoc.h : CPlaneGameDoc ��Ľӿ�
//


#pragma once
#include "cmeplane.h"
#include "cmebomb.h"
#include "afxcoll.h"
#include "Cop_com_plane.h"
#include "Cop_com_bomb.h"
#include "Cexplode.h"
#include "Cboss.h"
#include "Cequip.h"

class CPlaneGameDoc : public CDocument
{
protected: // �������л�����
	CPlaneGameDoc();
	DECLARE_DYNCREATE(CPlaneGameDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CPlaneGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	Cmeplane meplane;
	CObList mebomblist;
	int mebomb_speed;
	int meplane_speed;
	int op_com_plane_chance;//�л����ֵļ���
	int op_com_bomb_chance;
	CObList op_com_planelist;
	int op_com_planespeed;
	int op_com_bombspeed;
	CObList op_com_bomblist;
	CObList explodelist;
	
	int meplane_hp;
	int EXP;//����
	int meplane_level;
	int meplane_level_increment;//�������辭��
	int score;
	Cboss boss;
	int total_op_plane;//���ڳ��ֵĵл�����
	int appear_boss_count_plane;//����BOSS����Ҫ�ĵл�����
	CObList equiplist;//װ������
};
