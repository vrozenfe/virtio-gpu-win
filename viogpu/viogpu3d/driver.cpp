#include "driver.h"
#include "viogpu3d.h"
#include "helper.h"
#include "baseobj.h"

#pragma code_seg(push)
#pragma code_seg("INIT")

int nDebugLevel;
int virtioDebugLevel;
int bDebugPrint;

tDebugPrintFunc VirtioDebugPrintProc;


void InitializeDebugPrints(IN PDRIVER_OBJECT  DriverObject, IN PUNICODE_STRING RegistryPath)
{
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);
    bDebugPrint = 0;
    virtioDebugLevel = 0;
    nDebugLevel = TRACE_LEVEL_NONE;

#ifdef DBG
    bDebugPrint = 1;
    virtioDebugLevel = 0;// 0xff;
    nDebugLevel = TRACE_LEVEL_VERBOSE;
#if defined(COM_DEBUG)
    VirtioDebugPrintProc = DebugPrintFuncSerial;
#elif defined(PRINT_DEBUG)
    VirtioDebugPrintProc = DebugPrintFuncKdPrint;
#endif
#endif
}


extern "C"
NTSTATUS
DriverEntry(
    _In_  DRIVER_OBJECT*  pDriverObject,
    _In_  UNICODE_STRING* pRegistryPath)
{
    PAGED_CODE();
    NTSTATUS Status = STATUS_SUCCESS;
    InitializeDebugPrints(pDriverObject, pRegistryPath);
    DbgPrint(TRACE_LEVEL_FATAL, ("---> VOIGPU3D build on on %s %s\n", __DATE__, __TIME__));

    if (KD_DEBUGGER_ENABLED == TRUE && KD_DEBUGGER_NOT_PRESENT == FALSE) {
        DbgBreakPoint();
    }
    DRIVER_INITIALIZATION_DATA DriverInitializationData = {0};

    DriverInitializationData.Version                                = DXGKDDI_INTERFACE_VERSION;

    // Miniport
    DriverInitializationData.DxgkDdiAddDevice                       = VioGpu3DAddDevice;
    DriverInitializationData.DxgkDdiStartDevice                     = VioGpu3DStartDevice;
    DriverInitializationData.DxgkDdiStopDevice                      = VioGpu3DStopDevice;
    DriverInitializationData.DxgkDdiRemoveDevice                    = VioGpu3DRemoveDevice;
    DriverInitializationData.DxgkDdiDispatchIoRequest               = VioGpu3DDispatchIoRequest;
    DriverInitializationData.DxgkDdiInterruptRoutine                = VioGpu3DInterruptRoutine;
    DriverInitializationData.DxgkDdiDpcRoutine                      = VioGpu3DDpcRoutine;
    DriverInitializationData.DxgkDdiQueryChildRelations             = VioGpu3DQueryChildRelations;
    DriverInitializationData.DxgkDdiQueryChildStatus                = VioGpu3DQueryChildStatus;
    DriverInitializationData.DxgkDdiQueryDeviceDescriptor           = VioGpu3DQueryDeviceDescriptor;
    DriverInitializationData.DxgkDdiSetPowerState                   = VioGpu3DSetPowerState;
    DriverInitializationData.DxgkDdiNotifyAcpiEvent                 = NULL; // optional, not currently used
    DriverInitializationData.DxgkDdiResetDevice                     = VioGpu3DResetDevice;
    DriverInitializationData.DxgkDdiUnload                          = VioGpu3DUnload;
    DriverInitializationData.DxgkDdiQueryInterface                  = VioGpu3DQueryInterface;
    // DDI
    DriverInitializationData.DxgkDdiControlEtwLogging               = VioGpu3DControlEtwLogging;
    DriverInitializationData.DxgkDdiQueryAdapterInfo                = VioGpu3DQueryAdapterInfo;
    DriverInitializationData.DxgkDdiCreateDevice                    = VioGpu3DCreateDevice;
    DriverInitializationData.DxgkDdiCreateAllocation                = VioGpu3DCreateAllocation;
    DriverInitializationData.DxgkDdiDestroyAllocation               = VioGpu3DDestroyAllocation;
    DriverInitializationData.DxgkDdiDescribeAllocation              = VioGpu3DDescribeAllocation;
    DriverInitializationData.DxgkDdiGetStandardAllocationDriverData = VioGpu3DGetStandardAllocationDriverData;
    DriverInitializationData.DxgkDdiAcquireSwizzlingRange           = VioGpu3DAcquireSwizzlingRange;
    DriverInitializationData.DxgkDdiReleaseSwizzlingRange           = VioGpu3DReleaseSwizzlingRange;
    DriverInitializationData.DxgkDdiPatch                           = VioGpu3DPatch;
    DriverInitializationData.DxgkDdiSubmitCommand                   = VioGpu3DSubmitCommand;
    DriverInitializationData.DxgkDdiPreemptCommand                  = VioGpu3DPreemptCommand;
    DriverInitializationData.DxgkDdiBuildPagingBuffer               = VioGpu3DBuildPagingBuffer;
    DriverInitializationData.DxgkDdiSetPalette                      = VioGpu3DSetPalette;
    DriverInitializationData.DxgkDdiSetPointerPosition              = VioGpu3DSetPointerPosition;
    DriverInitializationData.DxgkDdiSetPointerShape                 = VioGpu3DSetPointerShape;
    DriverInitializationData.DxgkDdiResetFromTimeout                = VioGpu3DResetFromTimeout;
    DriverInitializationData.DxgkDdiRestartFromTimeout              = VioGpu3DRestartFromTimeout;
    DriverInitializationData.DxgkDdiEscape                          = VioGpu3DEscape;
    DriverInitializationData.DxgkDdiCollectDbgInfo                  = VioGpu3DCollectDbgInfo;
    DriverInitializationData.DxgkDdiQueryCurrentFence               = VioGpu3DQueryCurrentFence;
    // VidPn
    DriverInitializationData.DxgkDdiIsSupportedVidPn                = VioGpu3DIsSupportedVidPn;
    DriverInitializationData.DxgkDdiRecommendFunctionalVidPn        = VioGpu3DRecommendFunctionalVidPn;
    DriverInitializationData.DxgkDdiEnumVidPnCofuncModality         = VioGpu3DEnumVidPnCofuncModality;
    DriverInitializationData.DxgkDdiSetVidPnSourceAddress           = VioGpu3DSetVidPnSourceAddress;
    DriverInitializationData.DxgkDdiSetVidPnSourceVisibility        = VioGpu3DSetVidPnSourceVisibility;
    DriverInitializationData.DxgkDdiCommitVidPn                     = VioGpu3DCommitVidPn;
    DriverInitializationData.DxgkDdiUpdateActiveVidPnPresentPath    = VioGpu3DUpdateActiveVidPnPresentPath;
    DriverInitializationData.DxgkDdiRecommendMonitorModes           = VioGpu3DRecommendMonitorModes;
    DriverInitializationData.DxgkDdiRecommendVidPnTopology          = VioGpu3DRecommendVidPnTopology;
    DriverInitializationData.DxgkDdiGetScanLine                     = VioGpu3DGetScanLine;
    // DDI
    DriverInitializationData.DxgkDdiStopCapture                     = VioGpu3DStopCapture;
    DriverInitializationData.DxgkDdiControlInterrupt                = VioGpu3DControlInterrupt;
    DriverInitializationData.DxgkDdiCreateOverlay                   = NULL; // not supported
    DriverInitializationData.DxgkDdiDestroyDevice                   = VioGpu3DDestroyDevice;
    DriverInitializationData.DxgkDdiOpenAllocation                  = VioGpu3DOpenAllocation;
    DriverInitializationData.DxgkDdiCloseAllocation                 = VioGpu3DCloseAllocation;
    DriverInitializationData.DxgkDdiRender                          = VioGpu3DRender;
    DriverInitializationData.DxgkDdiPresent                         = VioGpu3DPresent;
    DriverInitializationData.DxgkDdiUpdateOverlay                   = NULL; // not supported
    DriverInitializationData.DxgkDdiFlipOverlay                     = NULL; // not supported
    DriverInitializationData.DxgkDdiDestroyOverlay                  = NULL; // not supported
    DriverInitializationData.DxgkDdiCreateContext                   = VioGpu3DCreateContext;
    DriverInitializationData.DxgkDdiDestroyContext                  = VioGpu3DDestroyContext;
    DriverInitializationData.DxgkDdiLinkDevice                      = NULL; // not supported
    DriverInitializationData.DxgkDdiSetDisplayPrivateDriverFormat   = NULL; // not supported


    Status = DxgkInitialize(pDriverObject, pRegistryPath, &DriverInitializationData);

    if (!NT_SUCCESS(Status))
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("DxgkInitialize failed with Status: 0x%X\n", Status));
    }

    DbgPrint(TRACE_LEVEL_VERBOSE, ("<--- %s\n", __FUNCTION__));
    return Status;
}
// END: Init Code
#pragma code_seg(pop)

#pragma code_seg(push)
#pragma code_seg("PAGE")

//
// PnP DDIs
//

VOID
VioGpu3DUnload(VOID)
{
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--> %s\n", __FUNCTION__));
}

NTSTATUS
VioGpu3DAddDevice(
    _In_ DEVICE_OBJECT* pPhysicalDeviceObject,
    _Outptr_ PVOID*  ppDeviceContext)
{
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));

    if ((pPhysicalDeviceObject == NULL) ||
        (ppDeviceContext == NULL))
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("One of pPhysicalDeviceObject (0x%I64x), ppDeviceContext (0x%I64x) is NULL",
                        pPhysicalDeviceObject, ppDeviceContext));
        return STATUS_INVALID_PARAMETER;
    }
    *ppDeviceContext = NULL;

    VioGpu3D* pVioGpu3D = new(NonPagedPoolNx) VioGpu3D(pPhysicalDeviceObject);
    if (pVioGpu3D == NULL)
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("pVioGpu3D failed to be allocated"));
        return STATUS_NO_MEMORY;
    }

    *ppDeviceContext = pVioGpu3D;

    DbgPrint(TRACE_LEVEL_VERBOSE, ("<--- %s ppDeviceContext = %p\n", __FUNCTION__, pVioGpu3D));
    return STATUS_SUCCESS;
}

NTSTATUS
VioGpu3DRemoveDevice(
    _In_  VOID* pDeviceContext)
{
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_INFORMATION, ("---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);

    if (pVioGpu3D)
    {
        delete pVioGpu3D;
        pVioGpu3D = NULL;
    }

    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s\n", __FUNCTION__));
    return STATUS_SUCCESS;
}

NTSTATUS
VioGpu3DStartDevice(
    _In_  VOID*              pDeviceContext,
    _In_  DXGK_START_INFO*   pDxgkStartInfo,
    _In_  DXGKRNL_INTERFACE* pDxgkInterface,
    _Out_ ULONG*             pNumberOfViews,
    _Out_ ULONG*             pNumberOfChildren)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    Status = pVioGpu3D->StartDevice(pDxgkStartInfo, pDxgkInterface, pNumberOfViews, pNumberOfChildren);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
VioGpu3DStopDevice(
    _In_  VOID* pDeviceContext)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    Status = pVioGpu3D->StopDevice();
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
VioGpu3DDispatchIoRequest(
    _In_  VOID*                 pDeviceContext,
    _In_  ULONG                 VidPnSourceId,
    _In_  VIDEO_REQUEST_PACKET* pVideoRequestPacket)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->DispatchIoRequest(VidPnSourceId, pVideoRequestPacket);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
VioGpu3DSetPowerState(
    _In_  VOID*              pDeviceContext,
    _In_  ULONG              HardwareUid,
    _In_  DEVICE_POWER_STATE DevicePowerState,
    _In_  POWER_ACTION       ActionType)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    if (!pVioGpu3D->IsDriverActive())
    {
        return STATUS_SUCCESS;
    }
    Status = pVioGpu3D->SetPowerState(HardwareUid, DevicePowerState, ActionType);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
VioGpu3DQueryChildRelations(
    _In_  VOID*              pDeviceContext,
    _Out_writes_bytes_(ChildRelationsSize) DXGK_CHILD_DESCRIPTOR* pChildRelations,
    _In_  ULONG              ChildRelationsSize)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    Status = pVioGpu3D->QueryChildRelations(pChildRelations, ChildRelationsSize);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
VioGpu3DQueryChildStatus(
    _In_    VOID*            pDeviceContext,
    _Inout_ DXGK_CHILD_STATUS* pChildStatus,
    _In_    BOOLEAN          NonDestructiveOnly)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    Status = pVioGpu3D->QueryChildStatus(pChildStatus, NonDestructiveOnly);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
VioGpu3DQueryDeviceDescriptor(
    _In_  VOID*                     pDeviceContext,
    _In_  ULONG                     ChildUid,
    _Inout_ DXGK_DEVICE_DESCRIPTOR* pDeviceDescriptor)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_WARNING, ("VIOGPU (%p) is being called when not active!", pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->QueryDeviceDescriptor(ChildUid, pDeviceDescriptor);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


//
// WDDM Display Only Driver DDIs
//

NTSTATUS
APIENTRY
VioGpu3DQueryAdapterInfo(
    _In_ CONST HANDLE                    hAdapter,
    _In_ CONST DXGKARG_QUERYADAPTERINFO* pQueryAdapterInfo)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    Status = pVioGpu3D->QueryAdapterInfo(pQueryAdapterInfo);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DSetPointerPosition(
    _In_ CONST HANDLE                      hAdapter,
    _In_ CONST DXGKARG_SETPOINTERPOSITION* pSetPointerPosition)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu (%p) is being called when not active!", pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->SetPointerPosition(pSetPointerPosition);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DSetPointerShape(
    _In_ CONST HANDLE                   hAdapter,
    _In_ CONST DXGKARG_SETPOINTERSHAPE* pSetPointerShape)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("<---> %s VioGpu (%p) is being called when not active!\n", __FUNCTION__, pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->SetPointerShape(pSetPointerShape);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
VioGpu3DQueryInterface(
    _In_ CONST PVOID          pDeviceContext,
    _In_ CONST PQUERY_INTERFACE     QueryInterface
    )
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    Status = pVioGpu3D->QueryInterface(QueryInterface);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DIsSupportedVidPn(
    _In_ CONST HANDLE                 hAdapter,
    _Inout_ DXGKARG_ISSUPPORTEDVIDPN* pIsSupportedVidPn)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_WARNING, ("VIOGPU (%p) is being called when not active!", pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->IsSupportedVidPn(pIsSupportedVidPn);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DRecommendFunctionalVidPn(
    _In_ CONST HANDLE                                  hAdapter,
    _In_ CONST DXGKARG_RECOMMENDFUNCTIONALVIDPN* CONST pRecommendFunctionalVidPn)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->RecommendFunctionalVidPn(pRecommendFunctionalVidPn);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DRecommendVidPnTopology(
    _In_ CONST HANDLE                                 hAdapter,
    _In_ CONST DXGKARG_RECOMMENDVIDPNTOPOLOGY* CONST  pRecommendVidPnTopology)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->RecommendVidPnTopology(pRecommendVidPnTopology);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DRecommendMonitorModes(
    _In_ CONST HANDLE                                hAdapter,
    _In_ CONST DXGKARG_RECOMMENDMONITORMODES* CONST  pRecommendMonitorModes)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->RecommendMonitorModes(pRecommendMonitorModes);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DEnumVidPnCofuncModality(
    _In_ CONST HANDLE                                 hAdapter,
    _In_ CONST DXGKARG_ENUMVIDPNCOFUNCMODALITY* CONST pEnumCofuncModality)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->EnumVidPnCofuncModality(pEnumCofuncModality);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DSetVidPnSourceVisibility(
    _In_ CONST HANDLE                            hAdapter,
    _In_ CONST DXGKARG_SETVIDPNSOURCEVISIBILITY* pSetVidPnSourceVisibility)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->SetVidPnSourceVisibility(pSetVidPnSourceVisibility);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DCommitVidPn(
    _In_ CONST HANDLE                     hAdapter,
    _In_ CONST DXGKARG_COMMITVIDPN* CONST pCommitVidPn)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->CommitVidPn(pCommitVidPn);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DUpdateActiveVidPnPresentPath(
    _In_ CONST HANDLE                                      hAdapter,
    _In_ CONST DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH* CONST pUpdateActiveVidPnPresentPath)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }
    Status = pVioGpu3D->UpdateActiveVidPnPresentPath(pUpdateActiveVidPnPresentPath);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


VOID 
APIENTRY
VioGpu3DControlEtwLogging(
    _In_  BOOLEAN Enable,
    _In_  ULONG Flags,
    _In_  UCHAR Level)
{
    UNREFERENCED_PARAMETER(Enable);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(Level);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));
}

NTSTATUS
APIENTRY
VioGpu3DCreateDevice(
    _In_ CONST HANDLE hAdapter,
    _Inout_ DXGKARG_CREATEDEVICE *pCreateDevice)
{
    UNREFERENCED_PARAMETER(pCreateDevice);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));

    pCreateDevice->hDevice = new (NonPagedPoolNx) VioGpuDevice(hAdapter, pCreateDevice);
    if (!pCreateDevice->hDevice)
    {
        DbgPrint(TRACE_LEVEL_FATAL, ("<--> %s VioGpu3D Failed allocate memory for device!\n", __FUNCTION__));
        return STATUS_NO_MEMORY;
    }

    DbgPrint(TRACE_LEVEL_VERBOSE, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, STATUS_SUCCESS));
    return STATUS_SUCCESS;
}


NTSTATUS
APIENTRY
VioGpu3DCreateAllocation(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_CREATEALLOCATION *pCreateAllocation)
{
    UNREFERENCED_PARAMETER(pCreateAllocation);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = pVioGpu3D->CreateAllocation(pCreateAllocation);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DDestroyAllocation(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_DESTROYALLOCATION *pDestroyAllocation)
{
    UNREFERENCED_PARAMETER(pDestroyAllocation);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = Status = pVioGpu3D->DestroyAllocation(pDestroyAllocation);

    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DDescribeAllocation(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_DESCRIBEALLOCATION *pDescribeAlloc)
{
    UNREFERENCED_PARAMETER(pDescribeAlloc);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DGetStandardAllocationDriverData(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_GETSTANDARDALLOCATIONDRIVERDATA *pStandardAllocationDriverData)
{
    UNREFERENCED_PARAMETER(pStandardAllocationDriverData);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DAcquireSwizzlingRange(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_ACQUIRESWIZZLINGRANGE *pAcquireSwizzlingRange)
{
    UNREFERENCED_PARAMETER(pAcquireSwizzlingRange);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DReleaseSwizzlingRange(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_RELEASESWIZZLINGRANGE *pReleaseSwizzlingRange)
{
    UNREFERENCED_PARAMETER(pReleaseSwizzlingRange);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DPatch(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_PATCH *pPatch)
{
    UNREFERENCED_PARAMETER(pPatch);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DSubmitCommand(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_SUBMITCOMMAND *pSubmitCommand)
{
    UNREFERENCED_PARAMETER(pSubmitCommand);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DPreemptCommand(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_PREEMPTCOMMAND *pPreemptCommand)
{
    UNREFERENCED_PARAMETER(pPreemptCommand);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DBuildPagingBuffer(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_BUILDPAGINGBUFFER *pBuildPagingBuffer)
{
    UNREFERENCED_PARAMETER(pBuildPagingBuffer);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DSetPalette(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_SETPALETTE *pSetPalette)
{
    UNREFERENCED_PARAMETER(pSetPalette);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
CALLBACK
VioGpu3DResetFromTimeout(
    _In_ CONST HANDLE hAdapter)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
CALLBACK
VioGpu3DRestartFromTimeout(
    _In_ CONST HANDLE hAdapter)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DEscape(
    _In_ CONST HANDLE hAdapter, 
    _In_ CONST DXGKARG_ESCAPE *pEscape)
{
    UNREFERENCED_PARAMETER(pEscape);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DCollectDbgInfo(
    _In_ HANDLE hAdapter,
    _In_ CONST DXGKARG_COLLECTDBGINFO *pCollectDbgInfo)
{
    UNREFERENCED_PARAMETER(pCollectDbgInfo);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DQueryCurrentFence(
    _In_ CONST HANDLE hAdapter,
    _In_ DXGKARG_QUERYCURRENTFENCE *pCurrentFence)
{
    UNREFERENCED_PARAMETER(pCurrentFence);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DStopCapture(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGKARG_STOPCAPTURE *pStopCapture)
{
    UNREFERENCED_PARAMETER(pStopCapture);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DControlInterrupt(
    _In_ CONST HANDLE hAdapter,
    _In_ CONST DXGK_INTERRUPT_TYPE InterruptType,
    _In_ BOOLEAN Enable)
{
    UNREFERENCED_PARAMETER(InterruptType);
    UNREFERENCED_PARAMETER(Enable);
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;


    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DDestroyDevice(
    _In_ CONST HANDLE hDevice)
{
    UNREFERENCED_PARAMETER(hDevice);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));

    VioGpuDevice* pDevice = (VioGpuDevice*)hDevice;

    delete pDevice;

    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, STATUS_SUCCESS));
    return STATUS_SUCCESS;
}

NTSTATUS
APIENTRY
VioGpu3DOpenAllocation(
    _In_ CONST HANDLE hDevice,
    _In_ CONST DXGKARG_OPENALLOCATION *pOpenAllocation)
{
    UNREFERENCED_PARAMETER(pOpenAllocation);
    UNREFERENCED_PARAMETER(hDevice);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;


    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DCloseAllocation(
    _In_ CONST HANDLE hDevice,
    _In_ CONST DXGKARG_CLOSEALLOCATION *pCloseAllocation)
{
    UNREFERENCED_PARAMETER(pCloseAllocation);
    UNREFERENCED_PARAMETER(hDevice);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;


    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DRender(
    _In_ CONST HANDLE hContext,
    _In_ DXGKARG_RENDER *pRender)
{
    UNREFERENCED_PARAMETER(pRender);
    UNREFERENCED_PARAMETER(hContext);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;


    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DPresent(
    _In_ CONST HANDLE hContext,
    _In_ DXGKARG_PRESENT *pPresent)
{
    UNREFERENCED_PARAMETER(pPresent);
    UNREFERENCED_PARAMETER(hContext);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;


    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DCreateContext(
    _In_ CONST HANDLE hDevice,
    _In_ DXGKARG_CREATECONTEXT *pCreateContext)
{
    UNREFERENCED_PARAMETER(pCreateContext);
    UNREFERENCED_PARAMETER(hDevice);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;


    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS 
APIENTRY
VioGpu3DDestroyContext(
    _In_ CONST HANDLE hContext)
{
    UNREFERENCED_PARAMETER(hContext);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;


    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}


NTSTATUS
APIENTRY
VioGpu3DSetVidPnSourceAddress(
    _In_  CONST HANDLE hAdapter,
    _In_  CONST DXGKARG_SETVIDPNSOURCEADDRESS *pSetVidPnSourceAddress)
{
    UNREFERENCED_PARAMETER(pSetVidPnSourceAddress);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

NTSTATUS
APIENTRY
VioGpu3DGetScanLine(
    _In_  CONST HANDLE hAdapter,
    _In_  DXGKARG_GETSCANLINE *pGetScanLine)
{
    UNREFERENCED_PARAMETER(pGetScanLine);
    PAGED_CODE();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu3D (0x%I64x) is being called when not active (%s)!", pVioGpu3D, __FUNCTION__));
        return STATUS_UNSUCCESSFUL;
    }

    Status = STATUS_NOT_IMPLEMENTED;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}



//END: Paged Code
#pragma code_seg(pop)

#pragma code_seg(push)
#pragma code_seg()
// BEGIN: Non-Paged Code

VOID
VioGpu3DDpcRoutine(
    _In_  VOID* pDeviceContext)
{
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    if (!pVioGpu3D->IsHardwareInit())
    {
        DbgPrint(TRACE_LEVEL_FATAL, ("VioGpu (%p) is being called when not active!", pVioGpu3D));
        return;
    }
    pVioGpu3D->DpcRoutine();
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<--- %s\n", __FUNCTION__));
}

BOOLEAN
VioGpu3DInterruptRoutine(
    _In_  VOID* pDeviceContext,
    _In_  ULONG MessageNumber)
{
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
        return pVioGpu3D->InterruptRoutine(MessageNumber);
}

VOID
VioGpu3DResetDevice(
    _In_  VOID* pDeviceContext)
{
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    pVioGpu3D->ResetDevice();
}

NTSTATUS
APIENTRY
VioGpu3DSystemDisplayEnable(
    _In_  VOID* pDeviceContext,
    _In_  D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId,
    _In_  PDXGKARG_SYSTEM_DISPLAY_ENABLE_FLAGS Flags,
    _Out_ UINT* Width,
    _Out_ UINT* Height,
    _Out_ D3DDDIFORMAT* ColorFormat)
{
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("---> %s\n", __FUNCTION__));
    NTSTATUS Status = STATUS_SUCCESS;

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);

    Status = pVioGpu3D->SystemDisplayEnable(TargetId, Flags, Width, Height, ColorFormat);;
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<--- %s returned with status 0x%08X\n", __FUNCTION__, Status));
    return Status;
}

VOID
APIENTRY
VioGpu3DSystemDisplayWrite(
    _In_  VOID* pDeviceContext,
    _In_  VOID* Source,
    _In_  UINT  SourceWidth,
    _In_  UINT  SourceHeight,
    _In_  UINT  SourceStride,
    _In_  UINT  PositionX,
    _In_  UINT  PositionY)
{
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    pVioGpu3D->SystemDisplayWrite(Source, SourceWidth, SourceHeight, SourceStride, PositionX, PositionY);
}

#if defined(DBG)

#if defined(COM_DEBUG)

#define RHEL_DEBUG_PORT     ((PUCHAR)0x3F8)
#define TEMP_BUFFER_SIZE	256

void DebugPrintFuncSerial(const char *format, ...)
{
    char buf[TEMP_BUFFER_SIZE];
    NTSTATUS status;
    size_t len;
    va_list list;
    va_start(list, format);
    status = RtlStringCbVPrintfA(buf, sizeof(buf), format, list);
    if (status == STATUS_SUCCESS)
    {
        len = strlen(buf);
    }
    else
    {
        len = 2;
        buf[0] = 'O';
        buf[1] = '\n';
    }
    if (len)
    {
        WRITE_PORT_BUFFER_UCHAR(RHEL_DEBUG_PORT, (PUCHAR)buf, (ULONG)len);
        WRITE_PORT_UCHAR(RHEL_DEBUG_PORT, '\r');
    }
}
#endif

#if defined(PRINT_DEBUG)
void DebugPrintFuncKdPrint(const char *format, ...)
{
    va_list list;
    va_start(list, format);
    vDbgPrintEx(DPFLTR_DEFAULT_ID, 9 | DPFLTR_MASK, format, list);
}
#endif

#endif

#pragma code_seg(pop) // End Non-Paged Code

