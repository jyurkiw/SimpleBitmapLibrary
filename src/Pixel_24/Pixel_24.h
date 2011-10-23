/*
 * pixel_24.h
 *
 *  Created on: 2011-10-16
 *  @author master
 *  @version 0.1
 */

#ifndef PIXEL_24_H_
#define PIXEL_24_H_

#include "PixelData.h"
#include <memory>

/*!
 * Represents a single 24-bit pixel
 */
class PixelData_24_Bit: public pixel
{
public:


	/*!
	 * Empty constructor. Defaults red, green, and blue to 0x00, and
	 * write_length to 24.
	 */
	PixelData_24_Bit(): PixelData(3), blue(0x00), green(0x00), red(0x00),
			is_packed(false) { }

	/*!
	 * Constructor. Defaults red, green, and blue to passed values and
	 * write_length to 24.
	 */
	PixelData_24_Bit(char b, char g, char r): PixelData(3), blue(b), green(g),
			red(r), is_packed(false) { }

	/*!
	 * Set this pixel24 equal to another pixel24.
	 *
	 * @param rhs The right hand side of the equality.
	 * @return This pixel24.
	 */
	PixelData_24_Bit& operator = (const PixelData_24_Bit&);

	/*!
	 * Determine if this pixel24 is equal to another pixel24.
	 *
	 * @param rhs The right hand side of the equality.
	 * @return True if they are the same. False otherwise.
	 */
	bool operator == (const PixelData_24_Bit&);

	/*!
	 * Determine if this pixel24 is not equal to another pixel24.
	 *
	 * @param rhs The right hand side of the equality.
	 * @return True if they are not the same. False otherwise.
	 */
	bool operator != (const PixelData_24_Bit&);

	/*!
	 * Implimentation of required pack_pixel() function.
	 *
	 * Packs the pixel data into a char array and returns it.
	 * 24-bit pixel data is contained in 3 bytes so
	 * the return array is 3 chars long (blue, green, red).
	 */
	char* pack_pixel();

	/*!
	 * Set the color data of the pixel.
	 *
	 * @param red The red value of the pixel in hex.
	 * @param green The green value of the pixel in hex.
	 * @param blue The blue value of the pixel in hex.
	 */
	void set(char, char, char);

	/*!
	 * Set the blue value of the pixel.
	 *
	 * @param value The blue value to set
	 */
	void blue(char);

	/*!
	 * Set the green value of the pixel.
	 *
	 * @param value The green value to set
	 */
	void green(char);

	/*!
	 * Set the red value of the pixel.
	 *
	 * @param value The red value to set
	 */
	void red(char);

	/*!
	 * Get the blue value of the pixel.
	 *
	 * @return The blue value of the pixel
	 */
	char blue();

	/*!
	 * Get the green value of the pixel.
	 *
	 * @return The green value of the pixel
	 */
	char green();

	/*!
	 * Get the red value of the pixel.
	 *
	 * @return The red value of the pixel
	 */
	char red();

private:
	char v_blue;
	char v_green;
	char v_red;
	char packed_pixel_data[3];
	bool is_packed;
};

typedef PixelData_24_Bit pixel24;

#endif /* PIXEL_24_H_ */
