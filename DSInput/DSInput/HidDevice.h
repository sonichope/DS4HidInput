#pragma once

#include<Windows.h>
#include<SetupAPI.h>
#include<bluetoothapis.h>
#include<iostream>

extern "C"
{
#include <hidsdi.h>
}

#pragma comment(lib,"hid.lib")
#pragma comment(lib,"setupapi.lib")

using namespace std;

class HidDevice
{
public:
	HidDevice Create(char* path, int id);
	HIDP_CAPS GetCapabilities() noexcept;
	void Destroy() noexcept;
	BOOL isDevice;
	inline HANDLE GetHandle() noexcept
	{
		return deviceHandle;
	}
	inline USHORT GetProductID() noexcept
	{
		return productID;
	}
	inline USHORT GetVendorID() noexcept
	{
		return vendorID;
	}
	inline char* GetDevicePath() noexcept
	{
		return devicePath;
	}

private:
	USHORT productID;
	USHORT vendorID;
	HANDLE deviceHandle;
	HIDP_CAPS capabilities;
	bool isCapabilities;
	char* devicePath;

};