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

#include <iostream>
#include <stdio.h>
using namespace std;

/* PUBLIC */
template <class pixeltype>
PixelArray<pixeltype>::PixelArray()
{
	rows = 0;
	columns = 0;

	row_padding = 0;
	packed_pixel_array = 0;
//	packed_array_length = 0;
	set_packed_array_length();
	pixel_array_is_packed = false;
}

template <class pixeltype>
PixelArray<pixeltype>::PixelArray(int height, int width, pixeltype empty)
{
	packed_pixel_array = 0;
	setEmpty(empty);
	Resize_PixelArray(height, width);
}

template <class pixeltype>
void PixelArray<pixeltype>::Resize_PixelArray(int height, int width)
{
	rows = height;
	columns = width;

	row_padding = 4-(columns % 4 == 0 ? 4 : columns % 4);
	if (packed_pixel_array != 0)
	{
		delete[] packed_pixel_array;
	}

	set_packed_array_length();
	packed_pixel_array = 0;
	pixel_array_is_packed = false;

	init_pixel_data_array();
	row_offsets.reserve(rows);
	calculate_offsets();
}

template <class pixeltype>
int PixelArray<pixeltype>::Rows()
{
	return rows;
}

template <class pixeltype>
int PixelArray<pixeltype>::Columns()
{
	return columns;
}

template <class pixeltype>
int PixelArray<pixeltype>::Packed_Array_Length()
{
	return packed_array_length;
}

template <class pixeltype>
pixeltype PixelArray<pixeltype>::get(int row, int col)
{
	return pixel_data_array[get_pixel_position(row, col)];
}

template <class pixeltype>
void PixelArray<pixeltype>::set(int row, int col, pixeltype p)
{
	pixel_data_array[get_pixel_position(row, col)] = p;
	pixel_array_is_packed = false;
}

template <class pixeltype>
void PixelArray<pixeltype>::setEmpty(pixeltype new_empty)
{
	empty = new_empty;
	pixel_array_is_packed = false;
}

template <class pixeltype>
pixeltype PixelArray<pixeltype>::getEmpty()
{
	return empty;
}

template <class pixeltype>
char* PixelArray<pixeltype>::pack_pixel_array()
{
	if (!pixel_array_is_packed)
	{
		int pixel_len = empty.write_length;
		char *packed_pixel = 0;

		packed_pixel_array = new char[packed_array_length];

		std::pair<int,int> coords;
		int row, col;

//		char err_buff[200];

		for (int packed_i = 0; packed_i < packed_array_length; packed_i += pixel_len)
		{
			coords = calc_pixel_coords_by_packed_index(packed_i);
			row = coords.first;
			col = coords.second;

			packed_pixel = col < columns ? get(row, col).pack_pixel() : empty.pack_pixel();

//			for (int x = 0; x < 200; x++) err_buff[x] = 0;
//			for (int x = 0; x < empty.write_length; x++)
//			{
//				sprintf(err_buff, "Pixel %d: %s", packed_i, packed_pixel);
//				cout << err_buff << endl;
//			}

			move_data_into_packed_array(packed_pixel, packed_i, pixel_len);
		}

		pixel_array_is_packed = true;
	}
	return packed_pixel_array;
}

template <class pixeltype>
PixelArray<pixeltype>::~PixelArray()
{
	if (packed_pixel_array != 0)
		delete[] packed_pixel_array;
}

/* PRIVATE */
template <class pixeltype>
void PixelArray<pixeltype>::set_packed_array_length()
{
	if (rows > 0 && columns > 0)
	{
		int pixel_len = empty.write_length;
		packed_array_length = (columns + row_padding) * rows * pixel_len;
	}
	else
	{
		packed_array_length = 0;
	}
}

template <class pixeltype>
std::pair<int,int> PixelArray<pixeltype>::calc_pixel_coords_by_packed_index(int pack_i)
{
	pack_i /= empty.write_length;
	int colSize = columns + row_padding;

	int row;

	if (pack_i < colSize) row = 0;
	else row = pack_i / colSize;

	int col = pack_i % colSize;

	std::pair<int,int> coords(row, col);

	return coords;
}

template <class pixeltype>
int PixelArray<pixeltype>::get_pixel_position(int row, int col)
{
	return row_offsets[row] + col;
}

template <class pixeltype>
void PixelArray<pixeltype>::init_pixel_data_array()
{
	int length = columns * rows;
	pixel_data_array.reserve(length);
	for (int i = 0; i < length; i++) pixel_data_array[i] = empty;
}

template <class pixeltype>
void PixelArray<pixeltype>::calculate_offsets()
{
	for (int offset = 0, rowCount = 0;
		rowCount < rows;
		offset = rowCount * columns, rowCount++)
		row_offsets[rowCount] = offset;
}

template <class pixeltype>
void PixelArray<pixeltype>::move_data_into_packed_array(char *data, int packed_i, int pixel_len)
{
	for (int i = 0; i < pixel_len; i++)
		packed_pixel_array[packed_i + i] = data[i];
}

/*
 * Includes intended for explicit instantiations
 */
#include "Pixel_24.h"

/*
 * Explicitly instantiated pixel24-based PixelArray
 */
template class PixelArray<pixel24>;
