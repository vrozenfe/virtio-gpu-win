#include "stdafx.h"

BOOL WINAPI
DllMain(HINSTANCE hModule, DWORD Reason, LPVOID pReserved)
{
    UNREFERENCED_PARAMETER(pReserved);

    switch (Reason)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        break;
    case DLL_PROCESS_DETACH:
        break;
    default:
        break;
    }

    return TRUE;
}
