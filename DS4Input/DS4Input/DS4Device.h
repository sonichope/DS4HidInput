#pragma once
#include "DSDevice.h"
#include "DS4Status.h"

class DS4Device : public DSDevice
{
public:
	DS4Device(HidDevice device, int controllerId);
	bool SendOutputReport() override;
	bool ChangeLedColor(LED led) override;
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
	UCHAR* outputData = nullptr;
	UCHAR* inputData = nullptr;
	DS4Status status;
	int controllerNum = -1;
};