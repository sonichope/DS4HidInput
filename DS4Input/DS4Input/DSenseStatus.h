#pragma once
#include "DSenseButton.h"
struct DSenseStatus
{
	DSenseStatus();
	union
	{
		struct
		{
			DSenseButton square;
			DSenseButton cross;
			DSenseButton circle;
			DSenseButton triangle;
			DSenseButton up;
			DSenseButton right;
			DSenseButton down;
			DSenseButton left;
			DSenseButton l1;
			DSenseButton r1;
			DSenseButton share;
			DSenseButton option;
			DSenseButton l3;
			DSenseButton r3;
			DSenseButton home;
		};
		struct
		{
			DSenseButton data[15];
		};
	};
	
	float l2;
	float r2;
	float rightStickX;
	float rightStickY;
	float leftStickX;
	float leftStickY;
};

