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
    virtioDebugLevel = 0;//0xff;
    nDebugLevel = TRACE_LEVEL_ERROR;
    VirtioDebugPrintProc = DebugPrintFuncSerial;
#endif
}


extern "C"
NTSTATUS
DriverEntry(
    _In_  DRIVER_OBJECT*  pDriverObject,
    _In_  UNICODE_STRING* pRegistryPath)
{
    PAGED_CODE();

    InitializeDebugPrints(pDriverObject, pRegistryPath);
    DbgPrint(TRACE_LEVEL_FATAL, ("---> VOIGPU3D build on on %s %s\n", __DATE__, __TIME__));

    // Initialize DDI function pointers and dxgkrnl
    KMDDOD_INITIALIZATION_DATA InitialData = {0};

    InitialData.Version = DXGKDDI_INTERFACE_VERSION;

    InitialData.DxgkDdiAddDevice                    = VioGpu3DAddDevice;
    InitialData.DxgkDdiStartDevice                  = VioGpu3DStartDevice;
    InitialData.DxgkDdiStopDevice                   = VioGpu3DStopDevice;
    InitialData.DxgkDdiResetDevice                  = VioGpu3DResetDevice;
    InitialData.DxgkDdiRemoveDevice                 = VioGpu3DRemoveDevice;
    InitialData.DxgkDdiDispatchIoRequest            = VioGpu3DDispatchIoRequest;
    InitialData.DxgkDdiInterruptRoutine             = VioGpu3DInterruptRoutine;
    InitialData.DxgkDdiDpcRoutine                   = VioGpu3DDpcRoutine;
    InitialData.DxgkDdiQueryChildRelations          = VioGpu3DQueryChildRelations;
    InitialData.DxgkDdiQueryChildStatus             = VioGpu3DQueryChildStatus;
    InitialData.DxgkDdiQueryDeviceDescriptor        = VioGpu3DQueryDeviceDescriptor;
    InitialData.DxgkDdiSetPowerState                = VioGpu3DSetPowerState;
    InitialData.DxgkDdiUnload                       = VioGpu3DUnload;
    InitialData.DxgkDdiQueryInterface               = VioGpu3DQueryInterface;
    InitialData.DxgkDdiQueryAdapterInfo             = VioGpu3DQueryAdapterInfo;
    InitialData.DxgkDdiSetPointerPosition           = VioGpu3DSetPointerPosition;
    InitialData.DxgkDdiSetPointerShape              = VioGpu3DSetPointerShape;
    InitialData.DxgkDdiIsSupportedVidPn             = VioGpu3DIsSupportedVidPn;
    InitialData.DxgkDdiRecommendFunctionalVidPn     = VioGpu3DRecommendFunctionalVidPn;
    InitialData.DxgkDdiEnumVidPnCofuncModality      = VioGpu3DEnumVidPnCofuncModality;
    InitialData.DxgkDdiSetVidPnSourceVisibility     = VioGpu3DSetVidPnSourceVisibility;
    InitialData.DxgkDdiCommitVidPn                  = VioGpu3DCommitVidPn;
    InitialData.DxgkDdiUpdateActiveVidPnPresentPath = VioGpu3DUpdateActiveVidPnPresentPath;
    InitialData.DxgkDdiRecommendMonitorModes        = VioGpu3DRecommendMonitorModes;
    InitialData.DxgkDdiQueryVidPnHWCapability       = VioGpu3DQueryVidPnHWCapability;
    InitialData.DxgkDdiPresentDisplayOnly           = VioGpu3DPresentDisplayOnly;
    InitialData.DxgkDdiStopDeviceAndReleasePostDisplayOwnership = VioGpu3DStopDeviceAndReleasePostDisplayOwnership;
    InitialData.DxgkDdiSystemDisplayEnable          = VioGpu3DSystemDisplayEnable;
    InitialData.DxgkDdiSystemDisplayWrite           = VioGpu3DSystemDisplayWrite;

    NTSTATUS Status = DxgkInitializeDisplayOnlyDriver(pDriverObject, pRegistryPath, &InitialData);
    if (!NT_SUCCESS(Status))
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("DxgkInitializeDisplayOnlyDriver failed with Status: 0x%X\n", Status));
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

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    return pVioGpu3D->StartDevice(pDxgkStartInfo, pDxgkInterface, pNumberOfViews, pNumberOfChildren);
}

NTSTATUS
VioGpu3DStopDevice(
    _In_  VOID* pDeviceContext)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    return pVioGpu3D->StopDevice();
}


NTSTATUS
VioGpu3DDispatchIoRequest(
    _In_  VOID*                 pDeviceContext,
    _In_  ULONG                 VidPnSourceId,
    _In_  VIDEO_REQUEST_PACKET* pVideoRequestPacket)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VioGpu3D (0x%I64x) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->DispatchIoRequest(VidPnSourceId, pVideoRequestPacket);
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
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    if (!pVioGpu3D->IsDriverActive())
    {
        return STATUS_SUCCESS;
    }
    return pVioGpu3D->SetPowerState(HardwareUid, DevicePowerState, ActionType);
}

NTSTATUS
VioGpu3DQueryChildRelations(
    _In_  VOID*              pDeviceContext,
    _Out_writes_bytes_(ChildRelationsSize) DXGK_CHILD_DESCRIPTOR* pChildRelations,
    _In_  ULONG              ChildRelationsSize)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    return pVioGpu3D->QueryChildRelations(pChildRelations, ChildRelationsSize);
}

NTSTATUS
VioGpu3DQueryChildStatus(
    _In_    VOID*            pDeviceContext,
    _Inout_ DXGK_CHILD_STATUS* pChildStatus,
    _In_    BOOLEAN          NonDestructiveOnly)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    return pVioGpu3D->QueryChildStatus(pChildStatus, NonDestructiveOnly);
}

NTSTATUS
VioGpu3DQueryDeviceDescriptor(
    _In_  VOID*                     pDeviceContext,
    _In_  ULONG                     ChildUid,
    _Inout_ DXGK_DEVICE_DESCRIPTOR* pDeviceDescriptor)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_WARNING, ("VIOGPU (%p) is being called when not active!", pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->QueryDeviceDescriptor(ChildUid, pDeviceDescriptor);
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
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    return pVioGpu3D->QueryAdapterInfo(pQueryAdapterInfo);
}

NTSTATUS
APIENTRY
VioGpu3DSetPointerPosition(
    _In_ CONST HANDLE                      hAdapter,
    _In_ CONST DXGKARG_SETPOINTERPOSITION* pSetPointerPosition)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("VioGpu (%p) is being called when not active!", pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->SetPointerPosition(pSetPointerPosition);
}

NTSTATUS
APIENTRY
VioGpu3DSetPointerShape(
    _In_ CONST HANDLE                   hAdapter,
    _In_ CONST DXGKARG_SETPOINTERSHAPE* pSetPointerShape)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_ERROR, ("<---> %s VioGpu (%p) is being called when not active!\n", __FUNCTION__, pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->SetPointerShape(pSetPointerShape);
}

NTSTATUS
VioGpu3DQueryInterface(
    _In_ CONST PVOID          pDeviceContext,
    _In_ CONST PQUERY_INTERFACE     QueryInterface
    )
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    return pVioGpu3D->QueryInterface(QueryInterface);
}

NTSTATUS
APIENTRY
VioGpu3DPresentDisplayOnly(
    _In_ CONST HANDLE                       hAdapter,
    _In_ CONST DXGKARG_PRESENT_DISPLAYONLY* pPresentDisplayOnly)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->PresentDisplayOnly(pPresentDisplayOnly);
}

NTSTATUS
APIENTRY
VioGpu3DStopDeviceAndReleasePostDisplayOwnership(
    _In_  VOID*                          pDeviceContext,
    _In_  D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId,
    _Out_ DXGK_DISPLAY_INFORMATION*      DisplayInfo)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(pDeviceContext != NULL);
    DbgPrint(TRACE_LEVEL_INFORMATION, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    return pVioGpu3D->StopDeviceAndReleasePostDisplayOwnership(TargetId, DisplayInfo);
}

NTSTATUS
APIENTRY
VioGpu3DIsSupportedVidPn(
    _In_ CONST HANDLE                 hAdapter,
    _Inout_ DXGKARG_ISSUPPORTEDVIDPN* pIsSupportedVidPn)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        DbgPrint(TRACE_LEVEL_WARNING, ("VIOGPU (%p) is being called when not active!", pVioGpu3D));
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->IsSupportedVidPn(pIsSupportedVidPn);
}

NTSTATUS
APIENTRY
VioGpu3DRecommendFunctionalVidPn(
    _In_ CONST HANDLE                                  hAdapter,
    _In_ CONST DXGKARG_RECOMMENDFUNCTIONALVIDPN* CONST pRecommendFunctionalVidPn)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->RecommendFunctionalVidPn(pRecommendFunctionalVidPn);
}

NTSTATUS
APIENTRY
VioGpu3DRecommendVidPnTopology(
    _In_ CONST HANDLE                                 hAdapter,
    _In_ CONST DXGKARG_RECOMMENDVIDPNTOPOLOGY* CONST  pRecommendVidPnTopology)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->RecommendVidPnTopology(pRecommendVidPnTopology);
}

NTSTATUS
APIENTRY
VioGpu3DRecommendMonitorModes(
    _In_ CONST HANDLE                                hAdapter,
    _In_ CONST DXGKARG_RECOMMENDMONITORMODES* CONST  pRecommendMonitorModes)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->RecommendMonitorModes(pRecommendMonitorModes);
}

NTSTATUS
APIENTRY
VioGpu3DEnumVidPnCofuncModality(
    _In_ CONST HANDLE                                 hAdapter,
    _In_ CONST DXGKARG_ENUMVIDPNCOFUNCMODALITY* CONST pEnumCofuncModality)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->EnumVidPnCofuncModality(pEnumCofuncModality);
}

NTSTATUS
APIENTRY
VioGpu3DSetVidPnSourceVisibility(
    _In_ CONST HANDLE                            hAdapter,
    _In_ CONST DXGKARG_SETVIDPNSOURCEVISIBILITY* pSetVidPnSourceVisibility)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->SetVidPnSourceVisibility(pSetVidPnSourceVisibility);
}

NTSTATUS
APIENTRY
VioGpu3DCommitVidPn(
    _In_ CONST HANDLE                     hAdapter,
    _In_ CONST DXGKARG_COMMITVIDPN* CONST pCommitVidPn)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->CommitVidPn(pCommitVidPn);
}

NTSTATUS
APIENTRY
VioGpu3DUpdateActiveVidPnPresentPath(
    _In_ CONST HANDLE                                      hAdapter,
    _In_ CONST DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH* CONST pUpdateActiveVidPnPresentPath)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->UpdateActiveVidPnPresentPath(pUpdateActiveVidPnPresentPath);
}

NTSTATUS
APIENTRY
VioGpu3DQueryVidPnHWCapability(
    _In_ CONST HANDLE                       hAdapter,
    _Inout_ DXGKARG_QUERYVIDPNHWCAPABILITY* pVidPnHWCaps)
{
    PAGED_CODE();
    VIOGPU_ASSERT_CHK(hAdapter != NULL);
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(hAdapter);
    if (!pVioGpu3D->IsDriverActive())
    {
        VIOGPU_LOG_ASSERTION1("VIOGPU (%p) is being called when not active!", pVioGpu3D);
        return STATUS_UNSUCCESSFUL;
    }
    return pVioGpu3D->QueryVidPnHWCapability(pVidPnHWCaps);
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
    DbgPrint(TRACE_LEVEL_VERBOSE, ("<---> %s\n", __FUNCTION__));

    VioGpu3D* pVioGpu3D = reinterpret_cast<VioGpu3D*>(pDeviceContext);
    return pVioGpu3D->SystemDisplayEnable(TargetId, Flags, Width, Height, ColorFormat);
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

void DebugPrintFunc(const char *format, ...)
{
    va_list list;
    va_start(list, format);
    vDbgPrintEx(DPFLTR_DEFAULT_ID, 9 | DPFLTR_MASK, format, list);
}
#endif

#pragma code_seg(pop) // End Non-Paged Code

