#pragma once
#include <afxwin.h>
class CChildWnd :
	// CWnd 상속
	public CWnd	
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();	// header 파일에서 onPaint() 프로토타입 선언
};

