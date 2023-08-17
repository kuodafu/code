#include "pch.h"

#if 0
// 图形编程入门.cpp : 定义应用程序的入口点。
//
#include "pch.h"
#include <CommCtrl.h>

LRESULT Wndproc_static(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void re_calc_static_pos(HWND hWnd);





#define ID_DOTLINE  1000    // 画点画线

#define ID_STATIC_LEFTTOP       2001    // 左上, 调整矩形
#define ID_STATIC_RIGHTBOTTOM   2002    // 右下, 调整矩形

#define ID_STATIC_TOP           2003    // 顶边, 调整坐标
#define ID_STATIC_BOTTOM        2004    // 底边, 调整坐标

static int m_right;     // 距离右边的距离
static int m_bottom;    // 距离底边的距离


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain_02(_In_ HINSTANCE hInstance,
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
    HWND hWnd = CreateWindowExW(0, wcex.lpszClassName, L"主讲: 福仔 (@扩大福) kuodafu.com", WS_OVERLAPPEDWINDOW,
        1920 + 100, 100, 800, 600, nullptr, nullptr, hInstance, &wnd);

    int ret = 0;
    if (hWnd)
    {
        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);

        HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

        MSG msg;

        // 主消息循环:
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        ret = (int)msg.wParam;
    }
    return ret;
}



void GetStaticRect(HWND hParent, RECT& rc1, RECT& rc2)
{
    POINT pt = { 0 };
    ClientToScreen(hParent, &pt);  // 得到窗口的客户区在屏幕上的坐标

    // 获取组件在父窗口里的位置
    auto pfn_getpos = [pt, hParent](int id, RECT& rc)
        {
            GetWindowRect(GetDlgItem(hParent, id), &rc);
            const int cxStatic = rc.right - rc.left;
            const int cyStatic = rc.bottom - rc.top;
            rc.left -= pt.x;
            rc.top -= pt.y;
            rc.right = rc.left + cxStatic;
            rc.bottom = rc.top + cyStatic;
        };

    RECT rcs[4];
    pfn_getpos(ID_STATIC_LEFTTOP, rcs[0]);
    pfn_getpos(ID_STATIC_RIGHTBOTTOM, rcs[1]);
    pfn_getpos(ID_STATIC_TOP, rcs[2]);
    pfn_getpos(ID_STATIC_BOTTOM, rcs[3]);

    // rc1 = 显示矩形的位置
    // rc2 = 第一个坐标和第二个坐标的位置
    rc1.left = rcs[0].right;
    rc1.top = rcs[0].bottom;
    rc1.right = rcs[1].left;
    rc1.bottom = rcs[1].top;

    rc2.left = rcs[2].right;
    rc2.top = rcs[2].bottom;
    rc2.right = rcs[3].left;
    rc2.bottom = rcs[3].top;
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
    if (message == WM_NCCREATE)
    {
        LPCREATESTRUCTW cs = (LPCREATESTRUCTW)lParam;
        PWINDOW_DATA pWnd = (PWINDOW_DATA)cs->lpCreateParams;
        pWnd->hWnd = hWnd;
        SetWindowLongPtrW(hWnd, GWLP_USERDATA, (LONG_PTR)pWnd);
    }
    PWINDOW_DATA pWnd = (PWINDOW_DATA)GetWindowLongPtrW(hWnd, GWLP_USERDATA);


    switch (message)
    {
    case WM_CREATE:
    {
        DWORD style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
        //CreateWindowExW(0, WC_BUTTONW, L"画点画线", style, 10, 10, 80, 32, hWnd, (HMENU)ID_DOTLINE, 0, 0);

        auto pfn_create = [hWnd](int left, int top, int id)
            {
                const DWORD style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
                const int width = 20;

                HWND hStatic = CreateWindowExW(0, L"#32770", 0, style,
                    left, top, width, width, hWnd, (HMENU)(LONG_PTR)id, 0, 0);
                // 标签的子类化消息处理函数
                auto oldProc = SetWindowLongPtrW(hStatic, GWLP_WNDPROC, (LONG_PTR)Wndproc_static);
                SetPropW(hStatic, L"proc", (LPVOID)oldProc);
            };

        RECT rc;
        GetClientRect(hWnd, &rc);
        const int cxClient = rc.right - rc.left;
        const int cyClient = rc.bottom - rc.top;
        const int height = 20;

        pfn_create(10, 10, ID_STATIC_LEFTTOP);
        pfn_create(cxClient - height - 100, cyClient - height - 10, ID_STATIC_RIGHTBOTTOM);

        pfn_create(200, 10, ID_STATIC_TOP);
        pfn_create(200, cyClient - height - 10, ID_STATIC_BOTTOM);

        re_calc_static_pos(hWnd);
        break;
    }
    case WM_SIZE:
    {
        const int cxClient = LOWORD(lParam);
        const int cyClient = HIWORD(lParam);
        HWND hBtn = GetDlgItem(hWnd, ID_DOTLINE);

        MoveWindow(hBtn, cxClient - 88, 8, 80, 32, TRUE);

        HWND hStatic = GetDlgItem(hWnd, ID_STATIC_RIGHTBOTTOM);

        SetWindowPos(hStatic, 0,
            cxClient - m_right, cyClient - m_bottom, 0, 0,
            SWP_NOSIZE | SWP_NOZORDER);

        break;
    }
    case WM_COMMAND:
    {
        int id = LOWORD(wParam);
        // 分析菜单选择:
        switch (id)
        {
        case ID_DOTLINE:
        {
            void OnPaint_dot_line(PWINDOW_DATA pWnd, HDC hdc);
            HDC hdc = GetDC(hWnd);
            OnPaint_dot_line(pWnd, hdc);
            ReleaseDC(hWnd, hdc);
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
        void OnPaint_02(PWINDOW_DATA pWnd, HDC hdc);
        OnPaint_02(pWnd, hdc);
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

void re_calc_static_pos(HWND hWnd)
{
    RECT rc;
    GetClientRect(hWnd, &rc);
    const int cxClient = rc.right - rc.left;
    const int cyClient = rc.bottom - rc.top;

    POINT pt = { 0 };
    ClientToScreen(hWnd, &pt);  // 得到窗口的客户区在屏幕上的坐标

    RECT rcStatic;
    GetWindowRect(GetDlgItem(hWnd, ID_STATIC_RIGHTBOTTOM), &rcStatic);
    const int cxStatic = rcStatic.right - rcStatic.left;
    const int cyStatic = rcStatic.bottom - rcStatic.top;
    rcStatic.left -= pt.x;
    rcStatic.top -= pt.y;
    rcStatic.right = rcStatic.left + cxStatic;
    rcStatic.bottom = rcStatic.top + cyStatic;


    m_right = cxClient - rcStatic.left;
    m_bottom = cyClient - rcStatic.top;
}

LRESULT Wndproc_static(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WNDPROC oldProc = (WNDPROC)GetPropW(hWnd, L"proc");
    switch (message)
    {
    case WM_NCHITTEST:
        return HTCAPTION;
    case WM_MOVE:
    {
        const int id = GetDlgCtrlID(hWnd);
        HWND hParent = GetParent(hWnd);
        if (id == ID_STATIC_RIGHTBOTTOM)
        {
            re_calc_static_pos(hParent);
        }
        RECT rc1, rc2;
        GetStaticRect(hParent, rc1, rc2);

        wchar_t dbg[260];
        swprintf_s(dbg, L"矩形尺寸{%d,%d,%d,%d}, 第二坐标{%d,%d,%d,%d}",
            rc1.left, rc1.top, rc1.right, rc1.bottom,
            rc2.left, rc2.top, rc2.right, rc2.bottom
        );
        SetWindowTextW(hParent, dbg);

        InvalidateRect(hParent, 0, 0);
        break;
    }
    case WM_DESTROY:
    {
        SetWindowLongPtrW(hWnd, GWLP_WNDPROC, (LONG_PTR)oldProc);
        RemovePropW(hWnd, L"proc");
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hWnd, &ps);

        RECT rc;
        GetClientRect(hWnd, &rc);

        FillRect(ps.hdc, &rc, (HBRUSH)GetStockObject(GRAY_BRUSH));

        EndPaint(hWnd, &ps);
        return 0;
    }
    default:
        break;
    }
    return CallWindowProcW(oldProc, hWnd, message, wParam, lParam);
};

#endif

//void OnPaint_02(PWINDOW_DATA pWnd, HDC hdc)
//{
//    void GetStaticRect(HWND hParent, RECT & rc1, RECT & rc2);
//
//    RECT rc;
//    GetClientRect(pWnd->hWnd, &rc);
//    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);   // 填充整个窗口
//
//
//    // rc1 = 显示矩形的位置
//    // rc2 = 第一个坐标和第二个坐标的位置
//    RECT rc1, rc2;
//    GetStaticRect(pWnd->hWnd, rc1, rc2);
//
//    Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
//
//
//    //Rectangle     (画矩形)
//    //Ellipse       (画椭圆)
//    //RoundRect     (画圆角矩形)
//    //Arc           (画弧)
//    //Chord         (画弦)
//    //Pie           (画饼)
//    //Ellipse(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
//    //RoundRect(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, 100, 200);
//    //Arc(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, rc2.left, rc2.top, rc2.right, rc2.bottom);
//    //Chord(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, rc2.left, rc2.top, rc2.right, rc2.bottom);
//    Pie(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, rc2.left, rc2.top, rc2.right, rc2.bottom);
//
//
//}
//
//

