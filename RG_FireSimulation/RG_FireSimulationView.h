
// RG_FireSimulationView.h : interface of the CRGFireSimulationView class
//

#pragma once

#include "CGLRenderer.h"


class CRGFireSimulationView : public CView
{
protected: // create from serialization only
	CRGFireSimulationView() noexcept;
	DECLARE_DYNCREATE(CRGFireSimulationView)

	CGLRenderer m_glRenderer;

// Attributes
public:
	CRGFireSimulationDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CRGFireSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in RG_FireSimulationView.cpp
inline CRGFireSimulationDoc* CRGFireSimulationView::GetDocument() const
   { return reinterpret_cast<CRGFireSimulationDoc*>(m_pDocument); }
#endif

