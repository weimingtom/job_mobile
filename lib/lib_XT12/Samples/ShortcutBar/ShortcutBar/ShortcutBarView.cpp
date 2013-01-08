// ShortcutBarView.cpp : implementation of the CShortcutBarView class
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ShortcutBar.h"

#include "ShortcutBarDoc.h"
#include "ShortcutBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView

IMPLEMENT_DYNCREATE(CShortcutBarView, CView)

BEGIN_MESSAGE_MAP(CShortcutBarView, CView)
	//{{AFX_MSG_MAP(CShortcutBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView construction/destruction

CShortcutBarView::CShortcutBarView()
{
	// TODO: add construction code here

}

CShortcutBarView::~CShortcutBarView()
{
}

BOOL CShortcutBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView drawing

void CShortcutBarView::OnDraw(CDC* pDC)
{
	CShortcutBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (XTPPaintManager()->GetCurrentTheme() == xtpThemeOffice2003)
		pDC->Draw3dRect(CXTPClientRect(this), GetXtremeColor(XPCOLOR_FRAME), GetXtremeColor(XPCOLOR_FRAME));
	else
		pDC->Draw3dRect(CXTPClientRect(this), GetXtremeColor(COLOR_3DSHADOW), GetXtremeColor(COLOR_3DHIGHLIGHT));
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView printing

BOOL CShortcutBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CShortcutBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CShortcutBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView diagnostics

#ifdef _DEBUG
void CShortcutBarView::AssertValid() const
{
	CView::AssertValid();
}

void CShortcutBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShortcutBarDoc* CShortcutBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShortcutBarDoc)));
	return (CShortcutBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarView message handlers
