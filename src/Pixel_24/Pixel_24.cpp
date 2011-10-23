/*
 * Pixel_24.cpp
 *
 *  Created on: 2011-10-16
 *  @author: master
 *  @version 0.1
 */

#include "Pixel_24.h"
#include "PixelData.h"
#include <memory>

pixel24& PixelData_24_Bit::operator =(const pixel24 &rhs)
{
	blue(rhs.blue());
	green(rhs.green());
	red(rhs.red());

	return *this;
}

bool PixelData_24_Bit::operator ==(const pixel24 &rhs)
{
	return (v_blue == rhs.blue()) && (v_green == rhs.green()) && (v_red == rhs.red());
}

bool PixelData_24_Bit::operator !=(const pixel24 &rhs)
{
	return !(*this == rhs);
}

char* PixelData_24_Bit::pack_pixel()
{
	if (!is_packed)
	{
		packed_pixel_data[0] = v_blue;
		packed_pixel_data[1] = v_green;
		packed_pixel_data[2] = v_red;
		is_packed = true;
	}

	return packed_pixel_data;
}

void PixelData_24_Bit::set(char blue, char green, char red)
{
	this->v_blue = blue;
	this->v_green = green;
	this->v_red = red;
	is_packed = false;
}

void PixelData_24_Bit::blue(char value)
{
	v_blue = value;
	is_packed = false;
}

void PixelData_24_Bit::green(char value)
{
	v_green = value;
	is_packed = false;
}

void PixelData_24_Bit::red(char value)
{
	v_red = value;
	is_packed = false;
}

char PixelData_24_Bit::blue() const
{
	return v_blue;
}

char PixelData_24_Bit::green() const
{
	return v_green;
}

char PixelData_24_Bit::red() const
{
	return v_red;
}
