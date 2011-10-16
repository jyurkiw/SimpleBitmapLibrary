/*
 * bmp.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: master
 */
#include "bmp.h"
#include <boost/cstdint.hpp>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void Write_Memoryblock(std::ofstream *p_file, T block)
{
	int size = sizeof(block);
	char *memory_block = new char[size];

	for (int x = 0, shift = x*8; x < size; x++, shift = x*8)
		memory_block[x] = (block >> shift) & 0xff;

	p_file->write(memory_block, size);
	delete memory_block;
}

BMPFile_Header::BMPFile_Header()
{
	filesize = 0;
	creator1 = 0;
	creator2 = 0;
	bmp_offset = 0;
}

void BMPFile_Header::Write_Header(std::ofstream *p_file, BMPFile_Magic *p_magic)
{
	p_file->write(p_magic->magic, 2);

	//write filesize, creator 1, creator 2, and bmp_offset
	Write_Memoryblock <uint32_t> (p_file, filesize);
	Write_Memoryblock <uint16_t> (p_file, creator1);
	Write_Memoryblock <uint16_t> (p_file, creator2);
	Write_Memoryblock <uint32_t> (p_file, bmp_offset);
}

BMPFile_Magic::BMPFile_Magic()
{
	magic[0] = 'B';
	magic[1] = 'M';
}

BMPFile_Infoheader::BMPFile_Infoheader()
{
	header_size = 0;
	width = 0;
	height = 0;
	planes = 1;
	bits_per_pixel = 24;
	compress_type = 0;
	image_data_size = 0;
	horizontal_resolution = 2835;
	vertical_resolution = 2835;
	colors_in_colortable = 0;
	important_color_count = 0;
}

void BMPFile_Infoheader::Write_Header(std::ofstream *p_file)
{
	//write infoheader to the file in order they appear in the header file
	Write_Memoryblock <uint32_t> (p_file, header_size);
	Write_Memoryblock <int32_t> (p_file, width);
	Write_Memoryblock <int32_t> (p_file, height);
	Write_Memoryblock <uint16_t> (p_file, planes);
	Write_Memoryblock <uint16_t> (p_file, bits_per_pixel);
	Write_Memoryblock <uint32_t> (p_file, compress_type);
	Write_Memoryblock <uint32_t> (p_file, image_data_size);
	Write_Memoryblock <int32_t> (p_file, horizontal_resolution);
	Write_Memoryblock <int32_t> (p_file, vertical_resolution);
	Write_Memoryblock <uint32_t> (p_file, colors_in_colortable);
	Write_Memoryblock <uint32_t> (p_file, important_color_count);
}

BMPFile_24bit_PixelData::BMPFile_24bit_PixelData()
{
	blue = 0xff;
	green = 0xff;
	red = 0xff;
}

BMPFile_24bit_PixelData::BMPFile_24bit_PixelData(
		char pblue, char pgreen, char pred)
{
	blue = pblue;
	green = pgreen;
	red = pred;
}

//return the number of bytes written to the file so we
//can track row length for padding purposes (must be multiples of 4)
void BMPFile_24bit_PixelData::Write_PixelData(std::ofstream *p_file)
{
	p_file->write(&blue, 1);
	p_file->write(&green, 1);
	p_file->write(&red, 1);
}

BMPFile_24bit_PixelArray::BMPFile_24bit_PixelArray()
{
	row_padding = 0;
	rows = 0;
	columns = 0;
}

BMPFile_24bit_PixelArray::BMPFile_24bit_PixelArray(int height, int width)
{
	Reinitialize_PixelArray(height, width);
}

void BMPFile_24bit_PixelArray::Reinitialize_PixelArray(int height, int width)
{
	row_padding = width % 4;
	rows = height;
	columns = width;

	pixel_array.resize(height * width);

	row_offsets.resize(height);
	for(int x=0; x<height; x++) row_offsets[x]=x*width;
}

void BMPFile_24bit_PixelArray::Write_PixelData(std::ofstream *p_file)
{
	for(int i=rows-1;i>=0;i--)
	{
		for(int xa=row_offsets[i],x=0;x<columns;x++,xa++)
			pixel_array[xa].Write_PixelData(p_file);
		Write_RowPadding(p_file);
	}
}

BMPFile_24bit_PixelData& BMPFile_24bit_PixelData::operator =(const BMPFile_24bit_PixelData &rhs)
{
	this->blue = rhs.blue;
	this->green = rhs.green;
	this->red = rhs.red;

	return *this;
}

bool BMPFile_24bit_PixelData::operator ==(const BMPFile_24bit_PixelData &rhs)
{
	return (this->blue == rhs.blue) && (this->green == rhs.green) && (this->red == rhs.red);
}

bool BMPFile_24bit_PixelData::operator !=(const BMPFile_24bit_PixelData &rhs)
{
	return !(*this == rhs);
}

BMPFile_24bit_PixelData BMPFile_24bit_PixelArray::get(pair<int,int> rowCol)
{
	//return pixel_array.at(rowCol.first).at(rowCol.second);
	return pixel_array[getPosition(rowCol)];
}

void BMPFile_24bit_PixelArray::set(BMPFile_24bit_PixelData pixel, pair<int,int> rowCol)
{
	pixel_array[getPosition(rowCol)] = pixel;
}

void BMPFile_24bit_PixelArray::Write_RowPadding(ofstream *p_file)
{
	if (row_padding > 0)
	{
		char *datablock = new char[row_padding];

		for (int x = 0; x < row_padding; x++) datablock[x] = 0x00;

		p_file->write(datablock, row_padding);
		delete datablock;
	}
}

int BMPFile_24bit_PixelArray::getPosition(pair<int,int> rowCol)
{
	return rowCol.second + row_offsets[rowCol.first];
}

Bitmap_File_24bit::Bitmap_File_24bit(int p_height, int p_width)
{
	filename = "RenameMe.bmp";
	height = p_height;
	width = p_width;

	pixel_array.Reinitialize_PixelArray(height, width);
}

Bitmap_File_24bit::Bitmap_File_24bit(const string &p_filename, int p_height, int p_width)
{
	filename = p_filename;
	height = p_height;
	width = p_width;

	pixel_array.Reinitialize_PixelArray(height, width);
}

void Bitmap_File_24bit::Write_Bitmap()
{
	ofstream output_file;
	completeHeaderInformation();

	output_file.open(filename.c_str(), ios::binary);\

	header.Write_Header(&output_file, &magic_characters);
	infoheader.Write_Header(&output_file);
	pixel_array.Write_PixelData(&output_file);

	output_file.close();
}

void Bitmap_File_24bit::Write_Bitmap(const string &p_filename)
{
	filename = p_filename;
	Write_Bitmap();
}

BMPFile_24bit_PixelData Bitmap_File_24bit::get(pair<int,int> rowCol)
{
	return pixel_array.get(rowCol);
}

void Bitmap_File_24bit::set(BMPFile_24bit_PixelData pixel, pair<int,int> rowCol)
{
	pixel_array.set(pixel, rowCol);
}

void Bitmap_File_24bit::completeHeaderInformation()
{
	infoheader.width = width;
	infoheader.height = height;
	infoheader.image_data_size = infoheader.width * infoheader.height * sizeof(BMPFile_24bit_PixelData);
	infoheader.header_size = sizeof(infoheader);

	header.bmp_offset = sizeof(header) + sizeof(magic_characters) + infoheader.header_size;
	header.filesize = header.bmp_offset + infoheader.image_data_size;
}
