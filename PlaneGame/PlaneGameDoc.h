
// PlaneGameDoc.h : CPlaneGameDoc 类的接口
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
protected: // 仅从序列化创建
	CPlaneGameDoc();
	DECLARE_DYNCREATE(CPlaneGameDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CPlaneGameDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	Cmeplane meplane;
	CObList mebomblist;
	int mebomb_speed;
	int meplane_speed;
	int op_com_plane_chance;//敌机出现的几率
	int op_com_bomb_chance;
	CObList op_com_planelist;
	int op_com_planespeed;
	int op_com_bombspeed;
	CObList op_com_bomblist;
	CObList explodelist;
	
	int meplane_hp;
	int EXP;//经验
	int meplane_level;
	int meplane_level_increment;//升级所需经验
	int score;
	Cboss boss;
	int total_op_plane;//现在出现的敌机总数
	int appear_boss_count_plane;//出现BOSS所需要的敌机数量
	CObList equiplist;//装备链表
};
