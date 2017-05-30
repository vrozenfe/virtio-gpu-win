// viogpud3d.h : main header file for the d3d DLL
//
#pragma once
#include "stdafx.h"
#include "common.h"


VOID TraceLog(CONST WCHAR *pFormat, ...);
VOID DbgLog(CONST WCHAR *pFormat, ...);

#ifndef DBG
#define TraceLog(a) DbgLog a
#else
#define TraceLog(a) do {} while (FALSE)
#endif


typedef struct _VIOGPU_D3D_ADAPTER {
    HANDLE hAdapter;
    UINT Interface;
    UINT Version;
    D3DDDI_ADAPTERCALLBACKS AdapterCallbacks;
    VIOGPU_PRIVATEDATA PrivateData;
} VIOGPU_D3D_ADAPTER, *PVIOGPU_D3D_ADAPTER;

typedef struct _VIOGPU_D3D_DEVICE {
    PVIOGPU_D3D_ADAPTER pVioGpuAdapter;
    HANDLE hDevice;
    UINT Interface;
    UINT Version;
    D3DDDI_DEVICECALLBACKS DeviceCallbacks;
    D3DDDI_CREATEDEVICEFLAGS Flags;
} VIOGPU_D3D_DEVICE, *PVIOGPU_D3D_DEVICE;
