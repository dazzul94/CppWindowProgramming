#pragma once
#include <afxwin.h>
class CChildWnd :
	// CWnd ���
	public CWnd	
{
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();	// header ���Ͽ��� onPaint() ������Ÿ�� ����
};

