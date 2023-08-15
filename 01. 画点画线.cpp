#include "pch.h"
void OnPaint_dot_line(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_Bezier(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_pixelBlt(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_Polyline(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_star(PWINDOW_DATA pWnd, HDC hdc);

void OnPaint_01(PWINDOW_DATA pWnd, HDC hdc)
{
    //OnPaint_dot_line(pWnd, hdc);
    //OnPaint_Bezier(pWnd, hdc);
    //OnPaint_pixelBlt(pWnd, hdc);
    //OnPaint_Polyline(pWnd, hdc);
    OnPaint_star(pWnd, hdc);
}

// 画点, 画线
void OnPaint_dot_line(PWINDOW_DATA pWnd, HDC hdc)
{
    POINT pt = { 10, 10 };

    COLORREF ret1 = SetPixel(hdc, pt.x, pt.y, RGB(255, 0, 0));
    BOOL b = SetPixelV(hdc, pt.x, pt.y + 5, RGB(0, 255, 0));

    COLORREF clr1 = GetPixel(hdc, pt.x, pt.y);
    COLORREF clr2 = GetPixel(hdc, pt.x, pt.y + 5);

    output(L"SetPixel(%d, %d) 返回值 = 0x%08X\n"
           L"SetPixelV(%d, %d) 返回值 = %d\n"
           L"GetPixel(%d, %d) = 0x%08X\n"
           L"GetPixel(%d, %d) = 0x%08X\n",
           pt.x, pt.y, ret1,
           pt.x, pt.y + 5, b,
           pt.x, pt.y, clr1,
           pt.x, pt.y + 5, clr2);


    POINT nowPt1 = { 0 };
    POINT nowPt2 = { 0 };
    POINT nowPt3 = { 0 };
    POINT nowPt4 = { 0 };
    GetCurrentPositionEx(hdc, &nowPt1);

    MoveToEx(hdc, 50, 100, &nowPt2);
    GetCurrentPositionEx(hdc, &nowPt3);

    LineTo(hdc, 50, 200);
    GetCurrentPositionEx(hdc, &nowPt4);

    LineTo(hdc, 150, 200);

    LineTo(hdc, 150, 100);

    LineTo(hdc, 50, 100);

    output(L"设置起始坐标前的坐标 = {%d,%d}. MoveToEx返回的坐标 = {%d,%d}, MoveToEx设置之后获取的坐标 = {%d,%d}"
        L"画线之后的坐标 = {%d, %d}\n",
           nowPt1.x, nowPt1.y, nowPt2.x, nowPt2.y, nowPt3.x, nowPt3.y, nowPt4.x, nowPt4.y);

}

// 画贝塞尔曲线
void OnPaint_Bezier(PWINDOW_DATA pWnd, HDC hdc)
{
    POINT dot[] =
    {
        {10 ,  10    },
        {67 ,  137   },
        {166,  51    },
        {287,  137   },

    };

    PolyBezier(hdc, &dot[0], sizeof(dot) / sizeof(dot[0]));
}

// 课堂作业, 使用取点和画点函数绘制显示器部分区域到窗口上
void OnPaint_pixelBlt(PWINDOW_DATA pWnd, HDC hdc)
{
    HDC hdcDesktop = GetDC(0);
    const int xStart = 1930;
    const int yStart = 10;
    const int count = 20;
    for ( int y = yStart; y < yStart + count; y++ )
    {
        for ( int x = xStart; x < xStart + count; x++ )
        {
            COLORREF clr = GetPixel(hdcDesktop, x, y);
            SetPixelV(hdc, 50 + x - xStart, 50 + y - yStart, clr);
            //output(L"0x%08X = GetPixel(%d, %d)\n", clr, x, y);
        }
    }
    ReleaseDC(0, hdcDesktop);
}

void OnPaint_Polyline(PWINDOW_DATA pWnd, HDC hdc)
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


    DWORD asz[] = {6, 4, 3};
    PolyPolyline(hdc, pt, asz, sizeof(asz) / sizeof(asz[0]));

    GetCurrentPositionEx(hdc, &nowPt2);

    output(L"画线之前的坐标 = {%d,%d}. 画线之后的坐标 = {%d,%d}\n",
        nowPt1.x, nowPt1.y, nowPt2.x, nowPt2.y);
}


//课堂作业, 使用画线的方式绘制一个五角星
void OnPaint_star(PWINDOW_DATA pWnd, HDC hdc)
{
    if ( 0 )
    {
        MoveToEx(hdc, 68, 128, 0);
        LineTo(hdc, 183, 128);
        LineTo(hdc, 80, 200);
        LineTo(hdc, 105, 67);
        LineTo(hdc, 146, 200);
        LineTo(hdc, 68, 128);
    }
    else
    {
        POINT pt[] =
        {
            { 68    , 128 },
            { 183   , 128 },
            { 80    , 200 },
            { 105   , 67  },
            { 146   , 200 },
            { 68    , 128 },
        };
        Polyline(hdc, pt, sizeof(pt) / sizeof(pt[0]));
    }
}
