#pragma once
#include "HidDevice.h"
#include "Led.h"
#include "DS4KeyType.h"
#include "DS4AxisType.h"
#include "DS4Status.h"

class DS4Device
{
public:
	DS4Device();
	DS4Device Create(HidDevice device, int controllerId);
	bool SendOutputReport();
	bool ChangeLedColor(LED led) const;
	void ChangeVibration(UCHAR right, UCHAR left) const;
	bool GetInputReport();
	bool Destroy();
	bool IsDS4Device() const;
	bool GetButton(DS4KeyType keyType) const;
	bool GetButtonDown(DS4KeyType keyType) const;
	bool GetButtonUp(DS4KeyType keyType) const;
	float GetAxis(DS4AxisType axisType) const;

private:
	HidDevice device;
	USHORT inputDataLength;
	USHORT outputDataLength;
	UCHAR* outputData = nullptr;
	UCHAR* inputData = nullptr;
	DS4Status status;
	int controllerNum;
};