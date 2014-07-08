#if !defined(AFX_LINECHARTCTRL_H__35492752_A636_4655_984C_2902ED2DECD7__INCLUDED_)
#define AFX_LINECHARTCTRL_H__35492752_A636_4655_984C_2902ED2DECD7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LineChartCtrl.h : header file
//

#include <vector>
#include "AfxTempl.h"
using namespace std;

#define MAX_POINTS 2048 //1 pixel per point, 1024 is the ordinary screen pixels count

class CLine
{
public:
	BOOL        m_bDraw;     //plot or not
	COLORREF	m_color;     //
	int         m_iStyle;     //solid,dash
	int         m_iThick;     //1pixel,2pixel
	CLine()
	{
		m_bDraw = TRUE;
		m_color = RGB(0,0,0);
		m_iStyle = PS_SOLID;
		m_iThick = 1;
		InitializeCriticalSection ( & g_cs ) ;
	}
	CLine(int iStyle, COLORREF color, int iThick);
	CLine(const CLine& line);
	CLine& operator = (const CLine& line);
	~CLine();
	void AddPoint(double x, double y);
	double GetPointX(int nIndex);
	double GetPointY(int nIndex);
	int    GetPointCount();
	void RemoveAllPoints();
	void RemoveUselessPoints();
	
private:
	vector<double> m_dXValue;
	vector<double> m_dYValue;
	CRITICAL_SECTION g_cs ;
	
};
class CAxis
{
public:
	BOOL        m_bDraw;     //plot or not
	BOOL        m_bGrid;     //Draw grid line or not
	double      m_dMinValue;
	double      m_dMaxValue;
	double	    m_dValuePerPixel; //how much a pixel represented
	
	COLORREF	m_color;     //
	int         m_iStyle;     //
	int         m_iThick;     //
	CAxis()
	{
		m_bDraw = TRUE;
		m_bGrid = TRUE;
		m_dMinValue = 0;
		m_dMaxValue = 10000;
		m_color = RGB(0,0,0);
		m_iStyle = PS_SOLID;
		m_iThick = 1;
	}
};


/////////////////////////////////////////////////////////////////////////////
// CLineChartCtrl window

class CLineChartCtrl : public CStatic
{
// Construction
public:
	CLineChartCtrl();

// Attributes
public:

// Operations
public:
	//afx_msg void OnTimer(UINT nIDEvent);
	//afx_msg void OnPaint();
	//afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	
	void Start();
	void Stop();
	
	void CalcLayout();
	void AddLine(int iStyle, COLORREF color, int iThick = 1);
	CLine& GetLine(int nIndex);
	int    GetLineCount();
	
	void SetRate(int nRate);
	void SetBkColor(COLORREF clrBkColor);
	CAxis& GetAxisY();
	CAxis& GetAxisX();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLineChartCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLineChartCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLineChartCtrl)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void DrawAll(CDC* pDC);
	void DrawBackground(CDC* pDC);
	void DrawAxises(CDC* pDC);
	void DrawLines(CDC* pDC);
	
	CRect m_rectCtrl;                       // the static rect of chart control
	CRect m_rectAxisY;		                // Y axis rect
	CRect m_rectAxisX;		                // X axis rect
	CRect m_rectPlot;                       // m_rectCtrl - margin - axisRect
	CPoint m_ptInLine[MAX_POINTS];          // points used to draw a line
	
	
	int			m_iMarginLeft;			   // left margin in pixels
	int			m_iMarginRight;			   // right margin in pixels
	int			m_iMarginTop;			   // top margin in pixels
	int			m_iMarginBottom;		   // bottom margin in pixels
	
	CAxis m_axisY;       //Y axis
	CAxis m_axisX;     //X axis
	
	vector<CLine> m_lines;
	
	COLORREF m_clrBkColor; //plot control background color
	int      m_nRate;      //update interval
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINECHARTCTRL_H__DA4D1935_9FB2_4023_A91B_1DD25552494A__INCLUDED_)

