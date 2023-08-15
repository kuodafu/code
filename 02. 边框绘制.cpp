#include "pch.h"

void OnPaint_02(PWINDOW_DATA pWnd, HDC hdc)
{
    void GetStaticRect(HWND hParent, RECT & rc1, RECT & rc2);

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);   // �����������


    // rc1 = ��ʾ���ε�λ��
    // rc2 = ��һ������͵ڶ��������λ��
    RECT rc1, rc2;
    GetStaticRect(pWnd->hWnd, rc1, rc2);

    Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);


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


}

