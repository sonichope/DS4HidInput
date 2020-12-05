#pragma once
#include "HidDevice.h"
#include "Led.h"

class DSDevice {
public:
	virtual bool SendOutputReport() = 0;
	virtual bool ChangeLedColor(const LED& led) noexcept = 0;
	virtual void ChangePlayerLight(UCHAR val) {};
	virtual void ChangeVibration(UCHAR right, UCHAR left) = 0;
	virtual void ChangeTriggerLock(UCHAR rMode, UCHAR right, UCHAR lMode, UCHAR left) {};
	virtual bool GetInputReport() = 0;
	virtual bool Destroy() = 0;
	virtual bool IsDSDevice() = 0;
	virtual bool GetButton(UCHAR keyType) = 0;
	virtual bool GetButtonDown(UCHAR keyType) = 0;
	virtual bool GetButtonUp(UCHAR keyType) = 0;
	virtual float GetAxis(UCHAR axisType) = 0;
	virtual void Reset() noexcept = 0;
};
