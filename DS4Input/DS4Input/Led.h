#pragma once

struct LED
{
	LED(unsigned char red, unsigned char green, unsigned char blue);
	char red;
	char green;
	char blue;
	static LED Red();
	static LED Blue();
	static LED Green();
	static LED Purple();
};
