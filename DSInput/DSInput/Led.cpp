#include "Led.h"

LED::LED(uchar red, uchar green, uchar blue) noexcept : red( red), green( green), blue(blue)
{
}

LED::LED(uint ui) noexcept : ui( ui)
{
}

LED LED::Red() noexcept
{
	static LED red(0xff000000);
	return red;
}

LED LED::Blue() noexcept
{
	static LED blue(0x0000ff00);
	return blue;
}

LED LED::Green() noexcept
{
	static LED green(0x00ff0000);
	return green;
}

LED LED::Purple() noexcept
{
	static LED purple(0xff00ff00);
	return purple;

}
