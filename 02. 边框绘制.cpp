#include "pch.h"

#if 0
// ͼ�α������.cpp : ����Ӧ�ó������ڵ㡣
//
#include "pch.h"
#include <CommCtrl.h>

LRESULT Wndproc_static(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void re_calc_static_pos(HWND hWnd);





#define ID_DOTLINE  1000    // ���㻭��

#define ID_STATIC_LEFTTOP       2001    // ����, ��������
#define ID_STATIC_RIGHTBOTTOM   2002    // ����, ��������

#define ID_STATIC_TOP           2003    // ����, ��������
#define ID_STATIC_BOTTOM        2004    // �ױ�, ��������

static int m_right;     // �����ұߵľ���
static int m_bottom;    // ����ױߵľ���


LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain_02(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˴����ô��롣



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
    wcex.lpszClassName = L"��ţװ��Ⱥ: 20752843";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    ATOM atom = RegisterClassExW(&wcex);

    // ִ��Ӧ�ó����ʼ��:
    g_hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

    WINDOW_DATA wnd = { 0 };
    HWND hWnd = CreateWindowExW(0, wcex.lpszClassName, L"����: ���� (@����) kuodafu.com", WS_OVERLAPPEDWINDOW,
        1920 + 100, 100, 800, 600, nullptr, nullptr, hInstance, &wnd);

    int ret = 0;
    if (hWnd)
    {
        ShowWindow(hWnd, nCmdShow);
        UpdateWindow(hWnd);

        HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY));

        MSG msg;

        // ����Ϣѭ��:
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
    ClientToScreen(hParent, &pt);  // �õ����ڵĿͻ�������Ļ�ϵ�����

    // ��ȡ����ڸ��������λ��
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

    // rc1 = ��ʾ���ε�λ��
    // rc2 = ��һ������͵ڶ��������λ��
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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
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
        //CreateWindowExW(0, WC_BUTTONW, L"���㻭��", style, 10, 10, 80, 32, hWnd, (HMENU)ID_DOTLINE, 0, 0);

        auto pfn_create = [hWnd](int left, int top, int id)
            {
                const DWORD style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
                const int width = 20;

                HWND hStatic = CreateWindowExW(0, L"#32770", 0, style,
                    left, top, width, width, hWnd, (HMENU)(LONG_PTR)id, 0, 0);
                // ��ǩ�����໯��Ϣ������
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
        // �����˵�ѡ��:
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
    ClientToScreen(hWnd, &pt);  // �õ����ڵĿͻ�������Ļ�ϵ�����

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
        swprintf_s(dbg, L"���γߴ�{%d,%d,%d,%d}, �ڶ�����{%d,%d,%d,%d}",
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
//    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);   // �����������
//
//
//    // rc1 = ��ʾ���ε�λ��
//    // rc2 = ��һ������͵ڶ��������λ��
//    RECT rc1, rc2;
//    GetStaticRect(pWnd->hWnd, rc1, rc2);
//
//    Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
//
//
//    //Rectangle     (������)
//    //Ellipse       (����Բ)
//    //RoundRect     (��Բ�Ǿ���)
//    //Arc           (����)
//    //Chord         (����)
//    //Pie           (����)
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

