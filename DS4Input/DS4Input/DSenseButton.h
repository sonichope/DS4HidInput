#pragma once
#include "DS4ButtonStatus.h"

struct DSenseButton
{
	DSButtonStatus status;

	DSenseButton();
	DSenseButton(bool isButtonDown);
	void ChangeStatus(bool isButtonDown);
};

