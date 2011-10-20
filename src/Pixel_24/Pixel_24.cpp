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
	this->blue = rhs.blue;
	this->green = rhs.green;
	this->red = rhs.red;

	return *this;
}

bool PixelData_24_Bit::operator ==(const pixel24 &rhs)
{
	return (this->blue == rhs.blue) && (this->green == rhs.green) && (this->red == rhs.red);
}

bool PixelData_24_Bit::operator !=(const pixel24 &rhs)
{
	return !(*this == rhs);
}

char* PixelData_24_Bit::pack_pixel()
{
	if (!is_packed)
	{
		packed_pixel_data[0] = blue;
		packed_pixel_data[1] = green;
		packed_pixel_data[2] = red;
		is_packed = true;
	}

	return packed_pixel_data;
}

void PixelData_24_Bit::repack_pixel()
{
	is_packed = false;
}

void PixelData_24_Bit::set(char blue, char green, char red)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}
