#pragma once
#include "DSButtonStatus.h"

typedef int BOOL;

struct DSenseButton
{
	DSButtonStatus status;

	DSenseButton();
	void ChangeStatus(BOOL isButtonDown) noexcept;
};

