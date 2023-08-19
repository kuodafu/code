#include "pch.h"

void OnPaint_05_line1(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_line2(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_line3(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_black_dot(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_iphone5(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_ddm(HWND hwnd, HDC hdc);

#if 0
// 图形编程入门.cpp : 定义应用程序的入口点。
//

#include "pch.h"
#include <CommCtrl.h>

// 全局变量:
HINSTANCE g_hInst;                                // 当前实例

#define ID_LISTBOX  1001
#define ID_CHECK    1002
static int m_index;

int GetListIndex()
{
    return m_index;
}

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
        m_index = 0;
        DWORD style = WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS
            | LBS_NOTIFY | LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT;
        if ( 1 )
        {
            HWND hList = CreateWindowExW(WS_EX_CLIENTEDGE, WC_LISTBOXW, 0,
                                         style, 0, 0, 0, 0, hWnd, (HMENU)ID_LISTBOX, 0, 0);
            const LPCWSTR str[] =
            {
                L"清除",
                L"画辅助线",
                L"画头",
                L"画脸",
                L"画眼睛",
                L"画鼻子",
                L"画嘴巴",
                L"画胡子",
                L"画身体",
                L"画肚子",
                L"画项圈",
                L"画铃铛",
                L"画口袋",
                L"画脚",
                L"画左手",
                L"画右手",
                L"擦除黑线",
            };

            for ( LPCWSTR s : str )
                SendMessageW(hList, LB_ADDSTRING, 0, (LPARAM)s);
        }

        if ( 0 )
        {
            style = WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | BS_AUTOCHECKBOX;
            CreateWindowExW(0, WC_BUTTONW, L"去掉方格", style, 0, 0, 0, 0, hWnd, (HMENU)ID_CHECK, 0, 0);
        }
        break;
    }
    case WM_SIZE:
    {
        const int cxClient = LOWORD(lParam);
        const int cyClient = HIWORD(lParam);
        HWND hList = GetDlgItem(hWnd, ID_LISTBOX);
        HWND hCheck = GetDlgItem(hWnd, ID_CHECK);

        const int width = 100;
        MoveWindow(hList, cxClient - width, 0, width, cyClient, TRUE);

        MoveWindow(hCheck, 10, 10, 100, 20, TRUE);
        break;
    }
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        // 分析菜单选择:
        switch ( id )
        {
        case ID_LISTBOX:
        {
            if ( HIWORD(wParam) == LBN_SELCHANGE )
            {
                m_index = (int)SendMessageW((HWND)lParam, LB_GETCURSEL, 0, 0);
                InvalidateRect(hWnd, 0, 0);
            }
            break;
        }
        case ID_CHECK:
            InvalidateRect(hWnd, 0, 0);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        void OnPaint_05(PWINDOW_DATA pWnd, HDC hdc);
        OnPaint_05(pWnd, hdc);
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

bool isCheck(HWND hParent)
{
    //HWND hBtn = GetDlgItem(hParent, ID_CHECK);
    //int r = (int)(INT_PTR)SendMessageW(hBtn, BM_GETCHECK, 0, 0);
    //return r == BST_CHECKED;
    return false;
}
void OnPaint_05(PWINDOW_DATA pWnd, HDC hdc)
{
    //OnPaint_05_line1(pWnd, hdc);
    //OnPaint_05_line2(pWnd, hdc);
    //OnPaint_05_line3(pWnd, hdc);
    //OnPaint_05_black_dot(pWnd, hdc);
    //OnPaint_05_iphone5(pWnd, hdc);
    OnPaint_05_ddm(pWnd->hWnd, hdc);
}

// 比较两条直线的长度
void OnPaint_05_line1(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));
    HPEN hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(255, 0, 0));
    HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
    
    MoveToEx(hdc, 100, 100, 0);
    LineTo(hdc, 100, 300);
    
    SelectObject(hdc, hPenOld);
    
    MoveToEx(hdc, 50, 50, 0);
    LineTo(hdc, 100, 100);
    LineTo(hdc, 150, 50);
    
    MoveToEx(hdc, 50, 350, 0);
    LineTo(hdc, 100, 300);
    LineTo(hdc, 150, 350);
    
    SelectObject(hdc, hPen);
    MoveToEx(hdc, 400, 100, 0);
    LineTo(hdc, 400, 300);
    SelectObject(hdc, hPenOld);
    
    MoveToEx(hdc, 350, 150, 0);
    LineTo(hdc, 400, 100);
    LineTo(hdc, 450, 150);
    MoveToEx(hdc, 350, 250, 0);
    LineTo(hdc, 400, 300);
    LineTo(hdc, 450, 250);
    DeleteObject(hPen);
}
// 比较两条直线的长度2
void OnPaint_05_line2(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect (pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect (hdc, &rcClient, (HBRUSH)GetStockObject (WHITE_BRUSH));

    HPEN hPen = CreatePen (PS_SOLID, 1, 0);
    HPEN hPenOld = (HPEN)SelectObject (hdc, hPen);
    for ( int i = 0; i < 11; i++ )
    {
        MoveToEx(hdc, cxClient / 2, 20, 0);
        LineTo(hdc, cxClient / 2 - 250 + i * 50, 520);
    }

    SelectObject (hdc, hPenOld);
    DeleteObject (hPen);
    hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(255, 0, 0));
    hPenOld = (HPEN)SelectObject (hdc, hPen);
    MoveToEx (hdc, cxClient / 2 - 50, 120, 0);
    LineTo (hdc, cxClient / 2 + 50, 120);

    MoveToEx (hdc, cxClient / 2 - 50, 520, 0);
    LineTo (hdc, cxClient / 2 + 50, 520);
    //SelectObject (hdc, GetStockObject (NULL_BRUSH));
    //Rectangle (hdc, cxClient / 2 - 50, 120, cxClient / 2 + 50, 520);

    SelectObject (hdc, hPenOld);
    DeleteObject(hPen);

}
// 比较两条直线的长度3, 平行线
void OnPaint_05_line3(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(105, 105, 105));
    HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

    HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));

    bool isCheck(HWND hParent);
    const bool bCheck = isCheck(pWnd->hWnd);
    int nLeft = 0;
    bool b = false;

    const int count_col = (cyClient - 100) / 50 + 1;


    for ( int i = 0; i < count_col; i++ )
    {
        const int y = 100 + i * 50;
        MoveToEx(hdc, 50, y, 0);
        LineTo(hdc, cxClient - 50, y);

        if ( !bCheck )
        {
            const int count = (cxClient - 100) / 50 + 1;
            for ( int n = 0; n < count; n += 2 )
            {
                RECT rcDraw;
                rcDraw.left = nLeft + 50 + n * 50;
                rcDraw.top = 50 + i * 50;
                rcDraw.right = rcDraw.left + 50;
                rcDraw.bottom = rcDraw.top + 50;
                Rectangle(hdc, rcDraw.left, rcDraw.top, rcDraw.right, rcDraw.bottom);
            }


            if ( (i + 1) % 3 == 0 )
            {
                b = !b;
            }

            if ( !b )
            {
                nLeft += 50 / 3;
            }
            else
            {
                nLeft -= 50 / 3;
            }
        }



    }

    SelectObject(hdc, hPenOld);
    SelectObject(hdc, hBrushOld);
    DeleteObject(hPen);
}
// 画黑点, 数一数有几个黑点
void OnPaint_05_black_dot(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(BLACK_BRUSH));

    HPEN hPen = CreatePen(PS_INSIDEFRAME, 10, RGB(135, 135, 135));
    HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

    const int count1 = cxClient / 50 + 1;
    for ( int i = 0; i < count1; i++ )
    {
        const int x = 20 + i * 50;
        MoveToEx(hdc, x, 0, 0);
        LineTo(hdc, x, cyClient);
    }
    const int count2 = cyClient / 50 + 1;
    for ( int i = 0; i < count2; i++ )
    {
        const int y = 20 + i * 50;
        MoveToEx(hdc, 0, y, 0);
        LineTo(hdc, cxClient, y);
    }

    HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, GetStockObject(WHITE_PEN));

    for ( int i = 0; i < count1; i++ )
    {
        for ( int j = 0; j < count2; j++ )
        {
            const int x = 20 + i * 50;
            const int y = 20 + j * 50;
            const int r = 7;
            Ellipse(hdc, x - r, y - r, x + r, y + r);
        }
    }

    SelectObject(hdc, hPenOld);
    SelectObject(hdc, hBrushOld);
    DeleteObject(hPen);

}
// 画苹果5
void OnPaint_05_iphone5(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

    HPEN hPen = CreatePen(PS_DOT, 0, RGB(128, 128, 128));
    HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

    // ----------画辅助线
    MoveToEx (hdc, cxClient / 2, 0, 0);
    LineTo (hdc, cxClient / 2, cyClient);

    MoveToEx (hdc, 0, cyClient / 2, 0);
    LineTo (hdc, cxClient, cyClient / 2);

    SelectObject (hdc, hPenOld);
    DeleteObject (hPen);
    hPen = 0;

    // -----------画外框
    RoundRect (hdc, cxClient / 2 - 110, 50, cxClient / 2 + 110, cyClient - 50, 50, 50);
    RoundRect (hdc, cxClient / 2 - 110 + 3, 50 + 3, cxClient / 2 + 110 - 3, cyClient - 50 - 3, 50 - 2, 50 - 2);

    // -------------画电源键
    RoundRect (hdc, cxClient / 2 + 110 - 30 - 30, 49, cxClient / 2 + 110 - 30, 50, 1, 1);

    // 画音量键
    RoundRect (hdc, cxClient / 2 - 110 - 1, 110, cxClient / 2 - 110, 135, 0, 3);
    RoundRect (hdc, cxClient / 2 - 110 - 1, 155, cxClient / 2 - 110, 170, 0, 3);

    RoundRect (hdc, cxClient / 2 - 110 - 1, 185, cxClient / 2 - 110, 200, 0, 3);


    // ---------画前置摄像头
    HGDIOBJ hBrushOld = SelectObject (hdc, GetStockObject (BLACK_BRUSH));
    Ellipse (hdc, cxClient / 2 - 5, 65, cxClient / 2 + 5, 75);
    SelectObject (hdc, hBrushOld);

    Ellipse (hdc, cxClient / 2 - 25 - 8, 83, cxClient / 2 - 25, 91);
    RoundRect (hdc, cxClient / 2 - 20, 85, cxClient / 2 + 20, 90, 2, 2);

    // --------画屏幕;
    int nHeight = 110;
    Rectangle (hdc, cxClient / 2 - 100, 110, cxClient / 2 + 100, cyClient - nHeight);
    MoveToEx (hdc, cxClient / 2 - 100, 110, 0);
    LineTo (hdc, cxClient / 2 + 100, cyClient - nHeight);

    // ---------画home键;
    Ellipse (hdc, cxClient / 2 - 20, cyClient - 110 + 10, cxClient / 2 + 20, cyClient - 110 + 10 + 40);
    hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    hPenOld = (HPEN)SelectObject (hdc, hPen);
    Rectangle (hdc, cxClient / 2 - 10, cyClient - 110 + 20, cxClient / 2 + 10, cyClient - 110 + 20 + 20);
    SelectObject (hdc, hPenOld);
    DeleteObject (hPen);
    hPen = 0;

    // -----------画4条边框线;
    Rectangle (hdc, cxClient / 2 - 107, 80, cxClient / 2 - 110, 82);
    Rectangle (hdc, cxClient / 2 + 107, 80, cxClient / 2 + 110, 82);
    Rectangle (hdc, cxClient / 2 - 107, cyClient - 85, cxClient / 2 - 110, cyClient - 85 + 2);
    Rectangle (hdc, cxClient / 2 + 107, cyClient - 85, cxClient / 2 + 110, cyClient - 85 + 2);


}
// 画叮当猫
void OnPaint_05_ddm(HWND hwnd, HDC hdc)
{
    RECT rect;
    HPEN hBlackPen = 0, hOldPen, hWhite2Pen = 0;
    HBRUSH hOldBrush = 0, hRedBrush = 0, hYellowBrush = 0;
    HBRUSH blue_brush = 0;
    HPEN blue_pen = 0;
    POINT pxRightHand[4], pxiLeftHand[4];

    //int GetListIndex();
    const int index = 0;// GetListIndex();


    
    GetClientRect(hwnd, &rect);//获取客户矩形
    rect.right -= 100;  // 减去列表框的宽度
    const int cxClient = rect.right - rect.left;
    const int cyClient = rect.bottom - rect.top;
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

    // 绘制十字定位线
    if ( index > 0 )
    {
        HPEN hPen = CreatePen(PS_DOT, 1, RGB(135, 135, 135));//创建十字定位线型
        hOldPen = (HPEN)SelectObject(hdc, hPen);//将画笔选人设备环境句柄并保存原本画笔

        MoveToEx(hdc, 0, rect.bottom / 2, NULL);//
        LineTo(hdc, rect.right, rect.bottom / 2);

        MoveToEx(hdc, rect.right / 2, 0, NULL);
        LineTo(hdc, rect.right / 2, rect.bottom);
        DeleteObject(SelectObject(hdc, hOldPen));
    }




    //绘制头部 直径240
    if ( index > 1 )
    {
        hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//创建黑色画笔
        SelectObject(hdc, hBlackPen);

        blue_brush = CreateSolidBrush(RGB(0, 159, 232));    //蓝色画刷
        hOldBrush = (HBRUSH)SelectObject(hdc, blue_brush);
        Ellipse(hdc, rect.right / 2 - 120, rect.bottom / 2 - 200, rect.right / 2 + 120, rect.bottom / 2 + 40);
        SelectObject(hdc, hOldBrush);
    }

    //绘制脸(直径200)
    if ( index > 2 )
    {
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 100, rect.bottom / 2 - 160, rect.right / 2 + 100, rect.bottom / 2 + 40);
    }

    //绘制眼睛(眼白 高60,宽50)
    if ( index > 3 )
    {
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 50, rect.bottom / 2 - 190, rect.right / 2, rect.bottom / 2 - 130);
        Ellipse(hdc, rect.right / 2, rect.bottom / 2 - 190, rect.right / 2 + 50, rect.bottom / 2 - 130);

        //绘制瞳孔( 距中心4 宽16,高30)
        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        Ellipse(hdc, rect.right / 2 - 20, rect.bottom / 2 - 170, rect.right / 2 - 4, rect.bottom / 2 - 140);
        Ellipse(hdc, rect.right / 2 + 4, rect.bottom / 2 - 170, rect.right / 2 + 20, rect.bottom / 2 - 140);

        //绘制瞳孔中心白点
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 15, rect.bottom / 2 - 160, rect.right / 2 - 8, rect.bottom / 2 - 150);
        Ellipse(hdc, rect.right / 2 + 8, rect.bottom / 2 - 160, rect.right / 2 + 15, rect.bottom / 2 - 150);

    }

    if ( index > 4 )
    {
        //绘制鼻子(直径20)
        hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hRedBrush);
        Ellipse(hdc, rect.right / 2 - 10, rect.bottom / 2 - 143, rect.right / 2 + 10, rect.bottom / 2 - 123);

        //绘制鼻子到嘴中间线(长85)
        MoveToEx(hdc, rect.right / 2, rect.bottom / 2 - 123, NULL);
        LineTo(hdc, rect.right / 2, rect.bottom / 2 - 38);

    }

    //绘制嘴巴
    if ( index > 5 )
    {
        Arc(hdc, rect.right / 2 - 60, rect.bottom / 2 - 98, rect.right / 2 + 60, rect.bottom / 2 - 38,
            rect.right / 2 - 50, rect.bottom / 2 - 58, rect.right / 2 + 50, rect.bottom / 2 - 58);
    }

    //绘制胡子
    if ( index > 6 )
    {
        MoveToEx(hdc, rect.right / 2 - 15, rect.bottom / 2 - 88, NULL);
        LineTo(hdc, rect.right / 2 - 70, rect.bottom / 2 - 88);

        MoveToEx(hdc, rect.right / 2 + 15, rect.bottom / 2 - 88, NULL);
        LineTo(hdc, rect.right / 2 + 70, rect.bottom / 2 - 88);

        MoveToEx(hdc, rect.right / 2 - 15, rect.bottom / 2 - 98, NULL);
        LineTo(hdc, rect.right / 2 - 70, rect.bottom / 2 - 115);

        MoveToEx(hdc, rect.right / 2 + 15, rect.bottom / 2 - 98, NULL);
        LineTo(hdc, rect.right / 2 + 70, rect.bottom / 2 - 115);

        MoveToEx(hdc, rect.right / 2 - 15, rect.bottom / 2 - 78, NULL);
        LineTo(hdc, rect.right / 2 - 70, rect.bottom / 2 - 61);

        MoveToEx(hdc, rect.right / 2 + 15, rect.bottom / 2 - 78, NULL);
        LineTo(hdc, rect.right / 2 + 70, rect.bottom / 2 - 61);

    }

    if ( index > 7 )
    {
        //绘制身体(长方形 高150,宽180)
        SelectObject(hdc, blue_brush);
        Rectangle(hdc, rect.right / 2 - 90, rect.bottom / 2, rect.right / 2 + 90, rect.bottom / 2 + 150);
    }

    if ( index > 8 )
    {
        //绘制肚子(圆形 直径140)
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 70, rect.bottom / 2 - 20, rect.right / 2 + 70, rect.bottom / 2 + 120);//绘制白色肚子

        hWhite2Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//创建一个像素为2的白色实线画笔
        SelectObject(hdc, hWhite2Pen);
        Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 + 70, cyClient / 2 + 120,
            rect.right / 2 + 60, rect.bottom / 2 - 10, rect.right / 2 - 60, rect.bottom / 2 - 10);//覆盖黑色弧线
    }

    if ( index > 9 )
    {
        //绘制项圈
        SelectObject(hdc, hRedBrush);
        SelectObject(hdc, hBlackPen);
        RoundRect(hdc, rect.right / 2 - 95, rect.bottom / 2 - 5, rect.right / 2 + 95, rect.bottom / 2 + 10, 20, 20);
    }

    if ( index > 10 )
    {
        //绘制铃铛
        hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
        SelectObject(hdc, hYellowBrush);
        Ellipse(hdc, rect.right / 2 - 15, rect.bottom / 2, rect.right / 2 + 15, rect.bottom / 2 + 30);
        MoveToEx(hdc, rect.right / 2 - 13, rect.bottom / 2 + 13, NULL);//绘制铃铛横杆
        LineTo(hdc, rect.right / 2 + 13, rect.bottom / 2 + 13);

        MoveToEx(hdc, rect.right / 2 - 13, rect.bottom / 2 + 17, NULL);
        LineTo(hdc, rect.right / 2 + 13, rect.bottom / 2 + 17);

        SelectObject(hdc, hRedBrush);
        Ellipse(hdc, rect.right / 2 - 4, rect.bottom / 2 + 19, rect.right / 2 + 4, rect.bottom / 2 + 27);//绘制铃铛红圈

        MoveToEx(hdc, rect.right / 2, rect.bottom / 2 + 27, NULL);
        LineTo(hdc, rect.right / 2, rect.bottom / 2 + 30);//绘制铃铛红圈下横线
    }

    if ( index > 11 )
    {
        //百宝袋(直径100)
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Chord(hdc, rect.right / 2 - 50, rect.bottom / 2 - 20, rect.right / 2 + 50, rect.bottom / 2 + 100,
              rect.right / 2 - 50, rect.bottom / 2 + 50, rect.right / 2 + 50, rect.bottom / 2 + 50);
        //Pie(hdc, cxClient / 2 - 50, cyClient / 2, cxClient / 2 + 50, cyClient / 2 + 100,
        //    cxClient / 2 - 50, cyClient / 2 + 50, cxClient / 2 + 50, cyClient / 2 + 50);
    }

    if ( index > 12 )
    {
        //绘制腿间空白
        Chord(hdc, rect.right / 2 - 20, rect.bottom / 2 + 130, rect.right / 2 + 20, rect.bottom / 2 + 170,
              rect.right / 2 + 20, rect.bottom / 2 + 150, rect.right / 2 - 20, rect.bottom / 2 + 150);//绘制
        
        //Pie(hdc, rect.right / 2 - 20, rect.bottom / 2 + 130, rect.right / 2 + 20, rect.bottom / 2 + 170,
        //      rect.right / 2 + 20, rect.bottom / 2 + 150, rect.right / 2 - 20, rect.bottom / 2 + 150);//绘制

        SelectObject(hdc, hWhite2Pen);
        MoveToEx(hdc, rect.right / 2 - 20, rect.bottom / 2 + 150, NULL);
        LineTo(hdc, rect.right / 2 + 20, rect.bottom / 2 + 150);//擦除腿间黑线

        //绘制脚掌
        SelectObject(hdc, GetStockObject(BLACK_PEN));
        Ellipse(hdc, rect.right / 2 - 110, rect.bottom / 2 + 130, rect.right / 2 - 10, rect.bottom / 2 + 170);//绘制右脚掌
        Ellipse(hdc, rect.right / 2 + 110, rect.bottom / 2 + 130, rect.right / 2 + 10, rect.bottom / 2 + 170);//绘制左脚掌
    }

    //画左手
    if ( index > 13 )
    {
        SelectObject(hdc, blue_brush);
        pxiLeftHand[0].x = rect.right / 2 - 90;
        pxiLeftHand[0].y = rect.bottom / 2 + 10;

        pxiLeftHand[1].x = rect.right / 2 - 130;
        pxiLeftHand[1].y = rect.bottom / 2 + 50;

        pxiLeftHand[2].x = rect.right / 2 - 110;
        pxiLeftHand[2].y = rect.bottom / 2 + 70;

        pxiLeftHand[3].x = rect.right / 2 - 90;
        pxiLeftHand[3].y = rect.bottom / 2 + 60;
        Polygon(hdc, pxiLeftHand, 4);

        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 150, rect.bottom / 2 + 46, rect.right / 2 - 110, rect.bottom / 2 + 86);//绘制右手掌
    }

    //画右手
    if ( index > 14 )
    {
        SelectObject(hdc, blue_brush);
        pxRightHand[0].x = rect.right / 2 + 90;
        pxRightHand[0].y = rect.bottom / 2 + 10;

        pxRightHand[1].x = rect.right / 2 + 130;
        pxRightHand[1].y = rect.bottom / 2 + 50;

        pxRightHand[2].x = rect.right / 2 + 110;
        pxRightHand[2].y = rect.bottom / 2 + 70;

        pxRightHand[3].x = rect.right / 2 + 89;
        pxRightHand[3].y = rect.bottom / 2 + 60;

        Polygon(hdc, pxRightHand, 4);
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 + 150, rect.bottom / 2 + 46, rect.right / 2 + 110, rect.bottom / 2 + 86);//绘制右手掌
    }

    //擦除手臂与身体连接黑线
    if ( index > 15 )
    {
        blue_pen = CreatePen(PS_SOLID, 3, RGB(0, 159, 232));//蓝色画笔
        SelectObject(hdc, blue_pen);
        MoveToEx(hdc, rect.right / 2 - 90, rect.bottom / 2 + 10, NULL);
        LineTo(hdc, rect.right / 2 - 90, rect.bottom / 2 + 50);

        MoveToEx(hdc, rect.right / 2 + 90, rect.bottom / 2 + 10, NULL);
        LineTo(hdc, rect.right / 2 + 90, rect.bottom / 2 + 50);
    }

    DeleteObject(hBlackPen);
    DeleteObject(hWhite2Pen);
    DeleteObject(hRedBrush);
    DeleteObject(hYellowBrush);
    DeleteObject(blue_brush);
    DeleteObject(blue_pen);
}
