#include "DS4Button.h"

DS4Button::DS4Button()
{
	status = None;
}

DS4Button::DS4Button(const bool isButtonDown)
{
	ChangeStatus(isButtonDown);
}

void DS4Button::ChangeStatus(const bool isButtonDown)
{
	if (isButtonDown)
	{
		if (status == None)
		{
			status = Push;
			return;
		}

		if (status == Push)
		{
			status = Pushing;
			return;
		}

		if (status == UnPush)
		{
			status = Push;
		}
		return;
	}

	if (!isButtonDown)
	{
		if (status == Push)
		{
			status = UnPush;
			return;
		}

		if (status == Pushing)
		{
			status = UnPush;
			return;
		}

		if (status == UnPush)
		{
			status = None;
		}
		return;
	}
}
