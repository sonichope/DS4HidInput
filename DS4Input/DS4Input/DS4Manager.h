#pragma once
#include "DS4Device.h"

class DS4Manager
{
public:
	DS4Manager();
	void GetDevice();
	bool IsDevice(int id) const;
	void ChangeColor(int id, const UCHAR r, const UCHAR g, const UCHAR b) const;
	void ChangeVibration(int id, UCHAR right, UCHAR left) const;
	void SendOutput(int id);
	void InputUpdate();
	bool GetButton(int id, DS4KeyType key) const;
	bool GetButtonDown(int id, DS4KeyType key) const;
	bool GetButtonUp(int id, DS4KeyType key) const;
	float GetAxis(int id, DS4AxisType axis) const;
	void Destroy();

private:
	DS4Device ds4Device[4];
	int connectionNum = 0;
};
