#pragma once
#include "helper.h"

extern "C"
DRIVER_INITIALIZE DriverEntry;

//
// PnP DDIs
//

VOID
VioGpu3DUnload(VOID);

// If uncommenting ENABLE_DXGK_SAL in the sources file, all the below function prototypes should be updated to use
// the function typedef's from the header files. Additionally, annotations on the function definitions can be removed
// as they are inherited from the prototype definition here. As an example the entire 4-line prototype for BddDdiAddDevice
// is replaced by the single commented line below:
// DXGKDDI_ADD_DEVICE BddDdiAddDevice;
NTSTATUS
VioGpu3DAddDevice(
    _In_ DEVICE_OBJECT* pPhysicalDeviceObject,
    _Outptr_ PVOID*  ppDeviceContext);

NTSTATUS
VioGpu3DRemoveDevice(
    _In_  VOID* pDeviceContext);

NTSTATUS
VioGpu3DStartDevice(
    _In_  VOID*              pDeviceContext,
    _In_  DXGK_START_INFO*   pDxgkStartInfo,
    _In_  DXGKRNL_INTERFACE* pDxgkInterface,
    _Out_ ULONG*             pNumberOfViews,
    _Out_ ULONG*             pNumberOfChildren);

NTSTATUS
VioGpu3DStopDevice(
    _In_  VOID* pDeviceContext);

VOID
VioGpu3DResetDevice(
    _In_  VOID* pDeviceContext);


NTSTATUS
VioGpu3DDispatchIoRequest(
    _In_  VOID*                 pDeviceContext,
    _In_  ULONG                 VidPnSourceId,
    _In_  VIDEO_REQUEST_PACKET* pVideoRequestPacket);

NTSTATUS
VioGpu3DSetPowerState(
    _In_  VOID*              pDeviceContext,
    _In_  ULONG              HardwareUid,
    _In_  DEVICE_POWER_STATE DevicePowerState,
    _In_  POWER_ACTION       ActionType);

NTSTATUS
VioGpu3DQueryChildRelations(
    _In_                             VOID*                  pDeviceContext,
    _Out_writes_bytes_(ChildRelationsSize) DXGK_CHILD_DESCRIPTOR* pChildRelations,
    _In_                             ULONG                  ChildRelationsSize);

NTSTATUS
VioGpu3DQueryChildStatus(
    _In_    VOID*              pDeviceContext,
    _Inout_ DXGK_CHILD_STATUS* pChildStatus,
    _In_    BOOLEAN            NonDestructiveOnly);

NTSTATUS
VioGpu3DQueryDeviceDescriptor(
    _In_  VOID*                     pDeviceContext,
    _In_  ULONG                     ChildUid,
    _Inout_ DXGK_DEVICE_DESCRIPTOR* pDeviceDescriptor);

// Must be Non-Paged
BOOLEAN
VioGpu3DInterruptRoutine(
    _In_  VOID* pDeviceContext,
    _In_  ULONG MessageNumber);

VOID
VioGpu3DDpcRoutine(
    _In_  VOID* pDeviceContext);

//
// WDDM Display Only Driver DDIs
//

// DDI routines
VOID
APIENTRY
VioGpu3DControlEtwLogging(
    _In_ BOOLEAN Enable,
    _In_ ULONG Flags,
    _In_ UCHAR Level);

NTSTATUS
APIENTRY
VioGpu3DQueryAdapterInfo(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_QUERYADAPTERINFO *pQueryAdapterInfo);

NTSTATUS
APIENTRY
VioGpu3DCreateDevice(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_CREATEDEVICE *pCreateDevice);

NTSTATUS
APIENTRY
VioGpu3DCreateAllocation(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_CREATEALLOCATION *pCreateAllocation);

NTSTATUS
APIENTRY
VioGpu3DDestroyAllocation(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_DESTROYALLOCATION *pDestroyAllocation);

NTSTATUS
APIENTRY
VioGpu3DDescribeAllocation(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_DESCRIBEALLOCATION *pDescribeAlloc);

NTSTATUS
APIENTRY
VioGpu3DGetStandardAllocationDriverData(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA *pStandardAllocationDriverData);

NTSTATUS
APIENTRY
VioGpu3DAcquireSwizzlingRange(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_ACQUIRESWIZZLINGRANGE *pAcquireSwizzlingRange);

NTSTATUS
APIENTRY
VioGpu3DReleaseSwizzlingRange(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_RELEASESWIZZLINGRANGE *pReleaseSwizzlingRange);

NTSTATUS
APIENTRY
VioGpu3DPatch(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_PATCH *pPatch);

NTSTATUS
APIENTRY
VioGpu3DSubmitCommand(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_SUBMITCOMMAND *pSubmitCommand);

NTSTATUS
APIENTRY
VioGpu3DPreemptCommand(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_PREEMPTCOMMAND *pPreemptCommand);

NTSTATUS
APIENTRY
VioGpu3DBuildPagingBuffer(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_BUILDPAGINGBUFFER *pBuildPagingBuffer);

NTSTATUS
APIENTRY
VioGpu3DSetPalette(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_SETPALETTE *pSetPalette);

NTSTATUS
APIENTRY
VioGpu3DSetPointerPosition(
    _In_ CONST HANDLE                         hAdapter,
    _In_ CONST DXGKARG_SETPOINTERPOSITION*    pSetPointerPosition);

NTSTATUS
APIENTRY
VioGpu3DSetPointerShape(
    _In_ CONST HANDLE                         hAdapter,
    _In_ CONST DXGKARG_SETPOINTERSHAPE*       pSetPointerShape);

NTSTATUS
APIENTRY
CALLBACK
VioGpu3DResetFromTimeout(
    _In_ CONST HANDLE hAdapter);

NTSTATUS
APIENTRY
CALLBACK
VioGpu3DRestartFromTimeout(
    _In_ CONST HANDLE hAdapter);

NTSTATUS
APIENTRY
VioGpu3DEscape(
    _In_ CONST HANDLE hAdapter, 
    _In_ CONST DXGKARG_ESCAPE *pEscape);

NTSTATUS
APIENTRY
VioGpu3DCollectDbgInfo(
    _In_ HANDLE hAdapter,
    _In_ CONST DXGKARG_COLLECTDBGINFO *pCollectDbgInfo);

NTSTATUS
APIENTRY
VioGpu3DQueryCurrentFence(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_QUERYCURRENTFENCE *pCurrentFence);

NTSTATUS
APIENTRY
VioGpu3DStopCapture(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_STOPCAPTURE *pStopCapture);

NTSTATUS
APIENTRY
VioGpu3DControlInterrupt(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGK_INTERRUPT_TYPE InterruptType,
    _In_ BOOLEAN Enable);

NTSTATUS
APIENTRY
VioGpu3DDestroyDevice(
    _In_ CONST HANDLE hDevice);

NTSTATUS
APIENTRY
VioGpu3DOpenAllocation(
    _In_ CONST HANDLE hDevice,
    _In_ CONST DXGKARG_OPENALLOCATION *pOpenAllocation);

NTSTATUS
APIENTRY
VioGpu3DCloseAllocation(
    _In_ CONST HANDLE hDevice,
    _In_ CONST DXGKARG_CLOSEALLOCATION *pCloseAllocation);

NTSTATUS
APIENTRY
VioGpu3DRender(
    _In_ CONST HANDLE hContext,
    _In_ DXGKARG_RENDER *pRender);

NTSTATUS
APIENTRY
VioGpu3DPresent(
    _In_ CONST HANDLE hContext,
    _In_ DXGKARG_PRESENT *pPresent);

NTSTATUS
APIENTRY
VioGpu3DCreateContext(
    _In_ CONST HANDLE hDevice,
    _In_ DXGKARG_CREATECONTEXT *pCreateContext);

NTSTATUS 
APIENTRY
VioGpu3DDestroyContext(
    _In_ CONST HANDLE hContext);


NTSTATUS
APIENTRY
VioGpu3DQueryAdapterInfo(
    _In_ CONST HANDLE                         hAdapter,
    _In_ CONST DXGKARG_QUERYADAPTERINFO*      pQueryAdapterInfo);

NTSTATUS
VioGpu3DQueryInterface(
    _In_ CONST PVOID                          pDeviceContext,
    _In_ CONST PQUERY_INTERFACE               pQueryInterface);

NTSTATUS
APIENTRY
VioGpu3DIsSupportedVidPn(
    _In_ CONST HANDLE                         hAdapter,
    _Inout_ DXGKARG_ISSUPPORTEDVIDPN*         pIsSupportedVidPn);

NTSTATUS
APIENTRY
VioGpu3DRecommendFunctionalVidPn(
    _In_ CONST HANDLE                                   hAdapter,
    _In_ CONST DXGKARG_RECOMMENDFUNCTIONALVIDPN* CONST  pRecommendFunctionalVidPn);

NTSTATUS
APIENTRY
VioGpu3DRecommendVidPnTopology(
    _In_ CONST HANDLE                                 hAdapter,
    _In_ CONST DXGKARG_RECOMMENDVIDPNTOPOLOGY* CONST  pRecommendVidPnTopology);

NTSTATUS
APIENTRY
VioGpu3DRecommendMonitorModes(
    _In_ CONST HANDLE                                hAdapter,
    _In_ CONST DXGKARG_RECOMMENDMONITORMODES* CONST  pRecommendMonitorModes);

NTSTATUS
APIENTRY
VioGpu3DEnumVidPnCofuncModality(
    _In_ CONST HANDLE                                  hAdapter,
    _In_ CONST DXGKARG_ENUMVIDPNCOFUNCMODALITY* CONST  pEnumCofuncModality);

NTSTATUS
APIENTRY
VioGpu3DSetVidPnSourceVisibility(
    _In_ CONST HANDLE                             hAdapter,
    _In_ CONST DXGKARG_SETVIDPNSOURCEVISIBILITY*  pSetVidPnSourceVisibility);

NTSTATUS
APIENTRY
VioGpu3DCommitVidPn(
    _In_ CONST HANDLE                         hAdapter,
    _In_ CONST DXGKARG_COMMITVIDPN* CONST     pCommitVidPn);

NTSTATUS
APIENTRY
VioGpu3DUpdateActiveVidPnPresentPath(
    _In_ CONST HANDLE                                       hAdapter,
    _In_ CONST DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH* CONST  pUpdateActiveVidPnPresentPath);


// Must be Non-Paged
NTSTATUS
APIENTRY
VioGpu3DSystemDisplayEnable(
    _In_  VOID* pDeviceContext,
    _In_  D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId,
    _In_  PDXGKARG_SYSTEM_DISPLAY_ENABLE_FLAGS Flags,
    _Out_ UINT* Width,
    _Out_ UINT* Height,
    _Out_ D3DDDIFORMAT* ColorFormat);

// Must be Non-Paged
VOID
APIENTRY
VioGpu3DSystemDisplayWrite(
    _In_  VOID* pDeviceContext,
    _In_  VOID* Source,
    _In_  UINT  SourceWidth,
    _In_  UINT  SourceHeight,
    _In_  UINT  SourceStride,
    _In_  UINT  PositionX,
    _In_  UINT  PositionY);

NTSTATUS
APIENTRY
VioGpu3DSetVidPnSourceAddress(
    _In_  CONST HANDLE hAdapter,
    _In_  CONST DXGKARG_SETVIDPNSOURCEADDRESS *pSetVidPnSourceAddress);

NTSTATUS
APIENTRY
VioGpu3DGetScanLine(
    _In_  CONST HANDLE hAdapter,
    _In_  DXGKARG_GETSCANLINE *pGetScanLine);

