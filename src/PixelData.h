/*!
 * PixelData.h
 *
 *  Created on: 2011-10-16
 *  @author Jeffrey Yurkiw
 *  @version 0.1
 */

#ifndef PIXELDATA_H_
#define PIXELDATA_H_

/*!
 * Abstract PixelData class
 *
 * Inherited by bit-length specific bitmap classes who must impliment
 * the pack_pixel() function.
 */
class PixelData
{
public:
	/*!
	 * The length of the packed pixel data returned by the pack_pixel()
	 * function.
	 */
	int write_length;

	/*!
	 * Base constructor. Sets write_length.
	 */
	PixelData (int p_write_length) : write_length(p_write_length) { }

	/*!
	 * Packs the pixel data into a char array of the proper length
	 *
	 * @return A char array representing the pixel data.
	 */
	virtual char* pack_pixel() = 0;

	/*!
	 * Virtual destructor. Does nothing.
	 */
	virtual ~PixelData() { }
};

typedef PixelData pixel;

#endif /* PIXELDATA_H_ */
