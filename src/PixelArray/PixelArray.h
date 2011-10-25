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

using namespace std;

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
	PixelArray(int, int, pixel*);

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
	pixel* get(int, int);

	/*!
	 * Set a pixel object to a specific row and column in the PixelArray
	 *
	 * @param row The row position of the pixel data
	 * @param col The column position of the requested pixel data
	 * @param p The pixel data to set
	 */
	void set(int, int, pixel*);

	/*!
	 * Set the empty pixel data.
	 *
	 * @param new_empty The empty pixel data
	 */
	void setEmpty(pixel*);

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

	/*!
	 * Number of pixel rows in the bitmap
	 */
	int rows;

	/*!
	 * Number of columns of data per row
	 */
	int columns;

	/*!
	 * The length of the packed pixel array.
	 */
	int packed_array_length;

private:
	//Space at the end of every row that needs to be packed with
	//empty pixels.
	int row_padding;

	//pointer for a character array used to return packed pixel data
	char *packed_pixel_array;

	//flag to tell if the pixel array data has been packed.
	bool pixel_array_is_packed;

	//the default empty pixel data.
	pixel *empty;

	//pixel data array
	std::vector<pixel*> pixel_data_array;

	/*
	 * calculate the pixel_data_array row and column position
	 * based on a passed index.
	 * Return pair: first = row, second = column
	 */
	pair<int,int> calc_pixel_coords_by_packed_index(int);

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

	//de-initialize the pixel data array.
	//delete all pixel objects and clear the vector
	void un_init_pixel_data_array();

	//calculate the contents of the offsets vector
	void calculate_offsets();
};

#endif /* PIXELARRAY_H_ */
