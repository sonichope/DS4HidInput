#pragma once
#include "DSDevice.h"
#include "DSenseStatus.h"

class DSenseDevice : public DSDevice
{
public:
	DSenseDevice(HidDevice device, int controllerId);
	bool ChangeLedColor(LED led);
	void ChangePlayerLight(UCHAR val) override;
	bool SendOutputReport() override;
	void ChangeVibration(UCHAR right, UCHAR left) override;
	bool GetInputReport() override;
	bool Destroy() override;
	bool IsDSDevice() override;
	bool GetButton(UCHAR keyType) override;
	bool GetButtonDown(UCHAR keyType) override;
	bool GetButtonUp(UCHAR keyType) override;
	float GetAxis(UCHAR axisType) override;

private:
	HidDevice device;
	USHORT inputDataLength;
	USHORT outputDataLength;
	UCHAR outputData[48];
	UCHAR inputData[64];
	DSenseStatus status;
	int controllerNum;
};

