#include<Windows.h>
#include <stdio.h>
#include "dsound.h"
#include "resource.h"
#include <thread>
#include "FormTest.h"
#include <mmreg.h>
#include <iostream>
#include <fstream> 


HINSTANCE mHinstDLL = 0;

extern "C" UINT_PTR  mProcs[12] = { 0 };

LPCSTR mImportNames[] = { "DirectSoundCaptureCreate",
						  "DirectSoundCaptureCreate8",
						  "DirectSoundCaptureEnumerateA",
						  "DirectSoundCaptureEnumerateW",
						  "DirectSoundCreate",
						  "DirectSoundCreate8",
						  "DirectSoundEnumerateA",
						  "DirectSoundEnumerateW",
						  "DirectSoundFullDuplexCreate",
						  "DllCanUnloadNow",
						  "DllGetClassObject",
						  "GetDeviceID" };

typedef int(CALLBACK *DirectSoundEnumerate)(LPVOID, LPVOID);
typedef HRESULT(WINAPI *DirectSoundCreate)(LPCGUID, LPVOID, LPVOID);
typedef HRESULT(WINAPI *DirectSoundCreate8)(LPCGUID, LPVOID, LPVOID);

DWORD WINAPI ShowOnLoad(void* param)
{
	MessageBox(
		NULL,
		L"Phonix v0.1 has hooked into Spotify!",
		L"Phonix",
		MB_TOPMOST | MB_OK
	);
	return 0;
}

DWORD WINAPI ShowDevice(void* param)
{
	MessageBox(
		NULL,
		GetSelectedDevice().Name,
		L"Phonix",
		MB_TOPMOST | MB_OK
	);
	return 0;
}

DWORD WINAPI StartForm(void* param)
{
	wWinMain((HINSTANCE)param, nullptr, nullptr, SW_SHOW);
	return 0;
}
DWORD WINAPI LaterNULL(void* param)
{
	/*std::this_thread::sleep_for(std::chrono::seconds(5));
	WAVEFORMATEX wf;
	wf.wFormatTag = WAVE_FORMAT_PCM;
	wf.wBitsPerSample = 8;
	wf.nSamplesPerSec = 22050;
	wf.nChannels = 1;
	wf.nBlockAlign = 1; // 1 * 8/8
	wf.nAvgBytesPerSec = 22050; //22050 * 1
	MessageBox(NULL, L"HI", L"HI", NULL);
	DSBUFFERDESC ds;
	ds.dwSize = sizeof(DSBUFFERDESC);
	ds.dwFlags = 128;
	ds.dwBufferBytes = 4; //DSBSIZE_MIN
	ds.dwReserved = 0;
	ds.lpwfxFormat = &wf;
	ds.guid3DAlgorithm = GUID_NULL;
	MessageBox(NULL, L"HI", L"HI", NULL);
	LPDIRECTSOUNDBUFFER buff;
	((LPDIRECTSOUND8)param)->CreateSoundBuffer(&ds, &buff, NULL);
	MessageBox(NULL, L"HI", L"HI", NULL);
	dsound(NULL, (LPDIRECTSOUND8)param, NULL);*/

	//DirectSoundCreate8 dsound = (DirectSoundCreate8)mProcs[5];
	//dsound(NULL, param, NULL);
	return 0;
}

inline bool file_exists(const char* name) {
	struct stat buffer;
	return (stat(name, &buffer) == 0);
}

/*bool isEqual(char* one, char* two)
{
	int sizeOfArray = sizeof(one) / sizeof(one[0]);
	for (int i = 0; i < sizeOfArray - 1; i++)
	{
		if (one[i] != two[i])
			return false;
	}
	return true;
}*/

//char SelectedName[255];
int selectedIndex = 0;
BOOL CALLBACK DSEnumProc(LPCGUID lpGUID, LPCTSTR lpszDesc, LPCTSTR lpszDrvName, LPVOID lpContext)
{
	if (lpGUID == 0) return (TRUE);
	int x = AddDevice(Device(lpGUID, lpszDesc));
	//LPCTSTR name = GetSelectedDevice().Name;
	//size_t size = wcstombs(NULL, name, 0);
	//char* CharStr = new char[size + 1];
	//wcstombs(CharStr, name, size + 1);
	//if (isEqual(CharStr, SelectedName))
	if(x == selectedIndex)
		SetSelectedDevice(x);
	return (TRUE);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		if (Loaded) return (TRUE);
		Loaded = true;
		if (file_exists("settings.bin"))
		{
			std::ifstream infile("settings.bin");
			/*int i = 0;
			while (!infile.eof())
			{
				infile.read(SelectedName + i, 1);
				i++;
			}*/
			infile >> selectedIndex;
			infile.close();
		}
		else
		{
			std::ofstream outfile("settings.bin");
			outfile << 0;
			outfile.close();
		}
		TCHAR expandedPath[MAX_PATH];
		ExpandEnvironmentStrings(L"%WINDIR%\\System32\\dsound.dll", expandedPath, MAX_PATH);
		mHinstDLL = LoadLibrary(expandedPath);
		if (!mHinstDLL)
			return (FALSE);
		for (int i = 0; i < 12; i++)
			mProcs[i] = (UINT_PTR)GetProcAddress(mHinstDLL, mImportNames[i]);
		EnumerateDevices();
		
		CreateThread(NULL, 0, StartForm, hinstDLL, 0, NULL);
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {
		std::ofstream outfile("settings.bin");
		/*LPCTSTR name = GetSelectedDevice().Name;
		size_t size = wcstombs(NULL, name, 0);
		char* CharStr = new char[size + 1];
		wcstombs(CharStr, name, size + 1);
		outfile << CharStr;*/
		outfile << GetSelectedDeviceIndex();
		outfile.close();
		
		Loaded = false;
		FreeLibrary(mHinstDLL);
	}
	return (TRUE);
}


void EnumerateDevices()
{
	DirectSoundEnumerate dsenum = (DirectSoundEnumerate)mProcs[7];
	dsenum(DSEnumProc, "Phonix");
}

void UpdateDevice()
{
	
}

HRESULT WINAPI DirectSoundCreate_wrapper(LPCGUID lpGuid, LPVOID *ppDS, LPUNKNOWN pUnkOuter)
{
	DirectSoundCreate dsound = (DirectSoundCreate)mProcs[4];
	return dsound(GetSelectedDevice().Guid, ppDS, pUnkOuter);
}
HRESULT WINAPI DirectSoundCreate8_wrapper(LPCGUID lpGuid, LPDIRECTSOUND8 *ppDS8, LPUNKNOWN pUnkOuter)
{
	//WCHAR szTest[10];
	//swprintf_s(szTest, 10, L"%d", *ex);
	//MessageBoxW(NULL, szTest, L"Anus", 0);
	//CreateThread(NULL, 0, ShowDevice, 0, 0, NULL);
	DirectSoundCreate8 dsound = (DirectSoundCreate8)mProcs[5];
	HRESULT result = dsound(GetSelectedDevice().Guid, ppDS8, pUnkOuter);
	//CreateThread(NULL, 0, LaterNULL, *ppDS8, 0, NULL);
	return result;
}