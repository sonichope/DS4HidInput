#pragma once
#include "DSDevice.h"

class DS4Manager
{
public:
	DS4Manager();
	void GetDevice();
	bool IsDevice(int id);
	void ChangeColor(int id, const UCHAR r, const UCHAR g, const UCHAR b);
	void ChangePlayerLight(int id, const UCHAR val);
	void ChangeVibration(int id, UCHAR right, UCHAR left);
	void ChangeTriggerLock(int id, UCHAR rMode, UCHAR right, UCHAR lMode, UCHAR left);
	void SendOutput(int id);
	void InputUpdate();
	bool GetButton(int id, UCHAR key);
	bool GetButtonDown(int id, UCHAR key);
	bool GetButtonUp(int id, UCHAR key);
	float GetAxis(int id, UCHAR axis);
	void Destroy();

private:
	DSDevice* dsDevice[4];
};
