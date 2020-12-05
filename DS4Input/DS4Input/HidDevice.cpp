#include "HidDevice.h"

HidDevice HidDevice::Create(char * path, int id)
{
	//パスのコピー
	size_t size = 1;
	for (UINT i = 0; path[i] != '\0'; i++)
	{
		size += 1;
	}

	devicePath = new char[size];
	for (UINT i = 0; i < size; i++)
	{
		devicePath[i] = path[i];
	}

	//デバイスハンドルの作成
	deviceHandle = CreateFile(
		devicePath,
		(GENERIC_READ | GENERIC_WRITE),
		(FILE_SHARE_READ | FILE_SHARE_WRITE),
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	HIDD_ATTRIBUTES attributes;
	if (HidD_GetAttributes(deviceHandle, &attributes))
	{
		productID = attributes.ProductID;
		vendorID = attributes.VendorID;
	}

	isCapabilities = false;
	isDevice = 1;

	return *this;
}

HANDLE HidDevice::GetHandle()
{
	return deviceHandle;
}

USHORT HidDevice::GetProductID()
{
	return productID;
}

USHORT HidDevice::GetVendorID()
{
	return vendorID;
}

char * HidDevice::GetDevicePath()
{
	return devicePath;
}

HIDP_CAPS HidDevice::GetCapabilities()
{
	if (isCapabilities == true)
	{
		return capabilities;
	}

	PHIDP_PREPARSED_DATA preparsedData;
	if (HidD_GetPreparsedData(deviceHandle, &preparsedData))
	{
		//基本情報の取得
		if (HIDP_STATUS_SUCCESS == HidP_GetCaps(preparsedData, &capabilities))
		{
			isCapabilities = true;
		}
	}

	HidD_FreePreparsedData(preparsedData);

	return capabilities;
}

void HidDevice::Destroy()
{
	isDevice = 0;
	CloseHandle(deviceHandle);
	delete[] devicePath;
}
