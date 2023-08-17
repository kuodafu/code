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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = 0;// MAKEINTRESOURCEW(IDC_MY);
    wcex.lpszClassName  = L"吹牛装逼群: 20752843";
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    int r = SendMessageW(hBtn, BM_GETCHECK, 0, 0);
    return r == BST_CHECKED;
}
