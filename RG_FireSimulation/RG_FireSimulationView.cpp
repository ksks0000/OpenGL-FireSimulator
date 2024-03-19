
// RG_FireSimulationView.cpp : implementation of the CRGFireSimulationView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "RG_FireSimulation.h"
#endif

#include "RG_FireSimulationDoc.h"
#include "RG_FireSimulationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRGFireSimulationView

IMPLEMENT_DYNCREATE(CRGFireSimulationView, CView)

BEGIN_MESSAGE_MAP(CRGFireSimulationView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CRGFireSimulationView construction/destruction

CRGFireSimulationView::CRGFireSimulationView() noexcept
{
	// TODO: add construction code here

}

CRGFireSimulationView::~CRGFireSimulationView()
{
}

BOOL CRGFireSimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRGFireSimulationView drawing

void CRGFireSimulationView::OnDraw(CDC* pDC)
{
	CRGFireSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}


// CRGFireSimulationView printing

BOOL CRGFireSimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRGFireSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRGFireSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRGFireSimulationView diagnostics

#ifdef _DEBUG
void CRGFireSimulationView::AssertValid() const
{
	CView::AssertValid();
}

void CRGFireSimulationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRGFireSimulationDoc* CRGFireSimulationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRGFireSimulationDoc)));
	return (CRGFireSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CRGFireSimulationView message handlers


int CRGFireSimulationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CRGFireSimulationView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL CRGFireSimulationView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CRGFireSimulationView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CRGFireSimulationView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


void CRGFireSimulationView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_UP)
	{
		m_glRenderer.AddCameraAngleX(10);
		Invalidate();
	}

	if (nChar == VK_DOWN)
	{
		m_glRenderer.AddCameraAngleX(-10);
		Invalidate();
	}

	if (nChar == VK_LEFT)
	{
		m_glRenderer.AddCameraAngleY(10);
		Invalidate();
	}

	if (nChar == VK_RIGHT)
	{
		m_glRenderer.AddCameraAngleY(-10);
		Invalidate();
	}

	if (nChar == VK_ADD)
	{
		m_glRenderer.CameraZoom(2);
		Invalidate();
	}

	if (nChar == VK_SUBTRACT)
	{
		m_glRenderer.CameraZoom(-2);
		Invalidate();
	}

	if (nChar == VK_SPACE)
	{
		m_glRenderer.UpdateFrame();
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
