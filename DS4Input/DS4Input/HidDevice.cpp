#include "HidDevice.h"

HidDevice HidDevice::Create(const char * path, int id)
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
		nullptr,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL,
		nullptr);

	HIDD_ATTRIBUTES attributes;
	if (HidD_GetAttributes(deviceHandle, &attributes))
	{
		productID = attributes.ProductID;
		vendorID = attributes.VendorID;
	}

	isCapabilities = false;
	isDevice = true;

	return *this;
}

HANDLE HidDevice::GetHandle() const
{
	return deviceHandle;
}

USHORT HidDevice::GetProductID() const
{
	return productID;
}

USHORT HidDevice::GetVendorID() const
{
	return vendorID;
}

char * HidDevice::GetDevicePath() const
{
	return devicePath;
}

HIDP_CAPS HidDevice::GetCapabilities()
{
	if (isCapabilities)
	{
		return capabilities;
	}

	PHIDP_PREPARSED_DATA preparedData;
	if (HidD_GetPreparsedData(deviceHandle, &preparedData))
	{
		//基本情報の取得
		if (HIDP_STATUS_SUCCESS == HidP_GetCaps(preparedData, &capabilities))
		{
			isCapabilities = true;
		}
	}

	HidD_FreePreparsedData(preparedData);

	return capabilities;
}

void HidDevice::Destroy()
{
	productID = 0;
	vendorID = 0;
	isDevice = false;
	CloseHandle(deviceHandle);
	deviceHandle = nullptr;
	delete[] devicePath;
	devicePath = nullptr;
}
