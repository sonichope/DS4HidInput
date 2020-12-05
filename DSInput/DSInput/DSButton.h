#pragma once
#include "DSButtonStatus.h"

typedef int BOOL;

struct DSButton
{
	DSButtonStatus status;

	DSButton() noexcept;
	void ChangeStatus(BOOL isButtonDown) noexcept;
};