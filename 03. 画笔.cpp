#include "pch.h"
void _test_03(HWND hWnd, HDC hdc);


void OnPaint_03(PWINDOW_DATA pWnd, HDC hdc)
{
    _test_03(pWnd->hWnd, hdc);
    return;
    void GetStaticRect(HWND hParent, RECT & rc1, RECT & rc2);

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);   // �����������


    // rc1 = ��ʾ���ε�λ��
    // rc2 = ��һ������͵ڶ��������λ��
    RECT rc1, rc2;
    GetStaticRect(pWnd->hWnd, rc1, rc2);

    //SetBkMode(hdc, OPAQUE);
    //SetBkColor(hdc, RGB(0, 0, 255));

    // ���ʽ���ģʽ
    // 1 = �ӿ���ȡ����
    // 2 = CreatePen ��������
    // 3 = CreatePenIndirect ��������
    // 4 = ExtCreatePen ��������
#define PEN_MODE 2  

    int penStyle = PS_DOT;  // ������ʽ
    int penWidth = 1;         // ���ʿ��
    COLORREF penClr = RGB(255, 0, 0); // ������ɫ
    bool isFree = true;             // �Ƿ��ͷŻ���
#if PEN_MODE == 1
    // ���ʵ�һ����, ��ȡ��滭��
    HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);
    isFree = false;
#elif PEN_MODE == 2
    // ���ʵڶ�����, ʹ��API��������
    HPEN hPen = CreatePen(penStyle, penWidth, penClr);
#elif PEN_MODE == 3
    // ���ʵ�������, ʹ��API��������2
    LOGPEN logPen = { 0 };
    logPen.lopnStyle = penStyle;
    logPen.lopnWidth.x = penWidth;
    logPen.lopnColor = penClr;
    HPEN hPen = CreatePenIndirect(nullptr);
#elif PEN_MODE == 4
    // ���ʵ��Ĳ���, ʹ��API��������3

    penStyle |= PS_GEOMETRIC;   // ���λ���
    penStyle |= PS_ALTERNATE;
    // ��� dwPenStyle PS_GEOMETRIC�������ʹ�����г�Ա��ָ���ʵĻ�������
    LOGBRUSH logBrush = { 0 };
    logBrush.lbStyle = BS_SOLID;
    logBrush.lbColor = penClr;
    logBrush.lbHatch = 0;

    //penStyle |= PS_COSMETIC;   // ��ױ����

    DWORD clrs[] = { 255 };
    const int count = sizeof(clrs) / sizeof(clrs[0]);
    // ���� PS_USERSTYLE �����ʽ����Ҫ�����Զ��廭����ʽ����
    //HPEN hPen = ExtCreatePen(penStyle, penWidth, &logBrush, count, clrs);
    HPEN hPen = ExtCreatePen(penStyle, penWidth, &logBrush, 0, 0);
#endif

    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);

    MoveToEx(hdc, 50, 50, 0);
    LineTo(hdc, 250, 50);



    //Rectangle     (������)
    //Ellipse       (����Բ)
    //RoundRect     (��Բ�Ǿ���)
    //Arc           (����)
    //Chord         (����)
    //Pie           (����)
    //Ellipse(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);
    //RoundRect(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, 100, 200);
    //Arc(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, rc2.left, rc2.top, rc2.right, rc2.bottom);
    //Chord(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, rc2.left, rc2.top, rc2.right, rc2.bottom);
    Pie(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom, rc2.left, rc2.top, rc2.right, rc2.bottom);

    SelectObject(hdc, hOldPen);
    if (isFree)
        DeleteObject(hPen);
}



void _test_03(HWND hWnd, HDC hdc)
{
    PAINTSTRUCT ps;
    LOGBRUSH lb;
    RECT rc;
    int i;
    HGDIOBJ hPen = NULL;
    HGDIOBJ hPenOld;
    DWORD dwPenStyle[] = {
                           PS_DASH,
                           PS_DASHDOT,
                           PS_DOT,
                           PS_INSIDEFRAME,
                           PS_NULL,
                           PS_SOLID
    };
    UINT uHatch[] = {
                      HS_BDIAGONAL,
                      HS_CROSS,
                      HS_DIAGCROSS,
                      HS_FDIAGONAL,
                      HS_HORIZONTAL,
                      HS_VERTICAL
    };


    GetClientRect(hWnd, &rc);
    rc.left += 10;
    rc.top += 10;
    rc.bottom -= 10;

    // Initialize the pen's brush.
    lb.lbStyle = BS_SOLID;
    lb.lbColor = RGB(255, 0, 0);
    lb.lbHatch = 0;

    for ( i = 0; i < 6; i++ )
    {
        hPen = ExtCreatePen(PS_COSMETIC | dwPenStyle[i],
                            1, &lb, 0, NULL);
        hPenOld = SelectObject(hdc, hPen);
        MoveToEx(hdc, rc.left + (i * 20), rc.top, NULL);
        LineTo(hdc, rc.left + (i * 20), rc.bottom);
        SelectObject(hdc, hPenOld);
        DeleteObject(hPen);
    }
    rc.left += 150;
    for ( i = 0; i < 6; i++ )
    {
        lb.lbStyle = BS_HATCHED;
        lb.lbColor = RGB(0, 0, 255);
        lb.lbHatch = uHatch[i];
        hPen = ExtCreatePen(PS_GEOMETRIC,
                            5, &lb, 0, NULL);
        hPenOld = SelectObject(hdc, hPen);
        MoveToEx(hdc, rc.left + (i * 20), rc.top, NULL);
        LineTo(hdc, rc.left + (i * 20), rc.bottom);
        SelectObject(hdc, hPenOld);
        DeleteObject(hPen);
    }


}