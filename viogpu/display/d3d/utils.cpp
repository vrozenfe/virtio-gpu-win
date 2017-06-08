#include "stdafx.h"
#include <stdio.h>

#define DEBUG_BUFSIZE 1024

VOID
DbgLog(CONST TCHAR *pFormat, ...)
{
    TCHAR pBuf[DEBUG_BUFSIZE];
    va_list vArgs;

    va_start(vArgs, pFormat);
    _vstprintf_s(pBuf, _countof(pBuf), pFormat, vArgs);
    va_end(vArgs);

    OutputDebugString(pBuf);
}

