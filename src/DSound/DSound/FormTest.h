#pragma once

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow);

struct Device
{
	LPCGUID Guid;
	LPCTSTR Name;

	Device(LPCGUID guid, LPCTSTR name)
	{
		Guid = guid;
		Name = name;
	}
	Device()
	{
		Guid = 0;
		Name = L"";
	}
};

int AddDevice(Device device);
Device GetSelectedDevice();
void EnumerateDevices();
void UpdateDevice();
void ResetDevices();
void SetSelectedDevice(int device);
int GetSelectedDeviceIndex();