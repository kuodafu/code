#include "pch.h"
void _test_03(HWND hWnd, HDC hdc);


void OnPaint_03(PWINDOW_DATA pWnd, HDC hdc)
{
    _test_03(pWnd->hWnd, hdc);
    return;
    void GetStaticRect(HWND hParent, RECT & rc1, RECT & rc2);

    RECT rc;
    GetClientRect(pWnd->hWnd, &rc);
    Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);   // 填充整个窗口


    // rc1 = 显示矩形的位置
    // rc2 = 第一个坐标和第二个坐标的位置
    RECT rc1, rc2;
    GetStaticRect(pWnd->hWnd, rc1, rc2);

    //SetBkMode(hdc, OPAQUE);
    //SetBkColor(hdc, RGB(0, 0, 255));

    // 画笔讲解模式
    // 1 = 从库存获取画笔
    // 2 = CreatePen 创建画笔
    // 3 = CreatePenIndirect 创建画笔
    // 4 = ExtCreatePen 创建画笔
#define PEN_MODE 2  

    int penStyle = PS_DOT;  // 画笔样式
    int penWidth = 1;         // 画笔宽度
    COLORREF penClr = RGB(255, 0, 0); // 画笔颜色
    bool isFree = true;             // 是否释放画笔
#if PEN_MODE == 1
    // 画笔第一部分, 获取库存画笔
    HPEN hPen = (HPEN)GetStockObject(BLACK_PEN);
    isFree = false;
#elif PEN_MODE == 2
    // 画笔第二部分, 使用API创建画笔
    HPEN hPen = CreatePen(penStyle, penWidth, penClr);
#elif PEN_MODE == 3
    // 画笔第三部分, 使用API创建画笔2
    LOGPEN logPen = { 0 };
    logPen.lopnStyle = penStyle;
    logPen.lopnWidth.x = penWidth;
    logPen.lopnColor = penClr;
    HPEN hPen = CreatePenIndirect(nullptr);
#elif PEN_MODE == 4
    // 画笔第四部分, 使用API创建画笔3

    penStyle |= PS_GEOMETRIC;   // 几何画笔
    penStyle |= PS_ALTERNATE;
    // 如果 dwPenStyle PS_GEOMETRIC，则必须使用所有成员来指定笔的画笔属性
    LOGBRUSH logBrush = { 0 };
    logBrush.lbStyle = BS_SOLID;
    logBrush.lbColor = penClr;
    logBrush.lbHatch = 0;

    //penStyle |= PS_COSMETIC;   // 彩妆画笔

    DWORD clrs[] = { 255 };
    const int count = sizeof(clrs) / sizeof(clrs[0]);
    // 存在 PS_USERSTYLE 这个样式就需要传递自定义画笔样式数组
    //HPEN hPen = ExtCreatePen(penStyle, penWidth, &logBrush, count, clrs);
    HPEN hPen = ExtCreatePen(penStyle, penWidth, &logBrush, 0, 0);
#endif

    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    Rectangle(hdc, rc1.left, rc1.top, rc1.right, rc1.bottom);

    MoveToEx(hdc, 50, 50, 0);
    LineTo(hdc, 250, 50);



    //Rectangle     (画矩形)
    //Ellipse       (画椭圆)
    //RoundRect     (画圆角矩形)
    //Arc           (画弧)
    //Chord         (画弦)
    //Pie           (画饼)
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