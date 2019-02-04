#include "DS4Button.h"

DS4Button::DS4Button()
{
	status = DS4ButtonStatus::None;
}

DS4Button::DS4Button(bool isButtonDown)
{
	ChangeStatus(isButtonDown);
}

void DS4Button::ChangeStatus(bool isButtonDown)
{
	if (isButtonDown == true)
	{
		if (status == DS4ButtonStatus::None)
		{
			status = DS4ButtonStatus::Push;
			return;
		}

		if (status == DS4ButtonStatus::Push)
		{
			status = DS4ButtonStatus::Pushing;
			return;
		}

		if (status == DS4ButtonStatus::UnPush)
		{
			status = DS4ButtonStatus::Push;
		}
		return;
	}

	if (isButtonDown == false)
	{
		if (status == DS4ButtonStatus::Push)
		{
			status = DS4ButtonStatus::UnPush;
			return;
		}

		if (status == DS4ButtonStatus::Pushing)
		{
			status = DS4ButtonStatus::UnPush;
			return;
		}

		if (status == DS4ButtonStatus::UnPush)
		{
			status = DS4ButtonStatus::None;
		}
		return;
	}
}
