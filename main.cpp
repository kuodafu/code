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
        m_index = 0;
        DWORD style = WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS
            | LBS_NOTIFY | LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT;
        if ( 0 )
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

            for( LPCWSTR s : str )
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