#pragma once
#include "DS4Device.h"

class DS4Manager
{
public:
	void GetDevice();
	bool IsDevice(int id);
	void ChangeColor(int id, const UCHAR r, const UCHAR g, const UCHAR b);
	void ChangeVibration(int id, UCHAR right, UCHAR left);
	void SendOutput(int id);
	void InputUpdate();
	bool GetButton(int id, DS4KeyType key);
	bool GetButtonDown(int id, DS4KeyType key);
	bool GetButtonUp(int id, DS4KeyType key);
	float GetAxis(int id, DS4AxisType axis);
	void Destroy();

private:
	DS4Device ds4Device[4];
	int connectionNum = 0;
};
