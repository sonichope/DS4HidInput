#include "DSManager.h"
#include "DS4Device.h"
#include "DSenseDevice.h"

DSManager::DSManager() noexcept
{
	for (int i = 0; i < 4; i++) {
		dsDevice[i] = nullptr;
	}
}

void DSManager::GetDevice()
{
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
					for (int i = 0; i < 4; i++) {
						if (!dsDevice[i]) {
							dsDevice[i] = new DSenseDevice(device, i);
							break;
						}
					}
				}
				else if (device.GetVendorID() == 0x54c && (device.GetProductID() == 0x5c4 || device.GetProductID() == 0x9CC))
				{
					for (int i = 0; i < 4; i++) {
						if (!dsDevice[i]) {
							//PS4コントローラーとして設定
							dsDevice[i] = new DS4Device(device, i);
							break;
						}
					}
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

bool DSManager::IsDevice(int id)
{
	if (!dsDevice[id]) return false;
	bool device = dsDevice[id]->IsDSDevice();
	if (!device)
	{
		dsDevice[id]->Destroy();
		delete dsDevice[id];
		dsDevice[id] = nullptr;
	}
	return device;
}

void DSManager::ChangeColor(int id, const UCHAR r, const UCHAR g, const UCHAR b)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->ChangeLedColor(LED(r, g, b));
}

void DSManager::ChangePlayerLight(int id, const UCHAR val)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->ChangePlayerLight(val);
}

void DSManager::ChangeVibration(int id, UCHAR right, UCHAR left)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->ChangeVibration(right, left);
}

void DSManager::ChangeTriggerLock(int id, UCHAR rMode, UCHAR right, UCHAR lMode, UCHAR left)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->ChangeTriggerLock(rMode, right, lMode, left);
}

void DSManager::SendOutput(int id)
{
	if (!IsDevice(id)) return;
	dsDevice[id]->SendOutputReport();
}

void DSManager::InputUpdate()
{
	for (int i = 0; i < 4; i++)
	{
		if (dsDevice[i] == nullptr) continue;
		if (dsDevice[i]->IsDSDevice() == false) { continue; }
		dsDevice[i]->GetInputReport();
	}
}

bool DSManager::GetButton(int id, UCHAR key)
{
	if (IsDevice(id) == false) return false;
	return dsDevice[id]->GetButton(key);
}

bool DSManager::GetButtonDown(int id, UCHAR key)
{
	if (IsDevice(id) == false) return false;
	return dsDevice[id]->GetButtonDown(key);
}

bool DSManager::GetButtonUp(int id, UCHAR key)
{
	if (IsDevice(id) == false) return false;
	return dsDevice[id]->GetButtonUp(key);
}

float DSManager::GetAxis(int id, UCHAR axis)
{
	if (IsDevice(id) == false) return 0;
	return dsDevice[id]->GetAxis(axis);
}

void DSManager::Destroy()
{
	for (int i = 0; i < 4; i++)
	{
		if (dsDevice[i]) {
			dsDevice[i]->Destroy();
			dsDevice[i] = nullptr;
		}
	}
}
