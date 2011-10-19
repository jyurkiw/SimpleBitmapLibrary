/*
 * PixelArray.cpp
 *
 *  Created on: 2011-10-16
 *  @author master
 *  @version 0.1
 */
#include "PixelArray.h"

/* PUBLIC */
PixelArray::PixelArray()
{
	rows = 0;
	columns = 0;

	row_padding = 0;
	packed_pixel_array = 0;
	packed_array_length = 0;
}

PixelArray::PixelArray(int height, int width)
{
	Resize_PixelArray(height, width);
}

void PixelArray::Resize_PixelArray(int height, int width)
{
	rows = height;
	columns = width;

	row_padding = columns % 4;
	if (packed_pixel_array != 0)
	{
		delete[] packed_pixel_array;
	}

	packed_array_length = 0;
	packed_pixel_array = 0;

	init_pixel_data_array();
	row_offsets.reserve(rows);
}

pixel* PixelArray::get(int row, int col)
{
	return pixel_data_array[get_pixel_position(row, col)];
}

void PixelArray::set(int row, int col, pixel *p)
{
	*pixel_data_array[get_pixel_position(row, col)] = *p;
}

char* PixelArray::pack_pixel_array(pixel *empty)
{
	int pixel_len = empty->write_length;
	char *packed_pixel = 0;

	packed_array_length = (columns + row_padding) * rows * pixel_len;
	packed_pixel_array = new char[packed_array_length];

	int packed_array_i;
	int bmp_i = 0;
	int px_i;
	int current_row = 0;
	int current_column;

	while(current_row < rows)
	{
		current_column = 0;
		do
		{
			packed_array_i = get_pixel_position(current_row, current_column);
			if (pixel_data_array[packed_array_i] != 0)
				packed_pixel = pixel_data_array[packed_array_i]->pack_pixel();
			else
				packed_pixel = empty->pack_pixel();

			px_i = 0;
			do
			{
				if (bmp_i < packed_array_length)
					packed_pixel_array[bmp_i] = packed_pixel[px_i];
				px_i++;
				bmp_i++;
			} while (px_i < pixel_len);
		} while (current_column < columns);

	}

	delete[] packed_pixel;

	return packed_pixel_array;
}

PixelArray::~PixelArray()
{
	if (packed_pixel_array != 0)
		delete[] packed_pixel_array;
}

/* PRIVATE */
int PixelArray::get_pixel_position(int row, int col)
{
	return row_offsets[row] + col;
}

void PixelArray::init_pixel_data_array()
{
	int length = columns * rows;
	pixel_data_array.reserve(length);
	for (int i = 0; i < length; i++) pixel_data_array[i] = 0;
}

void PixelArray::calculate_offsets()
{
	for (int offset = 0, rowCount = 0;
		rowCount < rows;
		offset = rowCount * columns, rowCount++)
		row_offsets[rowCount] = offset;
}
