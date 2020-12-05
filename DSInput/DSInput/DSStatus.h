#pragma once
#include "DSButton.h"

struct DSStatus
{
	DSStatus() noexcept {};
	union
	{
		struct
		{
			DSButton square;
			DSButton cross;
			DSButton circle;
			DSButton triangle;
			DSButton up;
			DSButton right;
			DSButton down;
			DSButton left;
			DSButton l1;
			DSButton r1;
			DSButton share;
			DSButton option;
			DSButton l3;
			DSButton r3;
			DSButton home;
		};

		DSButton data[15];
	};

	union {
		struct
		{
			float rightStickX;
			float rightStickY;
			float leftStickX;
			float leftStickY;
			float l2;
			float r2;
		};

		float axisVals[6];
	};
};