#include "stdafx.h"
#include <stdio.h>

#define DEBUG_BUFSIZE 1024
#define DEBUG_PREFIX  _TEXT("VIOGPU: ")

VOID
DbgLog(CONST WCHAR *pFormat, ...)
{
    WCHAR pBuf[DEBUG_BUFSIZE];
    va_list vArgs;
    size_t Length;

    Length = wcslen(DEBUG_PREFIX);
    _snwprintf_s(pBuf, Length, DEBUG_PREFIX);

    va_start(vArgs, pFormat);
    _vsnwprintf_s(pBuf + Length, DEBUG_BUFSIZE - (Length - sizeof(WCHAR)), DEBUG_BUFSIZE - sizeof(WCHAR), pFormat, vArgs);
    pBuf[DEBUG_BUFSIZE] = '\0';
    OutputDebugString(pBuf);
}

