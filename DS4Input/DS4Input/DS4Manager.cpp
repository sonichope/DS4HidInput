#include "DS4Manager.h"
#include "DS4Device.h"
#include "DSenseDevice.h"

DS4Manager::DS4Manager()
{
	for (int i = 0; i < 4; i++) {
		dsDevice[i] = nullptr;
	}
}

void DS4Manager::GetDevice()
{
	connectionNum = 0;
	GUID hidGuid;
	HDEVINFO hdevInfo;
	HidD_GetHidGuid(&hidGuid);
	hdevInfo = SetupDiGetClassDevs(&hidGuid, NULL, NULL, (DIGCF_PRESENT | DIGCF_INTERFACEDEVICE));
	SP_DEVICE_INTERFACE_DATA data;
	data.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
	for (int i = 0; SetupDiEnumDeviceInterfaces(hdevInfo, NULL, &hidGuid, i, &data); i++)
	{
		PSP_INTERFACE_DEVICE_DETAIL_DATA detail;
		DWORD size = 0;

		//デバイスインタフェース詳細情報のメモリサイズを取得
		SetupDiGetDeviceInterfaceDetail(hdevInfo, &data, NULL, 0, &size, NULL);

		//デバイスインターフェース詳細情報の領域を確保する
		detail = new SP_INTERFACE_DEVICE_DETAIL_DATA[size];
		if (detail)
		{
			DWORD len = 0;
			memset(detail, 0, size);

			//デバイスインターフェースの詳細情報を読込む
			detail->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
			if (SetupDiGetInterfaceDeviceDetail(hdevInfo, &data, detail, size, &len, NULL))
			{
				//Hidデバイスの作成
				HidDevice device = device.Create(detail->DevicePath, 0);

				if (device.GetVendorID() == 0x54C && device.GetProductID() == 0xce6) {
					//	PS5コントローラー
					dsDevice[connectionNum] = new DSenseDevice(device, connectionNum);
					connectionNum++;
				}
				else if (device.GetVendorID() == 0x54c && (device.GetProductID() == 0x5c4 || device.GetProductID() == 0x9CC))
				{
					//PS4コントローラーとして設定
					dsDevice[connectionNum] = new DS4Device(device, connectionNum);
					connectionNum++;
				}
				else
				{
					//デバイスの破棄
					device.Destroy();
				}
			}
		}
		delete[] detail;
	}
	SetupDestroyDiskSpaceList(hdevInfo);
}

bool DS4Manager::IsDevice(int id)
{
	if (!dsDevice[id]) return false;
	return dsDevice[id]->IsDSDevice();
}

void DS4Manager::ChangeColor(int id, const UCHAR r, const UCHAR g, const UCHAR b)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->ChangeLedColor(LED(r, g, b));
}

void DS4Manager::ChangePlayerLight(int id, const UCHAR val)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->ChangePlayerLight(val);
}

void DS4Manager::ChangeVibration(int id, UCHAR right, UCHAR left)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->ChangeVibration(right, left);
}

void DS4Manager::SendOutput(int id)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->SendOutputReport();
}

void DS4Manager::InputUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		if (dsDevice[i] == nullptr) continue;
		if (dsDevice[i]->IsDSDevice() == false) { continue; }
		dsDevice[i]->GetInputReport();
	}
}

bool DS4Manager::GetButton(int id, UCHAR key)
{
	if (IsDevice(id) == false) return false;
	return dsDevice[id]->GetButton(key);
}

bool DS4Manager::GetButtonDown(int id, UCHAR key)
{
	if (IsDevice(id) == false) return false;
	return dsDevice[id]->GetButtonDown(key);
}

bool DS4Manager::GetButtonUp(int id, UCHAR key)
{
	if (IsDevice(id) == false) return false;
	return dsDevice[id]->GetButtonUp(key);
}

float DS4Manager::GetAxis(int id, UCHAR axis)
{
	if (IsDevice(id) == false) return 0;
	return dsDevice[id]->GetAxis(axis);
}

void DS4Manager::Destroy()
{
	for (int i = 0; i < connectionNum; i++)
	{
		if (dsDevice[i]) {
			dsDevice[i]->Destroy();
		}
	}
}
