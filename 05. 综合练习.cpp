#include "pch.h"
void OnPaint_05_line1(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_line2(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_line3(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_black_dot(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_iphone5(PWINDOW_DATA pWnd, HDC hdc);
void OnPaint_05_ddm(HWND hwnd, HDC hdc);
void OnPaint_05(PWINDOW_DATA pWnd, HDC hdc)
{
    OnPaint_05_line1(pWnd, hdc);
    //OnPaint_05_line2(pWnd, hdc);
    //OnPaint_05_line3(pWnd, hdc);
    //OnPaint_05_black_dot(pWnd, hdc);
    //OnPaint_05_iphone5(pWnd, hdc);
    //OnPaint_05_ddm(pWnd->hWnd, hdc);
}

// �Ƚ�����ֱ�ߵĳ���
void OnPaint_05_line1(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
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
// �Ƚ�����ֱ�ߵĳ���2
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
// �Ƚ�����ֱ�ߵĳ���3, ƽ����
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
// ���ڵ�, ��һ���м����ڵ�
void OnPaint_05_black_dot(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(BLACK_BRUSH));

    HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));
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

    SelectObject(hdc, GetStockObject(WHITE_BRUSH));
    SelectObject(hdc, GetStockObject(NULL_PEN));

    for ( int i = 0; i < count1; i++ )
    {
        for ( int j = 0; j < count2; j++ )
        {
            const int x = 20 + i * 50;
            const int y = 20 + j * 50;
            const int bj = 7;
            Ellipse(hdc, x - bj, y - bj, x + bj, y + bj);
        }
    }

    SelectObject(hdc, hPenOld);
    SelectObject(hdc, hBrushOld);
    DeleteObject(hPen);

}
// ��ƻ��5
void OnPaint_05_iphone5(PWINDOW_DATA pWnd, HDC hdc)
{
    RECT rcClient;
    GetClientRect(pWnd->hWnd, &rcClient);
    const int cxClient = rcClient.right - rcClient.left;
    const int cyClient = rcClient.bottom - rcClient.top;
    FillRect(hdc, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

    HPEN hPen = CreatePen(PS_DOT, 0, RGB(128, 128, 128));
    HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

    // ----------��������
    MoveToEx (hdc, cxClient / 2, 0, 0);
    LineTo (hdc, cxClient / 2, cyClient);

    MoveToEx (hdc, 0, cyClient / 2, 0);
    LineTo (hdc, cxClient, cyClient / 2);

    SelectObject (hdc, hPenOld);
    DeleteObject (hPen);

    // -----------�����
    RoundRect (hdc, cxClient / 2 - 110, 50, cxClient / 2 + 110, cyClient - 50, 50, 50);
    RoundRect (hdc, cxClient / 2 - 110 + 3, 50 + 3, cxClient / 2 + 110 - 3, cyClient - 50 - 3, 50 - 2, 50 - 2);

    // -------------����Դ��
    RoundRect (hdc, cxClient / 2 + 110 - 30 - 30, 49, cxClient / 2 + 110 - 30, 50, 1, 1);

    // ��������
    RoundRect (hdc, cxClient / 2 - 110 - 1, 110, cxClient / 2 - 110, 135, 0, 3);
    RoundRect (hdc, cxClient / 2 - 110 - 1, 155, cxClient / 2 - 110, 170, 0, 3);

    RoundRect (hdc, cxClient / 2 - 110 - 1, 185, cxClient / 2 - 110, 200, 0, 3);


    // ---------��ǰ������ͷ
    HGDIOBJ hBrushOld = SelectObject (hdc, GetStockObject (BLACK_BRUSH));
    Ellipse (hdc, cxClient / 2 - 5, 65, cxClient / 2 + 5, 75);
    SelectObject (hdc, hBrushOld);

    Ellipse (hdc, cxClient / 2 - 25 - 8, 83, cxClient / 2 - 25, 91);
    RoundRect (hdc, cxClient / 2 - 20, 85, cxClient / 2 + 20, 90, 2, 2);

    // --------����Ļ;
    int nHeight = 110;
    Rectangle (hdc, cxClient / 2 - 100, 110, cxClient / 2 + 100, cyClient - nHeight);
    MoveToEx (hdc, cxClient / 2 - 100, 110, 0);
    LineTo (hdc, cxClient / 2 + 100, cyClient - nHeight);

    // ---------��home��;
    Ellipse (hdc, cxClient / 2 - 20, cyClient - 110 + 10, cxClient / 2 + 20, cyClient - 110 + 10 + 40);
    hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    hPenOld = (HPEN)SelectObject (hdc, hPen);
    Rectangle (hdc, cxClient / 2 - 10, cyClient - 110 + 20, cxClient / 2 + 10, cyClient - 110 + 20 + 20);
    SelectObject (hdc, hPenOld);
    DeleteObject (hPen);

    // -----------��4���߿���;
    Rectangle (hdc, cxClient / 2 - 107, 80, cxClient / 2 - 110, 82);
    Rectangle (hdc, cxClient / 2 + 107, 80, cxClient / 2 + 110, 82);
    Rectangle (hdc, cxClient / 2 - 107, cyClient - 85, cxClient / 2 - 110, cyClient - 85 + 2);
    Rectangle (hdc, cxClient / 2 + 107, cyClient - 85, cxClient / 2 + 110, cyClient - 85 + 2);


}
// ������è
void OnPaint_05_ddm(HWND hwnd, HDC hdc)
{
    RECT rect;
    HPEN hBlackPen = 0, hOldPen, hWhite2Pen = 0;
    HBRUSH hOldBrush = 0, hRedBrush = 0, hYellowBrush = 0;
    HBRUSH blue_brush = 0, green_brush = 0;
    HPEN blue_pen = 0, green_pen = 0;
    POINT pxRightHand[4], pxiLeftHand[4];

    int GetListIndex();
    const int index = GetListIndex();

    green_brush = CreateSolidBrush(RGB(0, 255, 127));//��ɫ��ˢ

    blue_pen = CreatePen(PS_SOLID, 3, RGB(0, 159, 232));//��ɫ����
    green_pen = CreatePen(PS_SOLID, 3, RGB(0, 255, 127));//��ɫ����

    GetClientRect(hwnd, &rect);//��ȡ�ͻ�����
    rect.right -= 100;  // ��ȥ�б��Ŀ��
    const int cxClient = rect.right - rect.left;
    const int cyClient = rect.bottom - rect.top;
    FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

    // ����ʮ�ֶ�λ��
    if ( index > 0 )
    {
        HPEN hPen = CreatePen(PS_DOT, 1, RGB(135, 135, 135));//����ʮ�ֶ�λ����
        hOldPen = (HPEN)SelectObject(hdc, hPen);//������ѡ���豸�������������ԭ������

        MoveToEx(hdc, 0, rect.bottom / 2, NULL);//
        LineTo(hdc, rect.right, rect.bottom / 2);

        MoveToEx(hdc, rect.right / 2, 0, NULL);
        LineTo(hdc, rect.right / 2, rect.bottom);
        DeleteObject(SelectObject(hdc, hOldPen));
    }




    //����ͷ�� ֱ��240
    if ( index > 1 )
    {
        hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));//������ɫ����
        SelectObject(hdc, hBlackPen);

        blue_brush = CreateSolidBrush(RGB(0, 159, 232));    //��ɫ��ˢ
        hOldBrush = (HBRUSH)SelectObject(hdc, blue_brush);
        Ellipse(hdc, rect.right / 2 - 120, rect.bottom / 2 - 200, rect.right / 2 + 120, rect.bottom / 2 + 40);
        SelectObject(hdc, hOldBrush);
    }

    //������(ֱ��200)
    if ( index > 2 )
    {
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 100, rect.bottom / 2 - 160, rect.right / 2 + 100, rect.bottom / 2 + 40);
    }

    //�����۾�(�۰� ��60,��50)
    if ( index > 3 )
    {
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 50, rect.bottom / 2 - 190, rect.right / 2, rect.bottom / 2 - 130);
        Ellipse(hdc, rect.right / 2, rect.bottom / 2 - 190, rect.right / 2 + 50, rect.bottom / 2 - 130);

        //����ͫ��( ������4 ��16,��30)
        SelectObject(hdc, GetStockObject(BLACK_BRUSH));
        Ellipse(hdc, rect.right / 2 - 20, rect.bottom / 2 - 170, rect.right / 2 - 4, rect.bottom / 2 - 140);
        Ellipse(hdc, rect.right / 2 + 4, rect.bottom / 2 - 170, rect.right / 2 + 20, rect.bottom / 2 - 140);

        //����ͫ�����İ׵�
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 15, rect.bottom / 2 - 160, rect.right / 2 - 8, rect.bottom / 2 - 150);
        Ellipse(hdc, rect.right / 2 + 8, rect.bottom / 2 - 160, rect.right / 2 + 15, rect.bottom / 2 - 150);

    }

    if ( index > 4 )
    {
        //���Ʊ���(ֱ��20)
        hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hRedBrush);
        Ellipse(hdc, rect.right / 2 - 10, rect.bottom / 2 - 143, rect.right / 2 + 10, rect.bottom / 2 - 123);

        //���Ʊ��ӵ����м���(��85)
        MoveToEx(hdc, rect.right / 2, rect.bottom / 2 - 123, NULL);
        LineTo(hdc, rect.right / 2, rect.bottom / 2 - 38);

    }

    //�������
    if ( index > 5 )
    {
        Arc(hdc, rect.right / 2 - 60, rect.bottom / 2 - 98, rect.right / 2 + 60, rect.bottom / 2 - 38,
            rect.right / 2 - 50, rect.bottom / 2 - 58, rect.right / 2 + 50, rect.bottom / 2 - 58);
    }

    //���ƺ���
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
        //��������(������ ��150,��180)
        SelectObject(hdc, blue_brush);
        Rectangle(hdc, rect.right / 2 - 90, rect.bottom / 2, rect.right / 2 + 90, rect.bottom / 2 + 150);
    }

    if ( index > 8 )
    {
        //���ƶ���(Բ�� ֱ��140)
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Ellipse(hdc, rect.right / 2 - 70, rect.bottom / 2 - 20, rect.right / 2 + 70, rect.bottom / 2 + 120);//���ư�ɫ����

        hWhite2Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));//����һ������Ϊ2�İ�ɫʵ�߻���
        SelectObject(hdc, hWhite2Pen);
        Arc(hdc, cxClient / 2 - 70, cyClient / 2 - 20, cxClient / 2 + 70, cyClient / 2 + 120,
            rect.right / 2 + 60, rect.bottom / 2 - 10, rect.right / 2 - 60, rect.bottom / 2 - 10);//���Ǻ�ɫ����
    }

    if ( index > 9 )
    {
        //������Ȧ
        SelectObject(hdc, hRedBrush);
        SelectObject(hdc, hBlackPen);
        RoundRect(hdc, rect.right / 2 - 95, rect.bottom / 2 - 5, rect.right / 2 + 95, rect.bottom / 2 + 10, 20, 20);
    }

    if ( index > 10 )
    {
        //��������
        hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
        SelectObject(hdc, hYellowBrush);
        Ellipse(hdc, rect.right / 2 - 15, rect.bottom / 2, rect.right / 2 + 15, rect.bottom / 2 + 30);
        MoveToEx(hdc, rect.right / 2 - 13, rect.bottom / 2 + 13, NULL);//�����������
        LineTo(hdc, rect.right / 2 + 13, rect.bottom / 2 + 13);

        MoveToEx(hdc, rect.right / 2 - 13, rect.bottom / 2 + 17, NULL);
        LineTo(hdc, rect.right / 2 + 13, rect.bottom / 2 + 17);

        SelectObject(hdc, hRedBrush);
        Ellipse(hdc, rect.right / 2 - 4, rect.bottom / 2 + 19, rect.right / 2 + 4, rect.bottom / 2 + 27);//����������Ȧ

        MoveToEx(hdc, rect.right / 2, rect.bottom / 2 + 27, NULL);
        LineTo(hdc, rect.right / 2, rect.bottom / 2 + 30);//����������Ȧ�º���
    }

    if ( index > 11 )
    {
        //�ٱ���(ֱ��100)
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        Chord(hdc, rect.right / 2 - 50, rect.bottom / 2 - 20, rect.right / 2 + 50, rect.bottom / 2 + 100,
              rect.right / 2 - 50, rect.bottom / 2 + 50, rect.right / 2 + 50, rect.bottom / 2 + 50);
        //Pie(hdc, cxClient / 2 - 50, cyClient / 2, cxClient / 2 + 50, cyClient / 2 + 100,
        //    cxClient / 2 - 50, cyClient / 2 + 50, cxClient / 2 + 50, cyClient / 2 + 50);
    }

    if ( index > 12 )
    {
        //�����ȼ�հ�
        Chord(hdc, rect.right / 2 - 20, rect.bottom / 2 + 130, rect.right / 2 + 20, rect.bottom / 2 + 170,
              rect.right / 2 + 20, rect.bottom / 2 + 150, rect.right / 2 - 20, rect.bottom / 2 + 150);//����
        
        //Pie(hdc, rect.right / 2 - 20, rect.bottom / 2 + 130, rect.right / 2 + 20, rect.bottom / 2 + 170,
        //      rect.right / 2 + 20, rect.bottom / 2 + 150, rect.right / 2 - 20, rect.bottom / 2 + 150);//����

        SelectObject(hdc, hWhite2Pen);
        MoveToEx(hdc, rect.right / 2 - 20, rect.bottom / 2 + 150, NULL);
        LineTo(hdc, rect.right / 2 + 20, rect.bottom / 2 + 150);//�����ȼ����

        //���ƽ���
        SelectObject(hdc, GetStockObject(BLACK_PEN));
        Ellipse(hdc, rect.right / 2 - 110, rect.bottom / 2 + 130, rect.right / 2 - 10, rect.bottom / 2 + 170);//�����ҽ���
        Ellipse(hdc, rect.right / 2 + 110, rect.bottom / 2 + 130, rect.right / 2 + 10, rect.bottom / 2 + 170);//���������
    }

    //������
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
        Ellipse(hdc, rect.right / 2 - 150, rect.bottom / 2 + 46, rect.right / 2 - 110, rect.bottom / 2 + 86);//����������
    }

    //������
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
        Ellipse(hdc, rect.right / 2 + 150, rect.bottom / 2 + 46, rect.right / 2 + 110, rect.bottom / 2 + 86);//����������
    }

    //�����ֱ����������Ӻ���
    if ( index > 15 )
    {
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
    DeleteObject(green_brush);
    DeleteObject(blue_pen);
    DeleteObject(green_pen);
}
