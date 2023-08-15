#pragma once
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

template<typename T> inline void tstr_free(T* p)
{
    if ( p )
        free(p);
}
template<typename T> inline T* tstr_alloc(size_t size)
{
    if ( size == 0 ) size = 1;
    size_t len = size + 1;
    for ( ;;)
    {
        size_t bufSize = len * sizeof(T);
        T* p = (T*)malloc(bufSize);
        if ( p )
        {
            *p = 0;
            return p;
        }
        return 0;
    }
}

// ���·����ڴ�, ���Ѿ�����д���·�����ڴ���, �����·�����ڴ�, �ͷžɵ��ڴ�
template<typename T> inline T* tstr_realloc(T*& p, int size)
{
    tstr_free(p);
    p = tstr_alloc<T>(size);
    return p;
}


namespace tstr_hide
{
    inline int tstr_vsnprintf_s(char* const _Buffer, size_t const _BufferCount, char const* const _Format, va_list _ArgList)
    {
        return _vsnprintf_s(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
    }

    inline int tstr_vsnwprintf_s(wchar_t* const _Buffer, size_t const _BufferCount, wchar_t const* const _Format, va_list _ArgList)
    {
        return _vsnwprintf_s(_Buffer, _BufferCount, _BufferCount - 1, _Format, _ArgList);
    }
    inline int tstr_vsctprintf(char const* const _Format, va_list _ArgList)
    {
        return _vscprintf(_Format, _ArgList);
    }

    inline int tstr_vsctprintf(wchar_t const* const _Format, va_list _ArgList)
    {
        return _vscwprintf(_Format, _ArgList);
    }
    inline int tstr_vstscanf(const char* buffer, const char* _Format, va_list _ArgList)
    {
        return vsscanf_s(buffer, _Format, _ArgList);
    }
    inline int tstr_vstscanf(const wchar_t* buffer, const wchar_t* _Format, va_list _ArgList)
    {
        return vswscanf_s(buffer, _Format, _ArgList);
    }

};


// ��ʽ���ı�
inline static int tstr_vsnprintf(char* const _Buffer, const size_t _bufferSize, const char* const _Format, va_list _ArgList)
{
    return tstr_hide::tstr_vsnprintf_s(_Buffer, _bufferSize, _Format, _ArgList);
}
inline static int tstr_vsnprintf(wchar_t* const _Buffer, const size_t _bufferSize, const wchar_t* const _Format, va_list _ArgList)
{
    return tstr_hide::tstr_vsnwprintf_s(_Buffer, _bufferSize, _Format, _ArgList);
}

// ȡ��ʽ���ı�����
inline static int tstr_vscprintf(const char* const _Format, va_list _ArgList)
{
    return tstr_hide::tstr_vsctprintf(_Format, _ArgList);
}
inline static int tstr_vscprintf(const wchar_t* const _Format, va_list _ArgList)
{
    return tstr_hide::tstr_vsctprintf(_Format, _ArgList);
}

template<typename T>
inline static int tstr_sprintf(T* const _Buffer, const size_t _bufferSize, const T* const _Format, ...)
{
    va_list aptr;
    va_start(aptr, _Format);
    int r = tstr_vsnprintf(_Buffer, _bufferSize, _Format, aptr);
    va_end(aptr);
    return r;
}


// ��ȡ��ʽ���ı�, �����ı���ַ, ���ص��ı���Ҫ���� tstr_free() �ͷ�
// pSize = �����ı�����, _vsnprintf_s �ķ���ֵ
// fmt = ��ʽ���ı�
// list = �����б�
template<typename T> inline T* tstr_GetFormat(int* pSize, const T* fmt, va_list list)
{
    int r = tstr_vscprintf(fmt, list) + 1;
    int bufferSize = r > 1 ? r : 260;
    T* buffer = tstr_alloc<T>(bufferSize);

    r = tstr_vsnprintf(buffer, bufferSize, fmt, list);
    while ( r == -1 )
    {
        bufferSize *= 2;
        buffer = tstr_realloc(buffer, bufferSize);
        r = tstr_vsnprintf(buffer, bufferSize, fmt, list);
    }
    if ( pSize )*pSize = r;
    return buffer;
}

// ��ȡ��ʽ���ı�, �����ı���ַ, ���ص��ı���Ҫ���� tstr_free() �ͷ�
// pSize = �����ı�����, _vsnprintf_s �ķ���ֵ
// fmt = ��ʽ���ı�
// list = �����б�
template<typename T> inline T* tstr_GetFormat(int* pSize, const T* fmt, ...)
{
    va_list list;
    va_start(list, fmt);
    T* ret = tstr_GetFormat(pSize, fmt, list);
    va_end(list);
    return ret;
}
