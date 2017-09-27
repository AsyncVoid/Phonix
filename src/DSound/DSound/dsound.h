#pragma once
#pragma data_seg("Shared")
bool Loaded = false;
#pragma data_seg

typedef struct _DSBUFFERDESC
{
	DWORD		dwSize;
	DWORD		dwFlags;
	DWORD		dwBufferBytes;
	DWORD		dwReserved;
	LPWAVEFORMATEX	lpwfxFormat;
	GUID		guid3DAlgorithm;
} DSBUFFERDESC, *LPDSBUFFERDESC;
typedef const DSBUFFERDESC *LPCDSBUFFERDESC;

DEFINE_GUID(IID_IDirectSoundBuffer, 0x279AFA85, 0x4981, 0x11CE, 0xA5, 0x21, 0x00, 0x20, 0xAF, 0x0B, 0xE5, 0x60);
typedef struct IDirectSoundBuffer *LPDIRECTSOUNDBUFFER, **LPLPDIRECTSOUNDBUFFER;

typedef struct _DSCAPS
{
	DWORD	dwSize;
	DWORD	dwFlags;
	DWORD	dwMinSecondarySampleRate;
	DWORD	dwMaxSecondarySampleRate;
	DWORD	dwPrimaryBuffers;
	DWORD	dwMaxHwMixingAllBuffers;
	DWORD	dwMaxHwMixingStaticBuffers;
	DWORD	dwMaxHwMixingStreamingBuffers;
	DWORD	dwFreeHwMixingAllBuffers;
	DWORD	dwFreeHwMixingStaticBuffers;
	DWORD	dwFreeHwMixingStreamingBuffers;
	DWORD	dwMaxHw3DAllBuffers;
	DWORD	dwMaxHw3DStaticBuffers;
	DWORD	dwMaxHw3DStreamingBuffers;
	DWORD	dwFreeHw3DAllBuffers;
	DWORD	dwFreeHw3DStaticBuffers;
	DWORD	dwFreeHw3DStreamingBuffers;
	DWORD	dwTotalHwMemBytes;
	DWORD	dwFreeHwMemBytes;
	DWORD	dwMaxContigFreeHwMemBytes;
	DWORD	dwUnlockTransferRateHwBuffers;
	DWORD	dwPlayCpuOverheadSwBuffers;
	DWORD	dwReserved1;
	DWORD	dwReserved2;
} DSCAPS, *LPDSCAPS;

DEFINE_GUID(CLSID_DirectSound8, 0x3901cc3f, 0x84b5, 0x4fa4, 0xba, 0x35, 0xaa, 0x81, 0x72, 0xb8, 0xa0, 0x9b);
DEFINE_GUID(IID_IDirectSound8, 0xC50A7E93, 0xF395, 0x4834, 0x9E, 0xF6, 0x7F, 0xA9, 0x9D, 0xE5, 0x09, 0x66);
typedef struct IDirectSound8 *LPDIRECTSOUND8, **LPLPDIRECTSOUND8;

#define INTERFACE IDirectSound8
DECLARE_INTERFACE_(IDirectSound8, IUnknown)
{
	/*** IUnknown methods ***/
	STDMETHOD_(HRESULT, QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
	STDMETHOD_(ULONG, AddRef)(THIS) PURE;
	STDMETHOD_(ULONG, Release)(THIS) PURE;
	/*** IDirectSound8 methods ***/
	STDMETHOD(CreateSoundBuffer)(THIS_ LPCDSBUFFERDESC lpcDSBufferDesc, LPLPDIRECTSOUNDBUFFER lplpDirectSoundBuffer, IUnknown *pUnkOuter) PURE;
	STDMETHOD(GetCaps)(THIS_ LPDSCAPS lpDSCaps) PURE;
	STDMETHOD(DuplicateSoundBuffer)(THIS_ LPDIRECTSOUNDBUFFER lpDsbOriginal, LPLPDIRECTSOUNDBUFFER lplpDsbDuplicate) PURE;
	STDMETHOD(SetCooperativeLevel)(THIS_ HWND hwnd, DWORD dwLevel) PURE;
	STDMETHOD(Compact)(THIS) PURE;
	STDMETHOD(GetSpeakerConfig)(THIS_ LPDWORD lpdwSpeakerConfig) PURE;
	STDMETHOD(SetSpeakerConfig)(THIS_ DWORD dwSpeakerConfig) PURE;
	STDMETHOD(Initialize)(THIS_ LPCGUID lpcGuid) PURE;
	STDMETHOD(VerifyCertification)(THIS_ LPDWORD pdwCertified) PURE;
};
#undef INTERFACE
#define IDirectSound8_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirectSound8_AddRef(p)             (p)->AddRef()
#define IDirectSound8_Release(p)            (p)->Release()
#define IDirectSound8_CreateSoundBuffer(p,a,b,c)  (p)->CreateSoundBuffer(a,b,c)
#define IDirectSound8_GetCaps(p,a)                (p)->GetCaps(a)
#define IDirectSound8_DuplicateSoundBuffer(p,a,b) (p)->DuplicateSoundBuffer(a,b)
#define IDirectSound8_SetCooperativeLevel(p,a,b)  (p)->SetCooperativeLevel(a,b)
#define IDirectSound8_Compact(p)                  (p)->Compact()
#define IDirectSound8_GetSpeakerConfig(p,a)       (p)->GetSpeakerConfig(a)
#define IDirectSound8_SetSpeakerConfig(p,a)       (p)->SetSpeakerConfig(a)
#define IDirectSound8_Initialize(p,a)             (p)->Initialize(a)
#define IDirectSound8_VerifyCertification(p,a)    (p)->VerifyCertification(a)

#define DSSPEAKER_COMBINED(c, g)    ((DWORD)(((BYTE)(c)) | ((DWORD)((BYTE)(g))) << 16))