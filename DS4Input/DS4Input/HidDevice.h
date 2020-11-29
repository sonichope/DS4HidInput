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
	HidDevice Create(const char* path, int id);
	HANDLE GetHandle() const;
	USHORT GetProductID() const;
	USHORT GetVendorID() const;
	char* GetDevicePath() const;
	HIDP_CAPS GetCapabilities();
	void Destroy();
	bool isDevice;

private:
	USHORT productID;
	USHORT vendorID;
	HANDLE deviceHandle;
	HIDP_CAPS capabilities;
	bool isCapabilities;
	char* devicePath;

};