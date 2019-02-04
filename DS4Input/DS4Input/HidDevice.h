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
	HANDLE GetHandle();
	USHORT GetProductID();
	USHORT GetVendorID();
	char* GetDevicePath();
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