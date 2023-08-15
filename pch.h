#pragma once
#include "framework.h"
#include "resource.h"
#include "tstr.h"

extern HINSTANCE g_hInst;                                // 当前实例

typedef struct WINDOW_DATA
{
    HWND hWnd;

}*PWINDOW_DATA;

inline void output(LPCSTR fmt, ...)
{
    int retSize = 0;
    va_list list;
    va_start(list, fmt);
    char* ret = tstr_GetFormat(&retSize, fmt, list);
    va_end(list);

    OutputDebugStringA(ret);
    tstr_free(ret);
    return;
}
inline void output(LPCWSTR fmt, ...)
{
    int retSize = 0;
    va_list list;
    va_start(list, fmt);
    wchar_t* ret = tstr_GetFormat(&retSize, fmt, list);
    va_end(list);

    OutputDebugStringW(ret);
    tstr_free(ret);
    return;
}