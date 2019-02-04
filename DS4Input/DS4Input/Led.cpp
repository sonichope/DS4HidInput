#include "Led.h"

LED::LED(unsigned char red, unsigned char green, unsigned char blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

LED LED::Red()
{
	return LED(0xFF,0x00,0x00);
}

LED LED::Blue()
{
	return LED(0x00, 0x00, 0xFF);
}

LED LED::Green()
{
	return LED(0x00, 0xFF, 0x00);
}

LED LED::Purple()
{
	return LED(0xFF, 0x00, 0xFF);
}
