/*
 * FileHeader.cpp
 *
 *  Created on: 2012-01-07
 *  @author: master
 *  @version: 0.1
 */
#import "BitmapFileHeader.h"
#import "../MemoryBlockFactory.h"
#import "HeaderMagic.h"
#include <boost/cstdint.hpp>

BitmapFile_Header::BitmapFile_Header()
{
	header_length = 2 + sizeof(filesize)
			+ sizeof(creator1)
			+ sizeof(creator2)
			+ sizeof(bmp_offset);

	header = new char[header_length];

	filesize = 0;
	creator1 = 0;
	creator2 = 0;
	bmp_offset = 0;
}

BitmapFile_Header::~BitmapFile_Header()
{
	delete[] header;
}

void BitmapFile_Header::build_header(BitmapHeader_Magic *magic)
{
	memblock m;
	int index = 2;

	/*!
	 * Simple execution.
	 * Set the memory block to the target variable.
	 * Merge the translated data into the header string.
	 * Increment the index by the size of the variable.
	 * Because we start writing at 0 but start incrementing at 1
	 * adding the size of the variable gives us the starting point
	 * of the next write sequence.
	 */

	header[0] = magic.magic[0];
	header[1] = magic.magic[1];

	//filesize
	m.set_memoryblock_handle<uint32_t>(filesize);
	index += m.merge_memoryblock_into_string(header, header_length);

	//creator1
	m.set_memoryblock_handle<uint16_t>(creator1);
	index += m.merge_memoryblock_into_string(header, header_length, index);

	//creator2
	m.set_memoryblock_handle<uint16_t>(creator2);
	index += m.merge_memoryblock_into_string(header, header_length, index);

	//bmp_offset
	m.set_memoryblock_handle<uint32_t>(filesize);
	m.merge_memoryblock_into_string(header, header_length, index);
}
