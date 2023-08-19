#include "pch.h"
#include <windowsx.h>
void OnPaint_06_textout(PWINDOW_DATA pWnd, HDC hdc);
HFONT OnPaint_06_create_font(int lfHeight = -12, LPCWSTR name = L"΢���ź�");
void paint_06_draw_header(HDC hdc);
void paint_06_draw_item(HDC hdc);
void paint_06_draw_line(HDC hdc);

static int m_head_state, m_item_state, m_index = -1, m_index_old = -1;
static RECT rcClient;
int cxClient;
int cyClient;
const int itemHeight = 24;

enum STATE
{
    NORMAL,
    HOVER,
    DOWN,

};

void OnPaint_06(PWINDOW_DATA pWnd, HDC hdc)
{
    GetClientRect(pWnd->hWnd, &rcClient);
    cxClient = rcClient.right - rcClient.left;
    cyClient = rcClient.bottom - rcClient.top;

    //OnPaint_06_textout(pWnd, hdc);

    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

    paint_06_draw_header(hdc);  // ���Ʊ�ͷ
    paint_06_draw_item(hdc);    // ���Ʊ���
    paint_06_draw_line(hdc);    // ���Ʒָ���
}

void paint_06_draw_header(HDC hdc)
{
    HBRUSH hbr = 0;
    if ( m_head_state == STATE::HOVER )
    {
        hbr = CreateSolidBrush(RGB(0, 222, 222));
    }
    else if ( m_head_state == STATE::DOWN )
    {
        hbr = CreateSolidBrush(RGB(200, 0, 200));
    }
    else
    {
        hbr = CreateSolidBrush(RGB(233, 233, 233));
    }

    RECT rcDraw = { 10, 10, rcClient.right - 50, 40 };
    FillRect(hdc, &rcDraw, hbr);

    HFONT hFont = OnPaint_06_create_font(-18);
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    const wchar_t text[] = L"���Ǳ�ͷ,�����������";
    const int size = sizeof(text) / sizeof(text[0]) - 1;
    SetBkMode(hdc, TRANSPARENT);

    DrawTextW(hdc, text, size, &rcDraw, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

    DeleteObject(hbr);
}
void paint_06_draw_item(HDC hdc)
{
    HBRUSH hbr = 0;
    HBRUSH hbr1 = CreateSolidBrush(RGB(200, 200, 200));
    HBRUSH hbr2 = CreateSolidBrush(RGB(220, 220, 220));
    HFONT hFont1 = OnPaint_06_create_font(-14, L"����");
    HFONT hFont2 = OnPaint_06_create_font(-16, L"Arial");
    HFONT hFontOld = (HFONT)GetCurrentObject(hdc, OBJ_FONT);

    if ( m_item_state == STATE::HOVER )
    {
        hbr = CreateSolidBrush(RGB(180, 0, 180));
    }
    else if ( m_item_state == STATE::DOWN )
    {
        hbr = CreateSolidBrush(RGB(0, 180, 180));
    }
    else
    {
        hbr = CreateSolidBrush(RGB(0255, 255, 255));
    }

    RECT rcDraw = { 10, 40, rcClient.right - 50, rcClient.bottom - 50 };

    const int count = rcClient.bottom / itemHeight;
    wchar_t text[260];
    for ( int i = 0; i < count; i++ )
    {
        rcDraw.bottom = rcDraw.top + itemHeight;
        if ( i % 2 == 0 )
        {
            if ( m_index == i )
            {
                FillRect(hdc, &rcDraw, hbr);
            }
            else
            {
                FillRect(hdc, &rcDraw, hbr1);
            }


            swprintf_s(text, L"���Ǳ���%d, ���Ǻ������, ����Ӷ�", i);
            const int size = wcslen(text);
            SelectObject(hdc, hFont1);
            DrawTextW(hdc, text, size, &rcDraw, DT_LEFT | DT_TOP);
        }
        else
        {
            if ( m_index == i )
            {
                FillRect(hdc, &rcDraw, hbr);
            }
            else
            {
                FillRect(hdc, &rcDraw, hbr2);
            }

            swprintf_s(text, L"���Ǳ���%d, ���Ǻ������,����ӵ�", i);
            const int size = wcslen(text);
            SelectObject(hdc, hFont1);
            DrawTextW(hdc, text, size, &rcDraw, DT_RIGHT | DT_BOTTOM);
        }
        rcDraw.top += itemHeight;
    }

    SelectObject(hdc, hFontOld);
    DeleteObject(hbr);
    DeleteObject(hbr1);
    DeleteObject(hbr2);
    DeleteObject(hFont1);
    DeleteObject(hFont2);
}
void paint_06_draw_line(HDC hdc)
{
    HPEN hPen1 = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    HPEN hPen2 = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
    HPEN hPenOld = (HPEN)GetCurrentObject(hdc, OBJ_PEN);

    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = (rcClient.bottom - rcClient.top) - 50;
    const int count = cyClient / itemHeight;
    int nTop = 40;

    for ( int i = 0; i < count; i++ )
    {
        SelectObject(hdc, (i % 2 == 0) ? hPen1 : hPen2);
        MoveToEx(hdc, 10, nTop, 0);
        LineTo(hdc, cxClient - 50, nTop);
        nTop += itemHeight;
    }

    SelectObject(hdc, hPenOld);
    DeleteObject(hPen1);
    DeleteObject(hPen2);
}

void OnPaint_06_textout(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

    HPEN hPen = CreatePen(PS_DOT, 1, RGB(135, 135, 135));//����ʮ�ֶ�λ����
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);//������ѡ���豸�������������ԭ������

    MoveToEx(hdc, 0, cyClient / 2, NULL);
    LineTo(hdc, cxClient, cyClient / 2);

    MoveToEx(hdc, cxClient / 2, 0, NULL);
    LineTo(hdc, cxClient / 2, cyClient);
    DeleteObject(SelectObject(hdc, hOldPen));


    //HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
    HFONT hFont = OnPaint_06_create_font();
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    const wchar_t text[] = L"�����ı�, �����Ǵ������ĵ�";
    const int size = sizeof(text) / sizeof(text[0]) - 1;

    TEXTMETRICW tm;
    GetTextMetricsW(hdc, &tm);

    SIZE si;
    GetTextExtentPoint32W(hdc, text, size, &si);
    RECT rcCalc = { 0, 0, cxClient, cyClient };
    DrawTextW(hdc, text, size, &rcCalc, DT_CALCRECT);

    //int oldAlign = SetTextAlign(hdc, TA_BOTTOM | TA_CENTER);
    //TextOutW(hdc, cxClient / 2, cyClient / 2, text, size);
    //SetTextAlign(hdc, oldAlign);

    RECT rcText = { 0, 0, cxClient, cyClient };
    DrawTextW(hdc, text, size, &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);


    SelectObject(hdc, hOldFont);

}

HFONT OnPaint_06_create_font(int lfHeight, LPCWSTR name)
{
    // ��������
    LOGFONTW lf = { 0 };
    lf.lfHeight         = lfHeight;                     // �ַ��߶�
    lf.lfWidth          = 0;                            // �ַ����
    lf.lfEscapement     = 0;                            // �Ƕ�
    lf.lfOrientation    = 0;                            // �Ƕ�
    lf.lfWeight         = FW_NORMAL;                    // ����Ȩ��
    lf.lfItalic         = FALSE;                        // б��
    lf.lfUnderline      = FALSE;                        // �»���
    lf.lfStrikeOut      = FALSE;                        // ɾ����
    lf.lfCharSet        = DEFAULT_CHARSET;              // �ַ���
    lf.lfOutPrecision   = OUT_DEFAULT_PRECIS;           // �������
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;          // �ü�����
    lf.lfQuality        = CLEARTYPE_QUALITY;            // �������
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;  // ������
    wcscpy_s(lf.lfFaceName, name);                      // ��������

    if ( 0 )
    {
        return CreateFontIndirectW(&lf);
    }
    else
    {
        return CreateFontW(lf.lfHeight,          // �ַ��߶�
                                  lf.lfWidth,           // �ַ����
                                  lf.lfEscapement,      // �Ƕ�
                                  lf.lfOrientation,     // �Ƕ�
                                  lf.lfWeight,          // ����Ȩ��
                                  lf.lfItalic,          // б��
                                  lf.lfUnderline,       // �»���
                                  lf.lfStrikeOut,       // ɾ����
                                  lf.lfCharSet,         // �ַ���
                                  lf.lfOutPrecision,    // �������
                                  lf.lfClipPrecision,   // �ü�����
                                  lf.lfQuality,         // �������
                                  lf.lfPitchAndFamily,  // ������
                                  lf.lfFaceName);       // ��������
    }
    return 0;
}

void WndProc_06(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch ( message )
    {
    case WM_LBUTTONDOWN:
    {
        if ( m_head_state == STATE::HOVER )
        {
            m_head_state = STATE::DOWN;
            InvalidateRect(hWnd, 0, 0);
            return;
        }

        if ( m_index != 0 )
        {
            m_item_state = STATE::DOWN;
            InvalidateRect(hWnd, 0, 0);
            return;
        }
    }
    case WM_LBUTTONUP:
    {
        if ( m_head_state == STATE::DOWN )
        {
            m_head_state = STATE::HOVER;
            InvalidateRect(hWnd, 0, 0);
            return;
        }

        if ( m_index != 0 && m_item_state == STATE::DOWN )
        {
            m_item_state = STATE::HOVER;
            InvalidateRect(hWnd, 0, 0);
            return;
        }
        break;
    }
    case WM_MOUSEMOVE:
    {
        int x = GET_X_LPARAM(lParam);
        int y = GET_Y_LPARAM(lParam);
        if ( x < 10 || x > cxClient - 50 )
        {
            m_index_old = -1;
            m_index = -1;
            if ( m_head_state != STATE::NORMAL || m_item_state != STATE::NORMAL )
            {
                m_head_state = STATE::NORMAL;
                m_item_state = STATE::NORMAL;
                InvalidateRect(hWnd, 0, 0);
            }
            return;
        }

        if ( y < 40 && y > 10 ) // ��ͷ������
        {
            m_index_old = -1;
            m_index = -1;
            if ( m_head_state != STATE::HOVER )
            {
                m_head_state = STATE::HOVER;
                m_item_state = STATE::NORMAL;
                InvalidateRect(hWnd, 0, 0);
            }
            return;
        }

        m_head_state = STATE::NORMAL;
        y -= 40;
        m_index = y / itemHeight;
        if ( m_index == m_index_old && m_index != -1 )
            return;

        m_index_old = m_index;
        m_item_state = STATE::HOVER;
        InvalidateRect(hWnd, 0, 0);
        break;
    }
    default:
        break;
    }
}