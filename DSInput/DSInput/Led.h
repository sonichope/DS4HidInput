#pragma once

typedef unsigned char uchar;
typedef unsigned int uint;

struct LED
{
	union
	{
		struct
		{
			uchar blue;
			uchar green;
			uchar red;
		};
		uint ui;
	};
	LED(uchar red, uchar green, uchar blue) noexcept;
	explicit LED(uint ui) noexcept;
	static LED Red() noexcept;
	static LED Blue() noexcept;
	static LED Green() noexcept;
	static LED Purple() noexcept;
};
