/*
 * BitmapInfoHeader.h
 *
 *  Created on: 2012-01-07
 *  @author: master
 *  @version: 0.1
 */

#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <boost/cstdint.hpp>

/*!
 * Class for handling an InfoHeader.
 * Manages the numeric data and can translate them into a character string
 * for writing out to file.
 */
class BitmapFile_Infoheader
{
public:
	/*!
	 * The size of the infoheader in bytes.
	 */
	uint32_t header_size;

	/*!
	 * The width of the image in pixels.
	 */
	int32_t width;

	/*!
	 * The height of the image in pixels.
	 */
	int32_t height;

	/*!
	 * The number of planes in the image (usually 1. Defaults to 1).
	 */
	uint16_t planes;

	/*!
	 * The number of bits used to store each pixel's data.
	 */
	uint16_t bits_per_pixel;

	/*!
	 * The file's compression type (not supported. Defaults to 0).
	 */
	uint32_t compress_type;

	/*!
	 * The size of the image's pixel array in bytes.
	 */
	uint32_t image_data_size;

	/*!
	 * The horizontal resolution of the image. Defaults to 2835. Default should
	 * be fine.
	 */
	int32_t horizontal_resolution;

	/*!
	 * The vertical resolution of the image. Defaults to 2835. Default should
	 * be fine.
	 */
	int32_t vertical_resolution;

	/*!
	 * Number of colors in the colortable.
	 * Unnecessary above 16 bits per pixel.
	 * Currently unsupported.
	 */
	uint32_t colors_in_colortable;

	/*!
	 * Number of important colors in the colortable.
	 * Unnecessary if there are no colortables.
	 * Currently unsupported.
	 */
	uint32_t important_color_count;

	/*!
	 * Character string that stores the translated infoheader.
	 */
	char *infoheader;

	/*!
	 * Constructor. Sets some default values.
	 * Calculates the size of the infoheader ans sets
	 * the infoheader array.
	 */
	BitmapFile_Infoheader();

	/*!
	 * Destructor. Deletes the infoheader array.
	 */
	~BitmapFile_Infoheader();

	/*!
	 * Builds the infoheader by translating the header's numeric data
	 * into hex and moving them into the infoheader array.
	 */
	void build_header();
};



#endif /* BITMAPINFOHEADER_H_ */
