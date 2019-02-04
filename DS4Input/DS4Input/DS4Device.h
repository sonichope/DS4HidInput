#pragma once
#include "HidDevice.h"
#include "Led.h"
#include "DS4KeyType.h"
#include "DS4AxisType.h"
#include "DS4Status.h"

class DS4Device
{
public:
	DS4Device Create(HidDevice device, int controllerId);
	bool SendOutputReport();
	bool ChangeLedColor(LED led);
	void ChangeVibration(UCHAR right, UCHAR left);
	bool GetInputReport();
	bool Destroy();
	bool IsDS4Device();
	bool GetButton(DS4KeyType keyType);
	bool GetButtonDown(DS4KeyType keyType);
	bool GetButtonUp(DS4KeyType keyType);
	float GetAxis(DS4AxisType axisType);

private:
	HidDevice device;
	USHORT inputDataLength;
	USHORT outputDataLength;
	UCHAR outputData[32];
	UCHAR inputData[64];
	DS4Status status;
	int controllerNum;
};