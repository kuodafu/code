#include "pch.h"
#include <math.h>
#include <vector>
#define PI 3.1415926

#if 0
// 图形编程入门.cpp : 定义应用程序的入口点。
//

#include "pch.h"
#include <CommCtrl.h>

// 全局变量:
HINSTANCE g_hInst;                                // 当前实例

#define ID_STAR     1000    // 画星
#define ID_POLYLINE 1001    // 画折线

#define ID_TIMER    1002    // 定时器

#define ID_CHECK    1003    // 复选框, 选择模式
#define ID_VISIBLE  1004    // 复选框, 显示隐藏组件



static int m_right;     // 距离右边的距离
static int m_bottom;    // 距离底边的距离


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                      _In_opt_ HINSTANCE hPrevInstance,
                      _In_ LPWSTR    lpCmdLine,
                      _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。



    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;// MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName = L"吹牛装逼群: 20752843";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    ATOM atom = RegisterClassExW(&wcex);

    // 执行应用程序初始化:
    g_hInst = hInstance; // 将实例句柄存储在全局变量中

    WINDOW_DATA wnd = { 0 };
    HWND hWnd = CreateWindowExW(0, wcex.lpszClassName, L"主讲: 福仔 (@扩大福) kuodafu.com",
                                WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
                                1920 + 100, 100, 800, 600, nullptr, nullptr, hInstance, &wnd);

    int ret = 0;
    if ( hWnd )
    {
        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);

        HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

        MSG msg;

        // 主消息循环:
        while ( GetMessage(&msg, nullptr, 0, 0) )
        {
            if ( !TranslateAccelerator(msg.hwnd, hAccelTable, &msg) )
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        ret = (int)msg.wParam;
    }
    return ret;
}



//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if ( message == WM_NCCREATE )
    {
        LPCREATESTRUCTW cs = (LPCREATESTRUCTW)lParam;
        PWINDOW_DATA pWnd = (PWINDOW_DATA)cs->lpCreateParams;
        pWnd->hWnd = hWnd;
        SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
    }
    PWINDOW_DATA pWnd = (PWINDOW_DATA)GetWindowLongPtrW(hWnd, GWLP_USERDATA);


    switch ( message )
    {
    case WM_CREATE:
    {
        DWORD style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
        CreateWindowExW(0, WC_BUTTONW, L"画星", style, 10, 10, 80, 32, hWnd, (HMENU)ID_STAR, 0, 0);
        CreateWindowExW(0, WC_BUTTONW, L"画图形", style, 10, 10, 80, 32, hWnd, (HMENU)ID_POLYLINE, 0, 0);

        CreateWindowExW(0, WC_BUTTONW, L"选中 = ALTERNATE, 否则 = WINDING",
                        style | BS_AUTOCHECKBOX, 10, 10, 80, 32, hWnd, (HMENU)ID_CHECK, 0, 0);

        CreateWindowExW(0, WC_BUTTONW, L"隐藏",
                        style | BS_AUTOCHECKBOX, 10, 10, 80, 32, hWnd, (HMENU)ID_VISIBLE, 0, 0);


        break;
    }
    case WM_SIZE:
    {
        const int cxClient = LOWORD(lParam);
        const int cyClient = HIWORD(lParam);
        HWND hBtn1 = GetDlgItem(hWnd, ID_STAR);
        HWND hBtn2 = GetDlgItem(hWnd, ID_POLYLINE);
        HWND hBtn3 = GetDlgItem(hWnd, ID_CHECK);
        HWND hBtn4 = GetDlgItem(hWnd, ID_VISIBLE);

        MoveWindow(hBtn1, 10, 10, 600, 32, TRUE);
        MoveWindow(hBtn2, 10, 48, 600, 32, TRUE);
        MoveWindow(hBtn3, 10, 88, 600, 32, TRUE);

        MoveWindow(hBtn4, 620, 10, 50, 20, TRUE);

        break;
    }
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        // 分析菜单选择:
        switch ( id )
        {
        case ID_STAR:
        {
            void OnPaint_star_04(PWINDOW_DATA pWnd, HDC hdc);
            HDC hdc = GetDC(hWnd);
            OnPaint_star_04(pWnd, hdc);
            ReleaseDC(hWnd, hdc);
            break;
        }
        case ID_POLYLINE:
        {
            void OnPaint_rect_04(PWINDOW_DATA pWnd, HDC hdc);
            HDC hdc = GetDC(hWnd);
            OnPaint_rect_04(pWnd, hdc);
            ReleaseDC(hWnd, hdc);
            break;
        }
        case ID_CHECK:
            InvalidateRect(hWnd, 0, 0);
            break;
        case ID_VISIBLE:
        {
            HWND hBtn = GetDlgItem(hWnd, ID_VISIBLE);
            const bool isCheck = SendMessageW(hBtn, BM_GETCHECK, 0, 0) == BST_CHECKED;
            HWND hWnds[] =
            {
                GetDlgItem(hWnd, ID_STAR),
                GetDlgItem(hWnd, ID_POLYLINE),
                GetDlgItem(hWnd, ID_CHECK),
            };
            for ( HWND h : hWnds )
            {
                ShowWindow(h, isCheck ? SW_HIDE : SW_SHOW);
            }
            SetTimer(hWnd, 10001, 100, [](HWND hWnd, UINT msg, UINT_PTR id, DWORD q)
            {
                KillTimer(hWnd, id);
                WndProc(hWnd, WM_COMMAND, ID_POLYLINE, 0);
            });
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        void OnPaint_04(PWINDOW_DATA pWnd, HDC hdc);
        OnPaint_04(pWnd, hdc);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

bool isCheck(HWND hParent)
{
    HWND hBtn = GetDlgItem(hParent, ID_CHECK);
    int r = (int)(INT_PTR)SendMessageW(hBtn, BM_GETCHECK, 0, 0);
    return r == BST_CHECKED;
}

#endif

void OnPaint_Polygon_04(PWINDOW_DATA pWnd, HDC hdc);
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
    //OnPaint_Polygon_04(pWnd, hdc);
    //OnPaint_star_04(pWnd, hdc);
    //OnPaint_04_1(pWnd, hdc);
    return;

    HBRUSH hbrOld = (HBRUSH)GetCurrentObject(hdc, OBJ_BRUSH);
    HPEN hpenOld = (HPEN)GetCurrentObject(hdc, OBJ_PEN);

    HBRUSH hbr = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, hbr);
    SelectObject(hdc, GetStockObject(NULL_PEN));


    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    // 填充整个窗口, 背景是红色
    //Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
    FillRect(hdc, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

    rc = { 50, 50, 150, 200 };
    Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);


    // 恢复画刷
    SelectObject(hdc, hbrOld);
    SelectObject(hdc, hpenOld);
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

        LOGBRUSH lb = { 0 };
        const int size1 = GetObjectW(hbr, 0, 0);
        const int size2 = GetObjectW(hbr, sizeof(lb), &lb);

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



void OnPaint_Polygon_04(PWINDOW_DATA pWnd, HDC hdc)
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

    Polygon(hdc, pt, sizeof(pt) / sizeof(pt[0]));

    DWORD asz[] = { 6, 4, 4 };
    //PolyPolygon(hdc, pt, (INT*)asz, sizeof(asz) / sizeof(asz[0]));

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
    Polygon(hdc, &apt[0], (int)apt.size());

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



