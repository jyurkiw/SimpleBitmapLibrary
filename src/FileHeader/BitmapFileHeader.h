/*
 * BitmapFileHeader.h
 *
 *  Created on: 2012-01-07
 *  @author: master
 *  @version: 0.1
 */
#ifndef BMP_FILE_HEADER
#define BMP_FILE_HEADER

#include <boost/cstdint.hpp>
#include "HeaderMagic.h"

/*!
 * Class to handle bitmap file header data.
 * This class stores data for the file size, creator 1 and 2, and offset fields.
 * It also handles translating the numeric data into a writable string format.
 */
class BitmapFile_Header
{
public:
	/*!
	 * The size of the file in bytes.
	 * This is equal to the size of the header, infoheader, pixel array,
	 * and any colortables.
	 */
	uint32_t filesize;

	/*!
	 * No standard use. Function determined by the application creating the
	 * bitmap file.
	 */
	uint16_t creator1;

	/*!
	 * No standard use. Function determined by the application creating the
	 * bitmap file.
	 */
	uint16_t creator2;

	/*!
	 * Offset of the pixel array data. Equal to the length of the header,
	 * infoheader, and any colortables.
	 */
	uint32_t bmp_offset;

	/*!
	 * Translated header data. A hex string not suited for human readability.
	 */
	char *header;

	/*!
	 * The length of the header string in bytes.
	 */
	char header_length;

	/*!
	 * Constructor. Sets all field to zero. Calculates the length of the header
	 * string and dynamically creates it.
	 */
	BitmapFile_Header();

	/*!
	 * Destructor. Frees the header memory.
	 */
	~BitmapFile_Header();

	/*!
	 * Builds the header string.
	 * @param BitmapHeader_Magic wrapper object for the "magic characters".
	 */
	void build_header(BitmapHeader_Magic*);
};

#endif
