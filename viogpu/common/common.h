#pragma once

typedef struct _VIOGPU_PRIVATEDATA {
    ULONG Magic;
    ULONG Version;
    USHORT VendorId;
    USHORT DeviceId;
    GUID AdapterGuid;
} VIOGPU_PRIVATEDATA, *PVIOGPU_PRIVATEDATA;
