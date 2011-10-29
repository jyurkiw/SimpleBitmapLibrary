/*
 * PixelArray.h
 *
 *  Created on: 2011-10-16
 *  @author master
 *  @version 0.1
 */
#ifndef PIXELARRAY_H_
#define PIXELARRAY_H_

#include <vector>
#include <utility>
#include "PixelData.h"

/*!
 * Pixel container class.
 * Instantiation is declared Explicitly in PixelArray.cpp
 *
 * PixelArray can be used with the following instantiations...
 * -# PixelArray<PixelData_24_Bit> (Pixel_24.h)
 */
template <class pixeltype>
class PixelArray
{
public:
	/*!
	 * Empty constructor for STL support
	 */
	PixelArray();

	/*!
	 * Make a new PixelArray with a set height and width.
	 *
	 * @param height The height of the bitmap in pixels
	 * @param width The width of the bitmap in pixels
	 * @param empty The array's default empty pixel data
	 */
	PixelArray(int, int, pixeltype*);

	/*!
	 * Get the number of rows in the bitmap. Does not count padding.
	 *
	 * @return The number of rows of pixel data
	 */
	int Rows();

	/*!
	 * Get the number of columns in the bitmap.
	 *
	 * @return The number of columns of pixel data
	 */
	int Columns();

	/*!
	 * Return the length of the fully packed pixel array (char array).
	 * Includes empty pixel data used for padding.
	 *
	 * @return The length of the pixel data array.
	 */
	int Packed_Array_Length();

	/*!
	 * Resize the PixelArray to a new size.
	 *
	 * @param height The height of the bitmap in pixels
	 * @param width The width of the bitmap in pixels
	 */
	void Resize_PixelArray(int, int);

	/*!
	 * Returns the a pixel object at a passed coordinate.
	 *
	 * @param row The row position of the requested pixel
	 * @param col The column position of the requested pixel
	 * @return The pixel at row x col
	 */
	pixeltype* get(int, int);

	/*!
	 * Set a pixel object to a specific row and column in the PixelArray
	 *
	 * @param row The row position of the pixel data
	 * @param col The column position of the requested pixel data
	 * @param p The pixel data to set
	 */
	void set(int, int, pixeltype*);

	/*!
	 * Set the empty pixel data.
	 *
	 * @param new_empty The empty pixel data
	 */
	void setEmpty(pixeltype*);

	/*!
	 * Pack and return the Pixel Array data
	 *
	 * @return The packed pixel array
	 */
	char* pack_pixel_array();

	/*!
	 * Destroys packed_pixel_array.
	 */
	~PixelArray();

private:
	/*
	 * Number of pixel rows in the bitmap
	 */
	int rows;

	/*
	 * Number of columns of data per row
	 */
	int columns;

	/*
	 * The length of the packed pixel array.
	 */
	int packed_array_length;

	//Space at the end of every row that needs to be packed with
	//empty pixels.
	int row_padding;

	//pointer for a character array used to return packed pixel data
	char *packed_pixel_array;

	//flag to tell if the pixel array data has been packed.
	bool pixel_array_is_packed;

	//the default empty pixel data.
	pixeltype *empty;

	//pixel data array
	std::vector<pixeltype> pixel_data_array;

	/*
	 * calculate the pixel_data_array row and column position
	 * based on a passed index.
	 * Return pair: first = row, second = column
	 */
	std::pair<int,int> calc_pixel_coords_by_packed_index(int);

	/*
	 * move the character data from one array to another
	 * based on the passed index
	 */
	void move_data_into_packed_array(char*, int, int);

	//vector that stores pre-calculated offset data for accessing pixel data
	std::vector<int> row_offsets;

	//Get the position of a pixel in the data array based on it's
	//cartesian coordinates.
	//int height/row, int width/column
	int get_pixel_position(int, int);

	//initialize the pixel data array to zeros
	void init_pixel_data_array();

	//calculate the contents of the offsets vector
	void calculate_offsets();
};

#endif /* PIXELARRAY_H_ */
