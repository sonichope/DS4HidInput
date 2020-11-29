#pragma once
#include "DS4Button.h"

struct DS4Status
{
	DS4Status();
	union
	{
		struct
		{
			DS4Button square;
			DS4Button cross;
			DS4Button circle;
			DS4Button triangle;
			DS4Button up;
			DS4Button right;
			DS4Button down;
			DS4Button left;
			DS4Button l1;
			DS4Button r1;
			DS4Button share;
			DS4Button option;
			DS4Button l3;
			DS4Button r3;
		};

		struct
		{
			DS4Button data[14];
		};
	};

	float l2{};
	float r2{};
	float rightStickX{};
	float rightStickY{};
	float leftStickX{};
	float leftStickY{};
};

inline DS4Status::DS4Status() = default;
