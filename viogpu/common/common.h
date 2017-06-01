#pragma once

#define VIOGPU_D3D_MAGIC        0x476F6956 // 'VioG'
#define VIOGPU_D3D_VERSION      0x1

typedef struct _VIOGPU_PRIVATEDATA {
    ULONG Magic;
    ULONG Version;
    USHORT VendorId;
    USHORT DeviceId;
    GUID AdapterGuid;
} VIOGPU_PRIVATEDATA, *PVIOGPU_PRIVATEDATA;
