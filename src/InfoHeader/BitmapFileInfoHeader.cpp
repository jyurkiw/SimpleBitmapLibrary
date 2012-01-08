/*
 * BitmapInfoHeader.cpp
 *
 *  Created on: 2012-01-07
 *  @author: master
 *  @version: 0.1
 */
#import "BitmapFileInfoHeader.h"
#import "../MemoryBlockFactory.h"
#include <boost/cstdint.hpp>

BitmapFile_Infoheader::BitmapFile_Infoheader()
{
	header_size = sizeof(header_size)
			+ sizeof(width)
			+ sizeof(height)
			+ sizeof(planes)
			+ sizeof(bits_per_pixel)
			+ sizeof(compress_type)
			+ sizeof(image_data_size)
			+ sizeof(horizontal_resolution)
			+ sizeof(vertical_resolution)
			+ sizeof(colors_in_colortable)
			+ sizeof(important_color_count);

	width = 0;
	height = 0;
	planes = 1;
	bits_per_pixel = 0;
	compress_type = 0;
	image_data_size = 0;
	horizontal_resolution = 2835;
	vertical_resolution = 2835;
	colors_in_colortable = 0;
	important_color_count = 0;

	infoheader = new char[header_size];
}

BitmapFile_Infoheader::~BitmapFile_Infoheader()
{
	delete[] infoheader;
}

void BitmapFile_Infoheader::build_header()
{
	memblock m;
	int index = 0;

	m.set_memoryblock_handle<uint32_t>(header_size);
	index += m.merge_memoryblock_into_string(infoheader, header_size);

	m.set_memoryblock_handle<uint32_t>(width);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(height);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(planes);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(bits_per_pixel);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(compress_type);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(image_data_size);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(horizontal_resolution);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(vertical_resolution);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(colors_in_colortable);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);

	m.set_memoryblock_handle<uint32_t>(important_color_count);
	index += m.merge_memoryblock_into_string(infoheader, header_size, index);
}
