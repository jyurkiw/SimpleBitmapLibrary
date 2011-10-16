/*
 * bmp.h
 *
 *  Created on: Oct 1, 2011
 *      Author: master
 *
 *  Defines header objects for a bitmap file, as well as objects used to
 *  represent pixel data and the pixel array structure.
 */
#ifndef BMP_H
#define BMP_H

#include <boost/cstdint.hpp>
#include <fstream>
#include <vector>
#include <string>

class BMPFile_Magic
{
public:
	char magic[2];

	BMPFile_Magic();
};

class BMPFile_Header
{
public:
	uint32_t filesize;
	uint16_t creator1;
	uint16_t creator2;
	uint32_t bmp_offset;

	BMPFile_Header();
	void Write_Header(std::ofstream*, BMPFile_Magic*);
};

class BMPFile_Infoheader
{
public:
	uint32_t header_size;
	int32_t width;
	int32_t height;
	uint16_t planes;
	uint16_t bits_per_pixel;
	uint32_t compress_type;
	uint32_t image_data_size;
	int32_t horizontal_resolution;
	int32_t vertical_resolution;
	uint32_t colors_in_colortable;
	uint32_t important_color_count;

	BMPFile_Infoheader();
	void Write_Header(std::ofstream*);
};

class BMPFile_24bit_PixelData
{
public:
	char blue;
	char green;
	char red;

	BMPFile_24bit_PixelData();
	BMPFile_24bit_PixelData(char, char, char);

	void Write_PixelData(std::ofstream*);

	BMPFile_24bit_PixelData& operator = (const BMPFile_24bit_PixelData&);
	bool operator == (const BMPFile_24bit_PixelData&);
	bool operator != (const BMPFile_24bit_PixelData&);
};

class BMPFile_24bit_PixelArray
{
public:
	BMPFile_24bit_PixelArray();
	BMPFile_24bit_PixelArray(int, int);

	void Reinitialize_PixelArray(int, int);

	void Write_PixelData(std::ofstream*);

	BMPFile_24bit_PixelData get(std::pair<int,int>);
	void set(BMPFile_24bit_PixelData, std::pair<int,int>);
private:
	int row_padding;
	int rows;
	int columns;

	std::vector<BMPFile_24bit_PixelData> pixel_array;
	std::vector<int> row_offsets;

	void Write_RowPadding(std::ofstream*);
	int getPosition(std::pair<int,int>);
};

class Bitmap_File_24bit
{
public:
	BMPFile_Magic magic_characters;
	BMPFile_Header header;
	BMPFile_Infoheader infoheader;
	BMPFile_24bit_PixelArray pixel_array;

	std::string filename;
	int height;
	int width;

	Bitmap_File_24bit(int, int);
	Bitmap_File_24bit(const std::string&, int, int);

	void Write_Bitmap();
	void Write_Bitmap(const std::string&);

	BMPFile_24bit_PixelData get(std::pair<int,int>);
	void set(BMPFile_24bit_PixelData, std::pair<int,int>);

private:
	void completeHeaderInformation();
};

#endif

typedef BMPFile_Header bitmap_header;
typedef BMPFile_Magic bitmap_magic;
typedef BMPFile_Infoheader bitmap_infoheader;
typedef BMPFile_24bit_PixelData pixel24;
typedef BMPFile_24bit_PixelArray pixel24_array;
typedef Bitmap_File_24bit BMP24;
