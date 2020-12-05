#pragma once
#include "DSDevice.h"
#include "DSStatus.h"

class DSenseDevice : public DSDevice
{
public:
	DSenseDevice(HidDevice device, int controllerId);
	bool ChangeLedColor(const LED& led) noexcept override;
	void ChangePlayerLight(UCHAR val) override;
	bool SendOutputReport() override;
	void ChangeVibration(UCHAR right, UCHAR left) override;
	void ChangeTriggerLock(UCHAR rMode, UCHAR right, UCHAR lMode, UCHAR left) override;
	bool GetInputReport() override;
	bool Destroy() override;
	inline bool IsDSDevice() override
	{
		return device.isDevice;
	}
	bool GetButton(UCHAR keyType) override;
	bool GetButtonDown(UCHAR keyType) override;
	bool GetButtonUp(UCHAR keyType) override;
	float GetAxis(UCHAR axisType) override;
	void Reset() noexcept override;

private:
	HidDevice device;
	USHORT inputDataLength;
	USHORT outputDataLength;
	UCHAR outputData[48];
	UCHAR inputData[64];
	DSStatus status;
	int controllerId = -1;
};