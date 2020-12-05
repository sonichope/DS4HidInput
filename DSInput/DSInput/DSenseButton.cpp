#include "DSenseButton.h"

DSenseButton::DSenseButton()
{
	status = DSButtonStatus::None;
}

void DSenseButton::ChangeStatus(BOOL isButtonDown) noexcept
{
	if (isButtonDown)
	{
		if (status == DSButtonStatus::None)
		{
			status = DSButtonStatus::Push;
			return;
		}

		if (status == DSButtonStatus::Push)
		{
			status = DSButtonStatus::Pushing;
			return;
		}

		if (status == DSButtonStatus::UnPush)
		{
			status = DSButtonStatus::Push;
			return;
		}

	}
	else
	{
		if (status == DSButtonStatus::Push)
		{
			status = DSButtonStatus::UnPush;
			return;
		}

		if (status == DSButtonStatus::Pushing)
		{
			status = DSButtonStatus::UnPush;
			return;
		}

		if (status == DSButtonStatus::UnPush)
		{
			status = DSButtonStatus::None;
			return;
		}
	}
}