
// MemoView.cpp: CMemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Memo.h"
#endif

#include "MemoDoc.h"
#include "MemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMemoView

IMPLEMENT_DYNCREATE(CMemoView, CView)

BEGIN_MESSAGE_MAP(CMemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_COPY, &CMemoView::OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, &CMemoView::OnEditPaste)
	ON_COMMAND(ID_EDIT_CUT, &CMemoView::OnEditCut)
	ON_COMMAND(ID_EDIT_UNDO, &CMemoView::OnEditUndo)
END_MESSAGE_MAP()

// CMemoView 생성/소멸

CMemoView::CMemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMemoView::~CMemoView()
{
}

BOOL CMemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMemoView 그리기

void CMemoView::OnDraw(CDC* /*pDC*/)
{
	CMemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMemoView 인쇄

BOOL CMemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMemoView 진단

#ifdef _DEBUG
void CMemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMemoDoc* CMemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMemoDoc)));
	return (CMemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMemoView 메시지 처리기


int CMemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CMemoDoc* pDoc = GetDocument();

	CRect rect(0, 0, 0, 0);
	pDoc->m_Edit.Create(ES_AUTOVSCROLL | ES_MULTILINE | ES_WANTRETURN | WS_VISIBLE | WS_CHILDWINDOW | WS_VSCROLL, rect, this, 1);
	return 0;
}


void CMemoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMemoDoc* pDoc = GetDocument();
	CRect rect;
	GetClientRect(rect);
	pDoc->m_Edit.SetWindowPos(&wndTop, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_SHOWWINDOW);

}


BOOL CMemoView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMemoDoc* pDoc = GetDocument();
	switch (LOWORD(wParam))
	{
	case 1:
		switch (HIWORD(wParam))
		{
		case EN_CHANGE:
			pDoc->SetModifiedFlag(TRUE);	//변경 사항이 있다는 표시
		}
		break;
	}
	return CView::OnCommand(wParam, lParam);
}


void CMemoView::OnEditCopy()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMemoDoc* pDoc = GetDocument();
	pDoc->m_Edit.Copy();

}


void CMemoView::OnEditPaste()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMemoDoc* pDoc = GetDocument();
	pDoc->m_Edit.Paste();
}


void CMemoView::OnEditCut()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMemoDoc* pDoc = GetDocument();
	pDoc->m_Edit.Cut();
}


void CMemoView::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMemoDoc* pDoc = GetDocument();
	pDoc->m_Edit.Undo();
}
