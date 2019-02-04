#pragma once
#include "DS4ButtonStatus.h"

struct DS4Button
{
	DS4ButtonStatus status;

	DS4Button();
	DS4Button(bool isButtonDown);
	void ChangeStatus(bool isButtonDown);

};