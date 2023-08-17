#include "pch.h"
#include <math.h>
#include <vector>
#define PI 3.1415926
void OnPaint_Polyline_04(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_04_1(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_star_04(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_rect_04(PWINDOW_DATA pWnd, HDC hdc);
void CALLBACK timer_proc_04(HWND hWnd, UINT message, UINT_PTR id, DWORD t);

typedef struct TIMER_DATA_04
{
    int index;
    PWINDOW_DATA pWnd;
    std::vector<POINT> apt;
    TIMER_DATA_04()
    {
        index = 0;
    }
}*PTIMER_DATA_04;

static PTIMER_DATA_04 m_mem;
void OnPaint_04(PWINDOW_DATA pWnd, HDC hdc)
{
    OnPaint_Polyline_04(pWnd, hdc);
    //OnPaint_star_04(pWnd, hdc);
    //OnPaint_04_1(pWnd, hdc);
    return;

    HBRUSH hbrOld = (HBRUSH)GetCurrentObject(hdc, OBJ_BRUSH);

    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, hbr);


    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    // 填充整个窗口, 背景是红色
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

    // 恢复画刷
    SelectObject(hdc, hbrOld);
    DeleteObject(hbr);

}

void OnPaint_04_1(PWINDOW_DATA pWnd, HDC hdc)
{
    // HS_BDIAGONAL  // 度向上从左到右的舱口
    // HS_CROSS      // 水平和垂直剖面线
    // HS_DIAGCROSS  // 45 度剖面线
    // HS_FDIAGONAL  // 45 度向下从左到右舱口
    // HS_HORIZONTAL // 水平舱口
    // HS_VERTICAL   // 垂直舱口

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);



    int top = 150;

    auto pfn_create = [&](int iHatch, COLORREF clr, int left)
    {
        HBRUSH hbr = CreateHatchBrush(iHatch, clr);
        HGDIOBJ hbrOld = SelectObject(hdc, hbr);
        Rectangle(hdc, left, top, left + 100, top + 100);
        DeleteObject(SelectObject(hdc, hbrOld));
    };

    
    pfn_create(HS_BDIAGONAL , RGB(255, 0, 0), 10);  // 度向上从左到右的舱口
    pfn_create(HS_CROSS     , RGB(0, 255, 0), 120); // 水平和垂直剖面线
    pfn_create(HS_DIAGCROSS , RGB(0, 0, 255), 230); // 45 度剖面线

    top += 110;
    // 45 度向下从左到右舱口
    pfn_create(HS_FDIAGONAL , RGB(255, 0, 128), 10);  // 45 度向下从左到右舱口
    pfn_create(HS_HORIZONTAL, RGB(128, 255, 0), 120); // 水平舱口
    pfn_create(HS_VERTICAL  , RGB(128, 0, 255), 230); // 垂直舱口


    auto pfn_create1 = [&](int lbStyle, int iHatch, COLORREF clr, int left)
    {
        LOGBRUSH lb = { 0 };
        lb.lbStyle = lbStyle;
        lb.lbColor = clr;
        lb.lbHatch = iHatch;
        HBRUSH hbr = CreateBrushIndirect(&lb);

        HGDIOBJ hbrOld = SelectObject(hdc, hbr);
        Rectangle(hdc, left + 400, top, left + 500, top + 100);
        DeleteObject(SelectObject(hdc, hbrOld));
    };

    top = 150;

    pfn_create1(BS_HATCHED, HS_BDIAGONAL , RGB(255, 0, 0), 10);  // 度向上从左到右的舱口
    pfn_create1(BS_HATCHED, HS_CROSS     , RGB(0, 255, 0), 120); // 水平和垂直剖面线
    pfn_create1(BS_HATCHED, HS_DIAGCROSS , RGB(0, 0, 255), 230); // 45 度剖面线

    top += 110;
    pfn_create1(BS_SOLID, HS_FDIAGONAL , RGB(255, 0, 128), 10);  // 45 度向下从左到右舱口
    pfn_create1(BS_SOLID, HS_HORIZONTAL, RGB(128, 255, 0), 120); // 水平舱口
    pfn_create1(BS_SOLID, HS_VERTICAL  , RGB(128, 0, 255), 230); // 垂直舱口


}



void OnPaint_Polyline_04(PWINDOW_DATA pWnd, HDC hdc)
{
    POINT pt[] =
    {
        {118, 217},
        {222,215},
        {139,295},
        {172,189},
        {217, 287},
        {118, 217},

        {340,201},
        {440,198},
        {396,275},
        {340,201},

        {286,290},
        {178,405},
        {396,402},
        {286,290},


    };

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

    bool isCheck(HWND hParent);
    SetPolyFillMode(hdc, isCheck(pWnd->hWnd) ? ALTERNATE : WINDING);

    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

    DWORD asz[] = { 6, 4, 4 };
    PolyPolygon(hdc, pt, (INT*)asz, sizeof(asz) / sizeof(asz[0]));

    SelectObject(hdc, hbrOld);
    DeleteObject(hbr);
}


void OnPaint_star_04(PWINDOW_DATA pWnd, HDC hdc)
{
    bool isCheck(HWND hParent);
    SetPolyFillMode(hdc, isCheck(pWnd->hWnd) ? ALTERNATE : WINDING);

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    const int cxClient = rc.right - rc.left;
    const int cyClient = rc.bottom - rc.top;


    HBRUSH hbr = CreateSolidBrush(RGB(245, 245, 245));
    HGDIOBJ hbrObj = SelectObject(hdc, hbr);
    Rectangle(hdc, 0, 0, cxClient, cyClient);
    SelectObject(hdc, hbrObj);
    DeleteObject(hbr);


    POINT ptCenter = { cxClient / 2, cyClient / 2 };
    int r = 150;
    POINT pt[5];

    pt[0].x = (int)(ptCenter.x - r * sin(2 * PI / 5));
    pt[0].y = (int)(ptCenter.y - r * cos(2 * PI / 5));

    pt[1].x = (int)(ptCenter.x + r * sin(2 * PI / 5));
    pt[1].y = (int)(ptCenter.y - r * cos(2 * PI / 5));

    pt[2].x = (int)(ptCenter.x - r * sin(PI / 5));
    pt[2].y = (int)(ptCenter.y + r * cos(PI / 5));

    pt[3].x = (int)(ptCenter.x);
    pt[3].y = (int)(ptCenter.y - r);

    pt[4].x = (int)(ptCenter.x + r * sin(PI / 5));
    pt[4].y = (int)(ptCenter.y + r * cos(PI / 5));

    hbr = CreateSolidBrush(RGB(255, 0, 0));
    hbrObj = SelectObject(hdc, hbr);

    const int count = sizeof(pt) / sizeof(pt[0]);
    Polygon(hdc, pt, count);

    SelectObject(hdc, hbrObj);
    DeleteObject(hbr);

}


void OnPaint_rect_04(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    const int cxClient = rc.right - rc.left;
    const int cyClient = rc.bottom - rc.top;


    HBRUSH hbr = CreateSolidBrush(RGB(255, 255, 255));
    HGDIOBJ hbrObj = SelectObject(hdc, hbr);
    Rectangle(hdc, 0, 0, cxClient, cyClient);
    SelectObject(hdc, hbrObj);
    DeleteObject(hbr);


    int aptFigure[]{ 10, 70, 50, 70, 50, 10, 90, 10, 90, 50, 30, 50, 30, 90, 70, 90, 70, 30, 10, 30 };
    const int count = sizeof(aptFigure) / sizeof(aptFigure[0]);
    std::vector<POINT> apt;
    apt.reserve(count);
    for ( int i = 0; i < count; i += 2 )
    {
        POINT pt = { 0 };
        pt.x = aptFigure[i] * cxClient / 200;
        pt.y = aptFigure[i + 1] * cyClient / 100;
        apt.push_back(pt);
    }

    bool isCheck(HWND hParent);
    SetPolyFillMode(hdc, isCheck(pWnd->hWnd) ? ALTERNATE : WINDING);


    hbr = CreateSolidBrush(RGB(245, 0, 0));
    hbrObj = SelectObject(hdc, hbr);
    Polygon(hdc, &apt[0], apt.size());

    for ( POINT& pt : apt )
    {
        pt.x += cxClient / 2;
    }

    if ( !m_mem )
        m_mem = new TIMER_DATA_04;

    m_mem->apt.swap(apt);
    m_mem->index = 0;
    SetTimer(pWnd->hWnd, (UINT_PTR)m_mem, 300, timer_proc_04);

    SelectObject(hdc, hbrObj);
    DeleteObject(hbr);
}

void CALLBACK timer_proc_04(HWND hWnd, UINT message, UINT_PTR id, DWORD t)
{
    HDC hdc = GetDC(hWnd);
    TIMER_DATA_04* pMem = (TIMER_DATA_04*)id;
    const int count = (int)pMem->apt.size();
    const int index = pMem->index;

    if ( index >= count )
    {
        pMem->index = 0;
        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        rcClient.left = (rcClient.right - rcClient.left) / 2;
        FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));
        ReleaseDC(hWnd, hdc);
        return;
    }

    int xStart = 0, yStart = 0, xEnd = 0, yEnd = 0;

    const POINT& pt = pMem->apt[index];
    xStart = pt.x;
    yStart = pt.y;
    if( index + 1 >= count )
        xEnd = pMem->apt[0].x, yEnd = pMem->apt[0].y;
    else
        xEnd = pMem->apt[index + 1].x, yEnd = pMem->apt[index + 1].y;

    MoveToEx(hdc, xStart, yStart, 0);
    LineTo(hdc, xEnd, yEnd);
    pMem->index = index + 1;

    ReleaseDC(hWnd, hdc);

}