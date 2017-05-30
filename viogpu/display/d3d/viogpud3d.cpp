// viogpud3d.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "viogpud3d.h"
#include <assert.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif



static HRESULT APIENTRY
VioGpuSetRenderState(HANDLE hDevice, CONST D3DDDIARG_RENDERSTATE *pSetRenderState)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuUpdateWInfo(HANDLE hDevice, CONST D3DDDIARG_WINFO *pUpdateWInfo)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuValidateDevice(HANDLE hDevice, D3DDDIARG_VALIDATETEXTURESTAGESTATE *pValidateTextureStageState)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetTextureStageState(HANDLE hDevice, CONST D3DDDIARG_TEXTURESTAGESTATE *pSetTextureStageState)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetTexture(HANDLE hDevice, UINT Stage, HANDLE hTexture)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetPixelShader(HANDLE hDevice, HANDLE hShader)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetPixelShaderConst(HANDLE hDevice, CONST D3DDDIARG_SETPIXELSHADERCONST *pSetPixelShaderConst, CONST FLOAT *pRegisters)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetStreamSourceUm(HANDLE hDevice, CONST D3DDDIARG_SETSTREAMSOURCEUM *pSetStreamSourceUm, CONST VOID *pUmBuffer)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetIndices(HANDLE hDevice, CONST D3DDDIARG_SETINDICES *pSetIndices)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetIndicesUm(HANDLE hDevice, UINT IndexSize, CONST VOID *pUmBuffer)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDrawPrimitive(HANDLE hDevice, CONST D3DDDIARG_DRAWPRIMITIVE *pDrawPrimitive, CONST UINT *pFlagBuffer)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDrawIndexedPrimitive(HANDLE hDevice, CONST D3DDDIARG_DRAWINDEXEDPRIMITIVE *pDrawIndexedPrimitive)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDrawRectPatch(HANDLE hDevice, CONST D3DDDIARG_DRAWRECTPATCH *pDrawRectPatch, CONST D3DDDIRECTPATCH_INFO *pInfo, CONST FLOAT *pPatch)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDrawTriPatch(HANDLE hDevice, CONST D3DDDIARG_DRAWTRIPATCH *pDrawTriPatch, CONST D3DDDITRIPATCH_INFO *pInfo, CONST FLOAT *pPatch)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDrawPrimitive2(HANDLE hDevice, CONST D3DDDIARG_DRAWPRIMITIVE2 *pDrawPrimitive2)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDrawIndexedPrimitive2(HANDLE hDevice, CONST D3DDDIARG_DRAWINDEXEDPRIMITIVE2 *pDrawIndexedPrimitive2, UINT IndicesSize, CONST VOID *pIndexBuffer, CONST UINT *pFlagBuffer)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuVolBlt(HANDLE hDevice, CONST D3DDDIARG_VOLUMEBLT *pVolumeBlt)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuBufBlt(HANDLE hDevice, CONST D3DDDIARG_BUFFERBLT *pBufferBlt)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuTexBlt(HANDLE hDevice, CONST D3DDDIARG_TEXBLT *pTextBlt)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuStateSet(HANDLE hDevice, D3DDDIARG_STATESET *pStateSet)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetPriority(HANDLE hDevice, CONST D3DDDIARG_SETPRIORITY *pSetPriority)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuClear(HANDLE hDevice, CONST D3DDDIARG_CLEAR *pClear, UINT NumRect, CONST RECT *pRect)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuUpdatePalette(HANDLE hDevice, CONST D3DDDIARG_UPDATEPALETTE *pUpdatePalette, CONST PALETTEENTRY *pPaletteEntry)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetPalette(HANDLE hDevice, CONST D3DDDIARG_SETPALETTE *pSetPalette)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetVertexShaderConst(HANDLE hDevice, CONST D3DDDIARG_SETVERTEXSHADERCONST *pSetVertexShaderConst, CONST VOID *pRegisters)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuMultiplyTransform(HANDLE hDevice, CONST D3DDDIARG_MULTIPLYTRANSFORM *pMultiplyTransform)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetTransform(HANDLE hDevice, CONST D3DDDIARG_SETTRANSFORM *pSetTransform)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetViewport(HANDLE hDevice, CONST D3DDDIARG_VIEWPORTINFO *pViewPortInfo)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetZRange(HANDLE hDevice, CONST D3DDDIARG_ZRANGE *pZRange)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetMaterial(HANDLE hDevice, CONST D3DDDIARG_SETMATERIAL *pSetMaterial)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetLight(HANDLE hDevice, CONST D3DDDIARG_SETLIGHT *pSetLight, CONST D3DDDI_LIGHT *pLight)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateLight(HANDLE hDevice, CONST D3DDDIARG_CREATELIGHT *pCreateLight)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyLight(HANDLE hDevice, CONST D3DDDIARG_DESTROYLIGHT *pDestroyLight)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetClipPlane(HANDLE hDevice, CONST D3DDDIARG_SETCLIPPLANE *pSetClipPlane)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuGetInfo(HANDLE hDevice, UINT DevInfoID, VOID *pDevInfoStruct, UINT DevInfoSize)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuLock(HANDLE hDevice, D3DDDIARG_LOCK *pLock)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuUnlock(HANDLE hDevice, CONST D3DDDIARG_UNLOCK *pUnlock)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateResource(HANDLE hDevice, D3DDDIARG_CREATERESOURCE *pCreateResource)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyResource(HANDLE hDevice, HANDLE hResource)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetDisplayMode(HANDLE hDevice, CONST D3DDDIARG_SETDISPLAYMODE *pSetDisplayMode)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuPresent(HANDLE hDevice, CONST D3DDDIARG_PRESENT *pPresent)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuFlush(HANDLE hDevice)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateVertexShaderDecl(HANDLE hDevice, D3DDDIARG_CREATEVERTEXSHADERDECL *pCreateVertexShaderDecl, CONST D3DDDIVERTEXELEMENT *pVertexElements)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetVertexShaderDecl(HANDLE hDevice, HANDLE hShader)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDeleteVertexShaderDecl(HANDLE hDevice, HANDLE hShader)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateVertexShaderFunc(HANDLE hDevice, D3DDDIARG_CREATEVERTEXSHADERFUNC *pCreateVertexShaderFunc, CONST UINT *pCode)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetVertexShaderFunc(HANDLE hDevice, HANDLE hShader)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDeleteVertexShaderFunc(HANDLE hDevice, HANDLE hShader)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetVertexShaderConstI(HANDLE hDevice, CONST D3DDDIARG_SETVERTEXSHADERCONSTI *pSetVertexShaderConstI, CONST INT *pRegisters)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetVertexShaderConstB(HANDLE hDevice, CONST D3DDDIARG_SETVERTEXSHADERCONSTB *pSetVertexShaderConstB, CONST BOOL *pRegisters)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetScissorRect(HANDLE hDevice, CONST RECT *pRect)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetStreamSource(HANDLE hDevice, CONST D3DDDIARG_SETSTREAMSOURCE *pSetStreamSource)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetStreamSourceFreq(HANDLE hDevice, CONST D3DDDIARG_SETSTREAMSOURCEFREQ *pSetStreamSourceFreq)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetConvolutionKernelMono(HANDLE hDevice, CONST D3DDDIARG_SETCONVOLUTIONKERNELMONO *pdSetConvolutionKernelMono)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuComposeRects(HANDLE hDevice, CONST D3DDDIARG_COMPOSERECTS *pComposeRects)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuBlt(HANDLE hDevice, CONST D3DDDIARG_BLT *pBlt)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuColorFill(HANDLE hDevice, CONST D3DDDIARG_COLORFILL *pColorFill)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDepthFill(HANDLE hDevice, CONST D3DDDIARG_DEPTHFILL *pDepthFill)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateQuery(HANDLE hDevice, D3DDDIARG_CREATEQUERY *pCreateQuery)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyQuery(HANDLE hDevice, HANDLE hQuery)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuIssueQuery(HANDLE hDevice, CONST D3DDDIARG_ISSUEQUERY *pIssueQuery)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY 
VioGpuGetQueryData(HANDLE hDevice, CONST D3DDDIARG_GETQUERYDATA *pGetQueryData)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetRenderTarget(HANDLE hDevice, CONST D3DDDIARG_SETRENDERTARGET *pSetRenderTarget)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetDepthStencil(HANDLE hDevice, CONST D3DDDIARG_SETDEPTHSTENCIL *pSetDepthStencil)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuGenerateMipSubLevels(HANDLE hDevice, CONST D3DDDIARG_GENERATEMIPSUBLEVELS *pGenerateMipSubLevels)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetPixelShaderConstI(HANDLE hDevice, CONST D3DDDIARG_SETPIXELSHADERCONSTI* pData, CONST INT *pRegisters)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetPixelShaderConstB(HANDLE hDevice, CONST D3DDDIARG_SETPIXELSHADERCONSTB *pSetPixelShaderConstB, CONST BOOL *pRegisters)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreatePixelShader(HANDLE hDevice, D3DDDIARG_CREATEPIXELSHADER *pCreatePixelShader, CONST UINT *pCode)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDeletePixelShader(HANDLE hDevice, HANDLE hShader)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateDecodeDevice(HANDLE hDevice, D3DDDIARG_CREATEDECODEDEVICE *pCreateDecodeDevice)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyDecodeDevice(HANDLE hDevice, HANDLE hDecodeDevice)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetDecodeRenderTarget(HANDLE hDevice, CONST D3DDDIARG_SETDECODERENDERTARGET *pSetDecodeRenderTarget)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDecodeBeginFrame(HANDLE hDevice, D3DDDIARG_DECODEBEGINFRAME *pDecodeBeginFrame)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDecodeEndFrame(HANDLE hDevice, D3DDDIARG_DECODEENDFRAME *pDecodeEndFrame)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDecodeExecute(HANDLE hDevice, CONST D3DDDIARG_DECODEEXECUTE *pDecodeExecute)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDecodeExtensionExecute(HANDLE hDevice, CONST D3DDDIARG_DECODEEXTENSIONEXECUTE *pDecodeExtensionExecute)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateVideoProcessDevice(HANDLE hDevice, D3DDDIARG_CREATEVIDEOPROCESSDEVICE *pCreateVideoProcessDevice)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyVideoProcessDevice(HANDLE hDevice, HANDLE hVideoProcessor)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuVideoProcessBeginFrame(HANDLE hDevice, HANDLE hVideoProcessor)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuVideoProcessEndFrame(HANDLE hDevice, D3DDDIARG_VIDEOPROCESSENDFRAME *pVideoProcessEndFrame)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetVideoProcessRenderTarget(HANDLE hDevice, CONST D3DDDIARG_SETVIDEOPROCESSRENDERTARGET *pSetVideoProcessRenderTarget)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuVideoProcessBlt(HANDLE hDevice, CONST D3DDDIARG_VIDEOPROCESSBLT *pVidoeProcessBlt)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCreateExtensionDevice(HANDLE hDevice, D3DDDIARG_CREATEEXTENSIONDEVICE *pCreateExtensionDevice)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyExtensionDevice(HANDLE hDevice, HANDLE hExtension)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuExtensionExecute(HANDLE hDevice, CONST D3DDDIARG_EXTENSIONEXECUTE *pExtensionExecute)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyDevice(HANDLE hDevice)
{
    TraceLog((L"---> '%s'.\n", __FUNCTION__));
    
    assert(hDevice != NULL);

    free(hDevice);

    TraceLog((L"<--- '%s'.\n", __FUNCTION__));

    return S_OK;
}

static HRESULT APIENTRY
VioGpuCreateOverlay(HANDLE hDevice, D3DDDIARG_CREATEOVERLAY *pCreateOverlay)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuUpdateOverlay(HANDLE hDevice, CONST D3DDDIARG_UPDATEOVERLAY *pUpdateOverlay)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuFlipOverlay(HANDLE hDevice, CONST D3DDDIARG_FLIPOVERLAY *pFlipOverlay)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuGetOverlayColorControls(HANDLE hDevice, D3DDDIARG_GETOVERLAYCOLORCONTROLS *pGetOverlayColorControls)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuSetOverlayColorControls(HANDLE hDevice, CONST D3DDDIARG_SETOVERLAYCOLORCONTROLS *pSetOverlayColorControls)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuDestroyOverlay(HANDLE hDevice, CONST D3DDDIARG_DESTROYOVERLAY *pDestroyOverlay)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuQueryResourceResidency(HANDLE hDevice, CONST D3DDDIARG_QUERYRESOURCERESIDENCY *pQueryResourceResidency)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuOpenResource(HANDLE hDevice, D3DDDIARG_OPENRESOURCE *pOpenResource)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuGetCaptureAllocationHandle(HANDLE hDevice, D3DDDIARG_GETCAPTUREALLOCATIONHANDLE *pGetCaptureAllocationHandle)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuCaptureToSysMem(HANDLE hDevice, CONST D3DDDIARG_CAPTURETOSYSMEM *pCaptureToSystem)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuLockAsync(HANDLE hDevice, D3DDDIARG_LOCKASYNC *pLockAsync)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuUnlockAsync(HANDLE hDevice, CONST D3DDDIARG_UNLOCKASYNC *pUnlockAsync)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuRename(HANDLE hDevice, CONST D3DDDIARG_RENAME *pRename)
{
    return E_NOTIMPL;
}

static HRESULT APIENTRY
VioGpuGetCaps(HANDLE hAdapter, CONST D3DDDIARG_GETCAPS *pGetCaps)
{

    TraceLog((L"---> '%s'.\n", __FUNCTION__));

    if ((hAdapter == NULL)||(pGetCaps == NULL))
        return E_INVALIDARG;

    // TODO 3D driver reports capabilities here

    TraceLog((L"<--- '%s'.\n", __FUNCTION__));

    return S_OK; 
}

static HRESULT APIENTRY
VioGpuCreateDevice(HANDLE hAdapter, D3DDDIARG_CREATEDEVICE *pCreateData)
{
    PVIOGPU_D3D_ADAPTER pVioGpuAdapter = (PVIOGPU_D3D_ADAPTER)hAdapter;
    PVIOGPU_D3D_DEVICE  pVioGpuDevice;

    TraceLog((L"====> '%s'.\n", __FUNCTION__));

    if ((hAdapter == NULL)||(pCreateData == NULL))
        return E_INVALIDARG;

    // Create a device object
    pVioGpuDevice = (PVIOGPU_D3D_DEVICE)malloc(sizeof(VIOGPU_D3D_DEVICE));
    if (pVioGpuDevice == NULL) {
        TraceLog((L"Failed to create device object.\n"));
        return E_OUTOFMEMORY;
    }
    ZeroMemory(pVioGpuDevice, sizeof(VIOGPU_D3D_DEVICE));
    pVioGpuDevice->pVioGpuAdapter = pVioGpuAdapter;

    // Copy the input values
    pVioGpuDevice->hDevice = pCreateData->hDevice;
    pVioGpuDevice->Interface = pCreateData->Interface;
    pVioGpuDevice->Version = pCreateData->Version;
    pVioGpuDevice->DeviceCallbacks = *pCreateData->pCallbacks;
    pVioGpuDevice->Flags = pCreateData->Flags;

    // Set the output values
    pCreateData->hDevice = pVioGpuDevice;

    pCreateData->pDeviceFuncs->pfnSetRenderState                = VioGpuSetRenderState;
    pCreateData->pDeviceFuncs->pfnUpdateWInfo                   = VioGpuUpdateWInfo;
    pCreateData->pDeviceFuncs->pfnValidateDevice                = VioGpuValidateDevice;
    pCreateData->pDeviceFuncs->pfnSetTextureStageState          = VioGpuSetTextureStageState;
    pCreateData->pDeviceFuncs->pfnSetTexture                    = VioGpuSetTexture;
    pCreateData->pDeviceFuncs->pfnSetPixelShader                = VioGpuSetPixelShader;
    pCreateData->pDeviceFuncs->pfnSetPixelShaderConst           = VioGpuSetPixelShaderConst;
    pCreateData->pDeviceFuncs->pfnSetStreamSourceUm             = VioGpuSetStreamSourceUm;
    pCreateData->pDeviceFuncs->pfnSetIndices                    = VioGpuSetIndices;
    pCreateData->pDeviceFuncs->pfnSetIndicesUm                  = VioGpuSetIndicesUm;
    pCreateData->pDeviceFuncs->pfnDrawPrimitive                 = VioGpuDrawPrimitive;
    pCreateData->pDeviceFuncs->pfnDrawIndexedPrimitive          = VioGpuDrawIndexedPrimitive;
    pCreateData->pDeviceFuncs->pfnDrawRectPatch                 = VioGpuDrawRectPatch;
    pCreateData->pDeviceFuncs->pfnDrawTriPatch                  = VioGpuDrawTriPatch;
    pCreateData->pDeviceFuncs->pfnDrawPrimitive2                = VioGpuDrawPrimitive2;
    pCreateData->pDeviceFuncs->pfnDrawIndexedPrimitive2         = VioGpuDrawIndexedPrimitive2;
    pCreateData->pDeviceFuncs->pfnVolBlt                        = VioGpuVolBlt;
    pCreateData->pDeviceFuncs->pfnBufBlt                        = VioGpuBufBlt;
    pCreateData->pDeviceFuncs->pfnTexBlt                        = VioGpuTexBlt;
    pCreateData->pDeviceFuncs->pfnStateSet                      = VioGpuStateSet;
    pCreateData->pDeviceFuncs->pfnSetPriority                   = VioGpuSetPriority;
    pCreateData->pDeviceFuncs->pfnClear                         = VioGpuClear;
    pCreateData->pDeviceFuncs->pfnUpdatePalette                 = VioGpuUpdatePalette;
    pCreateData->pDeviceFuncs->pfnSetPalette                    = VioGpuSetPalette;
    pCreateData->pDeviceFuncs->pfnSetVertexShaderConst          = VioGpuSetVertexShaderConst;
    pCreateData->pDeviceFuncs->pfnMultiplyTransform             = VioGpuMultiplyTransform;
    pCreateData->pDeviceFuncs->pfnSetTransform                  = VioGpuSetTransform;
    pCreateData->pDeviceFuncs->pfnSetViewport                   = VioGpuSetViewport;
    pCreateData->pDeviceFuncs->pfnSetZRange                     = VioGpuSetZRange;
    pCreateData->pDeviceFuncs->pfnSetMaterial                   = VioGpuSetMaterial;
    pCreateData->pDeviceFuncs->pfnSetLight                      = VioGpuSetLight;
    pCreateData->pDeviceFuncs->pfnCreateLight                   = VioGpuCreateLight;
    pCreateData->pDeviceFuncs->pfnDestroyLight                  = VioGpuDestroyLight;
    pCreateData->pDeviceFuncs->pfnSetClipPlane                  = VioGpuSetClipPlane;
    pCreateData->pDeviceFuncs->pfnGetInfo                       = VioGpuGetInfo;
    pCreateData->pDeviceFuncs->pfnLock                          = VioGpuLock;
    pCreateData->pDeviceFuncs->pfnUnlock                        = VioGpuUnlock;
    pCreateData->pDeviceFuncs->pfnCreateResource                = VioGpuCreateResource;
    pCreateData->pDeviceFuncs->pfnDestroyResource               = VioGpuDestroyResource;
    pCreateData->pDeviceFuncs->pfnSetDisplayMode                = VioGpuSetDisplayMode;
    pCreateData->pDeviceFuncs->pfnPresent                       = VioGpuPresent;
    pCreateData->pDeviceFuncs->pfnFlush                         = VioGpuFlush;
    pCreateData->pDeviceFuncs->pfnCreateVertexShaderFunc        = VioGpuCreateVertexShaderFunc;
    pCreateData->pDeviceFuncs->pfnDeleteVertexShaderFunc        = VioGpuDeleteVertexShaderFunc;
    pCreateData->pDeviceFuncs->pfnSetVertexShaderFunc           = VioGpuSetVertexShaderFunc;
    pCreateData->pDeviceFuncs->pfnCreateVertexShaderDecl        = VioGpuCreateVertexShaderDecl;
    pCreateData->pDeviceFuncs->pfnDeleteVertexShaderDecl        = VioGpuDeleteVertexShaderDecl;
    pCreateData->pDeviceFuncs->pfnSetVertexShaderDecl           = VioGpuSetVertexShaderDecl;
    pCreateData->pDeviceFuncs->pfnSetVertexShaderConstI         = VioGpuSetVertexShaderConstI;
    pCreateData->pDeviceFuncs->pfnSetVertexShaderConstB         = VioGpuSetVertexShaderConstB;
    pCreateData->pDeviceFuncs->pfnSetScissorRect                = VioGpuSetScissorRect;
    pCreateData->pDeviceFuncs->pfnSetStreamSource               = VioGpuSetStreamSource;
    pCreateData->pDeviceFuncs->pfnSetStreamSourceFreq           = VioGpuSetStreamSourceFreq;
    pCreateData->pDeviceFuncs->pfnSetConvolutionKernelMono      = VioGpuSetConvolutionKernelMono;
    pCreateData->pDeviceFuncs->pfnComposeRects                  = VioGpuComposeRects;
    pCreateData->pDeviceFuncs->pfnBlt                           = VioGpuBlt;
    pCreateData->pDeviceFuncs->pfnColorFill                     = VioGpuColorFill;
    pCreateData->pDeviceFuncs->pfnDepthFill                     = VioGpuDepthFill;
    pCreateData->pDeviceFuncs->pfnCreateQuery                   = VioGpuCreateQuery;
    pCreateData->pDeviceFuncs->pfnDestroyQuery                  = VioGpuDestroyQuery;
    pCreateData->pDeviceFuncs->pfnIssueQuery                    = VioGpuIssueQuery;
    pCreateData->pDeviceFuncs->pfnGetQueryData                  = VioGpuGetQueryData;
    pCreateData->pDeviceFuncs->pfnSetRenderTarget               = VioGpuSetRenderTarget;
    pCreateData->pDeviceFuncs->pfnSetDepthStencil               = VioGpuSetDepthStencil;
    pCreateData->pDeviceFuncs->pfnGenerateMipSubLevels          = VioGpuGenerateMipSubLevels;
    pCreateData->pDeviceFuncs->pfnSetPixelShaderConstI          = VioGpuSetPixelShaderConstI;
    pCreateData->pDeviceFuncs->pfnSetPixelShaderConstB          = VioGpuSetPixelShaderConstB;
    pCreateData->pDeviceFuncs->pfnCreatePixelShader             = VioGpuCreatePixelShader;
    pCreateData->pDeviceFuncs->pfnDeletePixelShader             = VioGpuDeletePixelShader;
    pCreateData->pDeviceFuncs->pfnCreateDecodeDevice            = VioGpuCreateDecodeDevice;
    pCreateData->pDeviceFuncs->pfnDestroyDecodeDevice           = VioGpuDestroyDecodeDevice;
    pCreateData->pDeviceFuncs->pfnSetDecodeRenderTarget         = VioGpuSetDecodeRenderTarget;
    pCreateData->pDeviceFuncs->pfnDecodeBeginFrame              = VioGpuDecodeBeginFrame;
    pCreateData->pDeviceFuncs->pfnDecodeEndFrame                = VioGpuDecodeEndFrame;
    pCreateData->pDeviceFuncs->pfnDecodeExecute                 = VioGpuDecodeExecute;
    pCreateData->pDeviceFuncs->pfnDecodeExtensionExecute        = VioGpuDecodeExtensionExecute;
    pCreateData->pDeviceFuncs->pfnCreateVideoProcessDevice      = VioGpuCreateVideoProcessDevice;
    pCreateData->pDeviceFuncs->pfnDestroyVideoProcessDevice     = VioGpuDestroyVideoProcessDevice;
    pCreateData->pDeviceFuncs->pfnVideoProcessBeginFrame        = VioGpuVideoProcessBeginFrame;
    pCreateData->pDeviceFuncs->pfnVideoProcessEndFrame          = VioGpuVideoProcessEndFrame;
    pCreateData->pDeviceFuncs->pfnSetVideoProcessRenderTarget   = VioGpuSetVideoProcessRenderTarget;
    pCreateData->pDeviceFuncs->pfnVideoProcessBlt               = VioGpuVideoProcessBlt;
    pCreateData->pDeviceFuncs->pfnCreateExtensionDevice         = VioGpuCreateExtensionDevice;
    pCreateData->pDeviceFuncs->pfnDestroyExtensionDevice        = VioGpuDestroyExtensionDevice;
    pCreateData->pDeviceFuncs->pfnExtensionExecute              = VioGpuExtensionExecute;
    pCreateData->pDeviceFuncs->pfnCreateOverlay                 = VioGpuCreateOverlay;
    pCreateData->pDeviceFuncs->pfnUpdateOverlay                 = VioGpuUpdateOverlay;
    pCreateData->pDeviceFuncs->pfnFlipOverlay                   = VioGpuFlipOverlay;
    pCreateData->pDeviceFuncs->pfnGetOverlayColorControls       = VioGpuGetOverlayColorControls;
    pCreateData->pDeviceFuncs->pfnSetOverlayColorControls       = VioGpuSetOverlayColorControls;
    pCreateData->pDeviceFuncs->pfnDestroyOverlay                = VioGpuDestroyOverlay;
    pCreateData->pDeviceFuncs->pfnDestroyDevice                 = VioGpuDestroyDevice;
    pCreateData->pDeviceFuncs->pfnQueryResourceResidency        = VioGpuQueryResourceResidency;
    pCreateData->pDeviceFuncs->pfnOpenResource                  = VioGpuOpenResource;
    pCreateData->pDeviceFuncs->pfnGetCaptureAllocationHandle    = VioGpuGetCaptureAllocationHandle;
    pCreateData->pDeviceFuncs->pfnCaptureToSysMem               = VioGpuCaptureToSysMem;
    pCreateData->pDeviceFuncs->pfnLockAsync                     = VioGpuLockAsync;
    pCreateData->pDeviceFuncs->pfnUnlockAsync                   = VioGpuUnlockAsync;
    pCreateData->pDeviceFuncs->pfnRename                        = VioGpuRename;

    TraceLog((L"<--- '%s'.\n", __FUNCTION__));

    return S_OK; 
}

static HRESULT APIENTRY
VioGpuCloseAdapter(HANDLE hAdapter)
{
    TraceLog((L"---> '%s'.\n", __FUNCTION__));
    
    assert(hAdapter != NULL);

    free(hAdapter);

    TraceLog((L"<--- '%s'.\n", __FUNCTION__));

    return S_OK;
}


HRESULT APIENTRY
OpenAdapter(D3DDDIARG_OPENADAPTER *pOpenData)
{
    HRESULT hr;
    PVIOGPU_D3D_ADAPTER pVioGpuAdapter;
    D3DDDICB_QUERYADAPTERINFO QueryAdapterInfo;
    VIOGPU_PRIVATEDATA PrivateData;

    TraceLog((L"---> '%s'.\n", __FUNCTION__));

    // Handshake with our driver
    QueryAdapterInfo.pPrivateDriverData = &PrivateData;
    QueryAdapterInfo.PrivateDriverDataSize = sizeof(VIOGPU_PRIVATEDATA);
    hr = pOpenData->pAdapterCallbacks->pfnQueryAdapterInfoCb(pOpenData->hAdapter, &QueryAdapterInfo);
    if (FAILED(hr)) {
        TraceLog((L"<--->pfnQueryAdapterInfoCb failed - hr: 0x%x\n", hr));
        return hr;
    }

//    if ((PrivateData.Magic != XENGFX_D3D_MAGIC)||(PrivateData.Version != XENGFX_D3D_MAGIC)) {
//        TraceLog((L"<--->Invalid driver magic %x or version %d failed\n",
//                          PrivateData.Magic, PrivateData.Version));
//        return E_FAIL;
//    }

    // Create an adapter object
    pVioGpuAdapter = (PVIOGPU_D3D_ADAPTER)malloc(sizeof(VIOGPU_D3D_ADAPTER));
    if (pVioGpuAdapter == NULL) {
        TraceLog((L"<--->Failed to create adapter object.\n"));
        return E_OUTOFMEMORY;
    }
    ZeroMemory(pVioGpuAdapter, sizeof(VIOGPU_D3D_ADAPTER));

    pVioGpuAdapter->hAdapter = pOpenData->hAdapter;
    pVioGpuAdapter->Interface = pOpenData->Interface;
    pVioGpuAdapter->Version = pOpenData->Version;
    pVioGpuAdapter->AdapterCallbacks = *pOpenData->pAdapterCallbacks;
    pVioGpuAdapter->PrivateData = PrivateData;

    pOpenData->hAdapter = pVioGpuAdapter;
    pOpenData->pAdapterFuncs->pfnGetCaps = VioGpuGetCaps;
    pOpenData->pAdapterFuncs->pfnCreateDevice = VioGpuCreateDevice;
    pOpenData->pAdapterFuncs->pfnCloseAdapter = VioGpuCloseAdapter;
    pOpenData->DriverVersion = D3D_UMD_INTERFACE_VERSION;

    TraceLog((L"<--- '%s'.\n", __FUNCTION__));
    
    return S_OK;
}
