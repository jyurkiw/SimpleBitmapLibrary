/*
 * PixelArray.cpp
 *
 *  Created on: 2011-10-16
 *  @author master
 *  @version 0.1
 */
#include "PixelArray.h"
#include <utility>
#include <vector>

/* PUBLIC */
PixelArray::PixelArray()
{
	rows = 0;
	columns = 0;

	row_padding = 0;
	packed_pixel_array = 0;
	packed_array_length = 0;
	empty = 0;
	pixel_array_is_packed = false;
}

PixelArray::PixelArray(int height, int width, pixel *empty)
{
	Resize_PixelArray(height, width);
	setEmpty(empty);
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
	pixel_array_is_packed = false;

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
	pixel_array_is_packed = false;
}

void PixelArray::setEmpty(pixel *new_empty)
{
	empty = new_empty;
	pixel_array_is_packed = false;
}

char* PixelArray::pack_pixel_array()
{
	if (!pixel_array_is_packed)
	{
		int pixel_len = empty->write_length;
		char *packed_pixel = 0;

		packed_array_length = (columns + row_padding) * rows * pixel_len;
		packed_pixel_array = new char[packed_array_length];

		pair<int,int> coords;
		int row, col;

		for (int packed_i = 0; packed_i < packed_array_length; packed_i += pixel_len)
		{
			coords = calc_pixel_coords_by_packed_index(packed_i);
			row = coords.first;
			col = coords.second;

			packed_pixel = col < columns ? get(row, col)->pack_pixel() : empty->pack_pixel();

			move_data_into_packed_array(packed_pixel, packed_i, pixel_len);
		}

		pixel_array_is_packed = true;
	}
	return packed_pixel_array;
}

PixelArray::~PixelArray()
{
	if (packed_pixel_array != 0)
		delete[] packed_pixel_array;
	un_init_pixel_data_array();
}

/* PRIVATE */
pair<int,int> PixelArray::calc_pixel_coords_by_packed_index(int pack_i)
{
	pair<int,int> coords(pack_i / (columns + row_padding),
			pack_i % (columns + row_padding));

	return coords;
}

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

void PixelArray::un_init_pixel_data_array()
{
	for (int i = 0, si = pixel_data_array.size(); i < si; i++)
		if (pixel_data_array[i] != 0) delete pixel_data_array[i];
	pixel_data_array.clear();
}

void PixelArray::calculate_offsets()
{
	for (int offset = 0, rowCount = 0;
		rowCount < rows;
		offset = rowCount * columns, rowCount++)
		row_offsets[rowCount] = offset;
}

void PixelArray::move_data_into_packed_array(char *data, int packed_i, int pixel_len)
{
	for (int i = 0; i < pixel_len; i++)
		packed_pixel_array[packed_i + i] = data[i];
}
