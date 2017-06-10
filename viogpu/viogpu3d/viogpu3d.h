#pragma once

#include "helper.h"


#pragma pack(push)
#pragma pack(1)

typedef struct
{
    UINT DriverStarted : 1; // ( 1) 1 after StartDevice and 0 after StopDevice
    UINT HardwareInit : 1; // ( 1) 1 after StartDevice and 0 after StopDevice
    UINT Unused : 30;
} DRIVER_STATUS_FLAG;


#pragma pack(pop)

// Represents the current mode, may not always be set (i.e. frame buffer mapped) if representing the mode passed in on single mode setups.
typedef struct _CURRENT_BDD_MODE
{
    // The source mode currently set for HW Framebuffer
    // For sample driver this info filled in StartDevice by the OS and never changed.
    DXGK_DISPLAY_INFORMATION             DispInfo;

    // The rotation of the current mode. Rotation is performed in software during Present call
    D3DKMDT_VIDPN_PRESENT_PATH_ROTATION  Rotation;

    D3DKMDT_VIDPN_PRESENT_PATH_SCALING Scaling;
    // This mode might be different from one which are supported for HW frame buffer
    // Scaling/displasment might be needed (if supported)
    UINT SrcModeWidth;
    UINT SrcModeHeight;

    // Various boolean flags the struct uses
    struct _CURRENT_BDD_MODE_FLAGS
    {
        UINT SourceNotVisible     : 1; // 0 if source is visible
        UINT FullscreenPresent    : 1; // 0 if should use dirty rects for present
        UINT FrameBufferIsActive  : 1; // 0 if not currently active (i.e. target not connected to source)
        UINT DoNotMapOrUnmap      : 1; // 1 if the FrameBuffer should not be (un)mapped during normal execution
        UINT IsInternal           : 1; // 1 if it was determined (i.e. through ACPI) that an internal panel is being driven
        UINT Unused               : 27;
    } Flags;

    // The start and end of physical memory known to be all zeroes. Used to optimize the BlackOutScreen function to not write
    // zeroes to memory already known to be zero. (Physical address is located in DispInfo)
    PHYSICAL_ADDRESS ZeroedOutStart;
    PHYSICAL_ADDRESS ZeroedOutEnd;

    union
    {
        VOID*                            Ptr;
        ULONG64                          Force8Bytes;
    } FrameBuffer;
} CURRENT_BDD_MODE;

class VioGpu3D;
class VioGpuAdapter;

class VioGpuDevice
{
public:

    VioGpuDevice(_In_ HANDLE hAdapter, _Inout_ DXGKARG_CREATEDEVICE* pCreateDevice);
    ~VioGpuDevice();

    NTSTATUS CloseAllocation(
            _In_ HANDLE                     hDevice,
            _In_ DXGKARG_CLOSEALLOCATION*   pCloseAlloc);
    NTSTATUS OpenAllocation (_In_ DXGKARG_OPENALLOCATION* pOpenAlloc);

private:
    DXGK_CREATEDEVICEFLAGS  m_Flags;
    HANDLE                  m_hDevice;
    VioGpuAdapter*          m_pAdapter;
};


class VioGpuAdapter
{
public:
    VioGpuAdapter(_In_ VioGpu3D* pVioGpu3D);
    ~VioGpuAdapter(void);
    NTSTATUS SetCurrentMode(ULONG Mode, CURRENT_BDD_MODE* pCurrentBddMode);
    ULONG GetModeCount(void) {return m_ModeCount;}
    NTSTATUS SetPowerState(DEVICE_POWER_STATE DevicePowerState, DXGK_DISPLAY_INFORMATION* pDispInfo);
    NTSTATUS HWInit(PCM_RESOURCE_LIST pResList, DXGK_DISPLAY_INFORMATION* pDispInfo);
    NTSTATUS HWClose(void);
    BOOLEAN EnablePointer(void) { return TRUE; }
    NTSTATUS ExecutePresentDisplayOnly(_In_ BYTE*       DstAddr,
                                 _In_ UINT              DstBitPerPixel,
                                 _In_ BYTE*             SrcAddr,
                                 _In_ UINT              SrcBytesPerPixel,
                                 _In_ LONG              SrcPitch,
                                 _In_ ULONG             NumMoves,
                                 _In_ D3DKMT_MOVE_RECT* pMoves,
                                 _In_ ULONG             NumDirtyRects,
                                 _In_ RECT*             pDirtyRect,
                                 _In_ D3DKMDT_VIDPN_PRESENT_PATH_ROTATION Rotation,
                                 _In_ const CURRENT_BDD_MODE* pModeCur);
    VOID BlackOutScreen(CURRENT_BDD_MODE* pCurrentBddMod);
    BOOLEAN InterruptRoutine(_In_ PDXGKRNL_INTERFACE pDxgkInterface, _In_  ULONG MessageNumber);
    VOID DpcRoutine(_In_ PDXGKRNL_INTERFACE pDxgkInterface);
    VOID ResetDevice(VOID);
    NTSTATUS SetPointerShape(_In_ CONST DXGKARG_SETPOINTERSHAPE* pSetPointerShape, _In_ CONST CURRENT_BDD_MODE* pModeCur);
    NTSTATUS SetPointerPosition(_In_ CONST DXGKARG_SETPOINTERPOSITION* pSetPointerPosition, _In_ CONST CURRENT_BDD_MODE* pModeCur);
    VOID FillPrivateData(_Out_ PVOID pData);
    CPciResources* GetPciResources(void) { return &m_PciResources; }
    NTSTATUS AcquireFrameBuffer(CURRENT_BDD_MODE* pCurrentBddMode) { UNREFERENCED_PARAMETER(pCurrentBddMode);  return STATUS_SUCCESS; }
    NTSTATUS ReleaseFrameBuffer(CURRENT_BDD_MODE* pCurrentBddMode) { UNREFERENCED_PARAMETER(pCurrentBddMode);  return STATUS_SUCCESS; }
    PVIDEO_MODE_INFORMATION GetModeInfo(UINT idx) {return &m_ModeInfo[idx];}
    USHORT GetModeNumber(USHORT idx) {return m_ModeNumbers[idx];}
    USHORT GetCurrentModeIndex(void) {return m_CurrentMode;}
    VOID SetCurrentModeIndex(USHORT idx) {m_CurrentMode = idx;}
    ULONG GetId(void) { return m_Id; }
    VioGpu3D* GetVioGpu(void) {return m_pVioGpu3D;}
    VOID QuerySegment(_Out_ DXGK_QUERYSEGMENTOUT* pQuerySegmentOut);
    UINT GetVSyncFreq() { return 60; }
protected:
private:
    NTSTATUS VioGpuAdapterInit(DXGK_DISPLAY_INFORMATION* pDispInfo);
    void SetVideoModeInfo(UINT Idx, PGPU_DISP_MODE pModeInfo);
    void VioGpuAdapterClose(void);
    NTSTATUS GetModeList(DXGK_DISPLAY_INFORMATION* pDispInfo);
    BOOLEAN AckFeature(UINT64 Feature);
    BOOLEAN GetDisplayInfo(void);
    NTSTATUS UpdateChildStatus(BOOLEAN connect);
    void SetCustomDisplay(_In_ USHORT xres,
                              _In_ USHORT yres);
    void CreateFrameBufferObj(PVIDEO_MODE_INFORMATION pModeInfo, CURRENT_BDD_MODE* pCurrentBddMode);
    void DestroyFrameBufferObj(void);
    BOOLEAN CreateCursorObj(_In_ CONST DXGKARG_SETPOINTERSHAPE* pSetPointerShape, _In_ CONST CURRENT_BDD_MODE* pCurrentBddMode);
    void DestroyCursorObj(void);
    BOOLEAN GpuObjectAttach(UINT res_id, VioGpuObj* obj);
    void static ThreadWork(_In_ PVOID Context);
    void ThreadWorkRoutine(void);
    void ConfigChanged(void);
    NTSTATUS VirtIoDeviceInit(void);
private:
    VirtIODevice m_VioDev;
    CPciResources m_PciResources;
    UINT64 m_u64HostFeatures;
    UINT64 m_u64GuestFeatures;
    UINT32 m_u32NumCapsets;
    UINT32 m_u32NumScanouts;
    CtrlQueue m_CtrlQueue;
    CrsrQueue m_CursorQueue;
    VioGpuBuf m_GpuBuf;
    VioGpuIdr m_Idr;
    VioGpuObj* m_pFrameObj;
    VioGpuObj* m_pCursorObj;
    VioGpuMemSegment m_CursorSegment;
    VioGpuMemSegment m_FrameSegment;
    volatile ULONG m_PendingWorks;
    KEVENT m_ConfigUpdateEvent;
    PETHREAD m_pWorkThread;
    BOOLEAN m_bStopWorkThread;
    VioGpu3D* m_pVioGpu3D;
    PVIDEO_MODE_INFORMATION m_ModeInfo;
    ULONG m_ModeCount;
    PUSHORT m_ModeNumbers;
    USHORT m_CurrentMode;
    USHORT m_CustomMode;
    ULONG  m_Id;
    VIOGPU_PRIVATEDATA m_PrivateData;
};

class VioGpu3D {
private:
    DEVICE_OBJECT* m_pPhysicalDevice;
    DXGKRNL_INTERFACE m_DxgkInterface;
    DXGK_DEVICE_INFO m_DeviceInfo;

    DEVICE_POWER_STATE m_MonitorPowerState;
    DEVICE_POWER_STATE m_AdapterPowerState;
    DRIVER_STATUS_FLAG m_Flags;

    CURRENT_BDD_MODE m_CurrentModes[MAX_VIEWS];

    D3DDDI_VIDEO_PRESENT_SOURCE_ID m_SystemDisplaySourceId;
    DXGKARG_SETPOINTERSHAPE m_PointerShape;
    VioGpuAdapter* m_pAdapter;
public:
    VioGpu3D(_In_ DEVICE_OBJECT* pPhysicalDeviceObject);
    ~VioGpu3D(void);
#pragma code_seg(push)
#pragma code_seg()
    BOOLEAN IsDriverActive() const
    {
        return m_Flags.DriverStarted;
    }
    BOOLEAN IsHardwareInit() const
    {
        return m_Flags.HardwareInit;
    }
    void SetHardwareInit(BOOLEAN init)
    {
        m_Flags.HardwareInit = init;
    }
#pragma code_seg(pop)

    NTSTATUS StartDevice(_In_  DXGK_START_INFO*   pDxgkStartInfo,
                         _In_  DXGKRNL_INTERFACE* pDxgkInterface,
                         _Out_ ULONG*             pNumberOfViews,
                         _Out_ ULONG*             pNumberOfChildren);
    NTSTATUS StopDevice(VOID);
    // Must be Non-Paged
    VOID ResetDevice(VOID);

    NTSTATUS DispatchIoRequest(_In_  ULONG VidPnSourceId,
                               _In_  VIDEO_REQUEST_PACKET* pVideoRequestPacket);
    NTSTATUS SetPowerState(_In_  ULONG HardwareUid,
                               _In_  DEVICE_POWER_STATE DevicePowerState,
                               _In_  POWER_ACTION       ActionType);
    // Report back child capabilities
    NTSTATUS QueryChildRelations(_Out_writes_bytes_(ChildRelationsSize) DXGK_CHILD_DESCRIPTOR* pChildRelations,
                                 _In_                             ULONG                  ChildRelationsSize);

    NTSTATUS QueryChildStatus(_Inout_ DXGK_CHILD_STATUS* pChildStatus,
                              _In_    BOOLEAN            NonDestructiveOnly);

    // Return EDID if previously retrieved
    NTSTATUS QueryDeviceDescriptor(_In_    ULONG                   ChildUid,
                                   _Inout_ DXGK_DEVICE_DESCRIPTOR* pDeviceDescriptor);

    // Must be Non-Paged
    // BDD doesn't have interrupts, so just returns false
    BOOLEAN InterruptRoutine(_In_  ULONG MessageNumber);

    VOID DpcRoutine(VOID);

    // Return DriverCaps, doesn't support other queries though
    NTSTATUS QueryAdapterInfo(_In_ CONST DXGKARG_QUERYADAPTERINFO* pQueryAdapterInfo);

    NTSTATUS SetPointerPosition(_In_ CONST DXGKARG_SETPOINTERPOSITION* pSetPointerPosition);

    NTSTATUS SetPointerShape(_In_ CONST DXGKARG_SETPOINTERSHAPE* pSetPointerShape);

    NTSTATUS PresentDisplayOnly(_In_ CONST DXGKARG_PRESENT_DISPLAYONLY* pPresentDisplayOnly);

    NTSTATUS QueryInterface(_In_ CONST PQUERY_INTERFACE     QueryInterface);

    NTSTATUS IsSupportedVidPn(_Inout_ DXGKARG_ISSUPPORTEDVIDPN* pIsSupportedVidPn);

    NTSTATUS RecommendFunctionalVidPn(_In_ CONST DXGKARG_RECOMMENDFUNCTIONALVIDPN* CONST pRecommendFunctionalVidPn);

    NTSTATUS RecommendVidPnTopology(_In_ CONST DXGKARG_RECOMMENDVIDPNTOPOLOGY* CONST pRecommendVidPnTopology);

    NTSTATUS RecommendMonitorModes(_In_ CONST DXGKARG_RECOMMENDMONITORMODES* CONST pRecommendMonitorModes);

    NTSTATUS EnumVidPnCofuncModality(_In_ CONST DXGKARG_ENUMVIDPNCOFUNCMODALITY* CONST pEnumCofuncModality);

    NTSTATUS SetVidPnSourceVisibility(_In_ CONST DXGKARG_SETVIDPNSOURCEVISIBILITY* pSetVidPnSourceVisibility);

    NTSTATUS CommitVidPn(_In_ CONST DXGKARG_COMMITVIDPN* CONST pCommitVidPn);

    NTSTATUS UpdateActiveVidPnPresentPath(_In_ CONST DXGKARG_UPDATEACTIVEVIDPNPRESENTPATH* CONST pUpdateActiveVidPnPresentPath);

    NTSTATUS QueryVidPnHWCapability(_Inout_ DXGKARG_QUERYVIDPNHWCAPABILITY* pVidPnHWCaps);

    // Part of PnPStop (PnP instance only), returns current mode information (which will be passed to fallback instance by dxgkrnl)
    NTSTATUS StopDeviceAndReleasePostDisplayOwnership(_In_  D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId,
                                                      _Out_ DXGK_DISPLAY_INFORMATION*      pDisplayInfo);

    NTSTATUS DestroyAllocation(_In_ CONST DXGKARG_DESTROYALLOCATION *pDestroyAllocation);

    NTSTATUS CreateAllocation(_In_ DXGKARG_CREATEALLOCATION *pCreateAllocation);


    // Must be Non-Paged
    // Call to initialize as part of bugcheck
    NTSTATUS SystemDisplayEnable(_In_  D3DDDI_VIDEO_PRESENT_TARGET_ID       TargetId,
                                 _In_  PDXGKARG_SYSTEM_DISPLAY_ENABLE_FLAGS Flags,
                                 _Out_ UINT*                                pWidth,
                                 _Out_ UINT*                                pHeight,
                                 _Out_ D3DDDIFORMAT*                        pColorFormat);

    // Must be Non-Paged
    // Write out pixels as part of bugcheck
    VOID SystemDisplayWrite(_In_reads_bytes_(SourceHeight * SourceStride) VOID* pSource,
                                 _In_                                     UINT  SourceWidth,
                                 _In_                                     UINT  SourceHeight,
                                 _In_                                     UINT  SourceStride,
                                 _In_                                     INT   PositionX,
                                 _In_                                     INT   PositionY);
    PDXGKRNL_INTERFACE GetDxgkInterface(void) { return &m_DxgkInterface;}
private:
    VOID CleanUp(VOID);
    BOOLEAN CheckHardware();
    NTSTATUS WriteHWInfoStr(_In_ HANDLE DevInstRegKeyHandle, _In_ PCWSTR pszwValueName, _In_ PCSTR pszValue);
    // Set the given source mode on the given path
    NTSTATUS SetSourceModeAndPath(CONST D3DKMDT_VIDPN_SOURCE_MODE* pSourceMode,
                                  CONST D3DKMDT_VIDPN_PRESENT_PATH* pPath);

    // Add the current mode to the given monitor source mode set
    NTSTATUS AddSingleMonitorMode(_In_ CONST DXGKARG_RECOMMENDMONITORMODES* CONST pRecommendMonitorModes);

    // Add the current mode to the given VidPn source mode set
    NTSTATUS AddSingleSourceMode(_In_ CONST DXGK_VIDPNSOURCEMODESET_INTERFACE* pVidPnSourceModeSetInterface,
                                 D3DKMDT_HVIDPNSOURCEMODESET hVidPnSourceModeSet,
                                 D3DDDI_VIDEO_PRESENT_SOURCE_ID SourceId);

    // Add the current mode (or the matching to pinned source mode) to the give VidPn target mode set
    NTSTATUS AddSingleTargetMode(_In_ CONST DXGK_VIDPNTARGETMODESET_INTERFACE* pVidPnTargetModeSetInterface,
                                 D3DKMDT_HVIDPNTARGETMODESET hVidPnTargetModeSet,
                                 _In_opt_ CONST D3DKMDT_VIDPN_SOURCE_MODE* pVidPnPinnedSourceModeInfo,
                                 D3DDDI_VIDEO_PRESENT_SOURCE_ID SourceId);
    D3DDDI_VIDEO_PRESENT_SOURCE_ID FindSourceForTarget(D3DDDI_VIDEO_PRESENT_TARGET_ID TargetId, BOOLEAN DefaultToZero);
    NTSTATUS IsVidPnSourceModeFieldsValid(CONST D3DKMDT_VIDPN_SOURCE_MODE* pSourceMode) const;
    NTSTATUS IsVidPnPathFieldsValid(CONST D3DKMDT_VIDPN_PRESENT_PATH* pPath) const;
    NTSTATUS RegisterHWInfo(_In_ ULONG Id);
};

