#include "pch.h"
#include <math.h>
#define PI 3.1415926
void OnPaint_Polyline_04(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_04_1(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_star_04(PWINDOW_DATA pWnd, HDC hdc);

void OnPaint_04(PWINDOW_DATA pWnd, HDC hdc)
{
    //OnPaint_star_04(pWnd, hdc);
    //OnPaint_04_1(pWnd, hdc);
    //return;


    //HBRUSH hbr_red  = CreateSolidBrush(RGB(255, 0, 0));
    //HBRUSH hbr_green = CreateSolidBrush(RGB(0, 255, 0));
    //HBRUSH hbr_blue = CreateSolidBrush(RGB(0, 0, 255));


    //HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr_red);

    //RECT rc;
    //GetClientRect(pWnd->hWnd, &rc);
    //// 填充整个窗口, 背景是红色
    //Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);   


}

void OnPaint_04_1(PWINDOW_DATA pWnd, HDC hdc)
{

    // HS_BDIAGONAL  // 度向上从左到右的舱口
    // HS_CROSS      // 水平和垂直剖面线
    // HS_DIAGCROSS  // 45 度剖面线
    // HS_FDIAGONAL  // 45 度向下从左到右舱口
    // HS_HORIZONTAL // 水平舱口
    // HS_VERTICAL   // 垂直舱口

    //HBRUSH hbr_red = CreateHatchBrush(HS_BDIAGONAL, RGB(255, 0, 0));
    //HBRUSH hbr_green = CreateHatchBrush(HS_CROSS, RGB(0, 255, 0));
    //HBRUSH hbr_blue = CreateHatchBrush(HS_FDIAGONAL, RGB(0, 0, 255));

    //HBRUSH hbr_red = CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0, 0));
    //HBRUSH hbr_green = CreateHatchBrush(HS_HORIZONTAL, RGB(0, 255, 0));
    //HBRUSH hbr_blue = CreateHatchBrush(HS_VERTICAL, RGB(0, 0, 255));

    LOGBRUSH lb = { 0 };
    lb.lbStyle = BS_HATCHED;
    lb.lbColor = RGB(255, 0, 0);
    lb.lbHatch = HS_BDIAGONAL;
    HBRUSH hbr_red = CreateBrushIndirect(&lb);
    
    lb.lbColor = RGB(0, 255, 0);
    lb.lbHatch = HS_CROSS;
    HBRUSH hbr_green = CreateBrushIndirect(&lb);

    lb.lbColor = RGB(0, 0, 255);
    lb.lbHatch = HS_FDIAGONAL;
    HBRUSH hbr_blue = CreateBrushIndirect(&lb);



    HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr_red);

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    // 填充整个窗口, 背景是红色
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);   



}



void OnPaint_Polyline_04(PWINDOW_DATA pWnd, HDC hdc)
{
    POINT pt[] =
    {
        { 73, 137},
        {177, 137},
        {103, 211},
        {122, 100},
        {173, 200},
        {73, 137},

        {216, 32},
        {340, 32},
        {280, 110},
        {216, 32 },

        {314, 268},
        {217, 407},
        {408, 409},
        //{314, 268},

    };

    POINT nowPt1 = { 0 };
    POINT nowPt2 = { 0 };
    GetCurrentPositionEx(hdc, &nowPt1);
    //Polyline(hdc, pt, sizeof(pt) / sizeof(pt[0]));
    //PolylineTo (hdc, pt, sizeof(pt) / sizeof(pt[0]));


    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
    HBRUSH hbrOld = (HBRUSH)SelectObject(hdc, hbr);

    DWORD asz[] = { 6, 4, 3 };
    PolyPolygon(hdc, pt, (INT*)asz, sizeof(asz) / sizeof(asz[0]));

    GetCurrentPositionEx(hdc, &nowPt2);

    output(L"画线之前的坐标 = {%d,%d}. 画线之后的坐标 = {%d,%d}\n",
           nowPt1.x, nowPt1.y, nowPt2.x, nowPt2.y);

    SelectObject(hdc, hbrOld);
    DeleteObject(hbr);
}


void OnPaint_star_04(PWINDOW_DATA pWnd, HDC hdc)
{
    SetPolyFillMode(hdc, ALTERNATE);
    //SetPolyFillMode(hdc, WINDING);

    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
    HGDIOBJ hbrObj = SelectObject(hdc, hbr);

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    const int cxClient = rc.right - rc.left;
    const int cyClient = rc.bottom - rc.top;

    POINT ptCenter = { cxClient / 2, cyClient / 2 };
    int r = 150;
    POINT pt[5];

    pt[0].x = ptCenter.x - r * sin(2 * PI / 5);
    pt[0].y = ptCenter.y - r * cos(2 * PI / 5);

    pt[1].x = ptCenter.x + r * sin(2 * PI / 5);
    pt[1].y = ptCenter.y - r * cos(2 * PI / 5);

    pt[2].x = ptCenter.x - r * sin(PI / 5);
    pt[2].y = ptCenter.y + r * cos(PI / 5);

    pt[3].x = ptCenter.x;
    pt[3].y = ptCenter.y - r;

    pt[4].x = ptCenter.x + r * sin(PI / 5);
    pt[4].y = ptCenter.y + r * cos(PI / 5);

    const int count = sizeof(pt) / sizeof(pt[0]);
    Polygon(hdc, pt, count);

    SelectObject(hdc, hbrObj);
    DeleteObject(hbrObj);

}