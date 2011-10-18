/*
 * writeBitmap.cpp
 *
 *  Created on: Oct 1, 2011
 *      Author: master
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <memory>
#include <boost/cstdint.hpp>

//#include "bmp.h"
#include "PixelArray.h"
#include "Pixel_24.h"

using namespace std;

void printPixel(pixel24 *p24)
{
	cout << setw(2) << hex << setfill('0') << p24->blue << " " <<
			setw(2) << hex << setfill('0') << p24->green << " " <<
			setw(2) << hex << setfill('0') << p24->red << endl;
}

void printPixelCharArray(char *data, int write_length)
{
	for (int x = 0; x < write_length; x++)
		cout << setw(2) << hex << setfill('0') << data[x] << " ";
	cout << endl;
}

int test_old()
{
	/*
	int height = 3;
	int width = 3;
	string filename = "test.bmp";
	//pixel24_array pixarr(height, width);
	BMP24 bmp(filename, height, width);

	char min = 0x00;
	char max = 0xff;

	pixel24 blue(max,min,min), green(min,max,min), red(min,min,max);
	pair<int,int> rowCol(0,0);

	bmp.set(blue,rowCol);

	rowCol.second = 1;
	bmp.set(green,rowCol);

	rowCol.second = 2;
	bmp.set(red,rowCol);

	bmp.Write_Bitmap();
	*/

	return 0;
}

int test_new()
{
	//pixel24 pix(0x01, 0x6F, 0x5A);
	//printPixelCharArray(pix.pack_pixel(), pix.write_length);

	//printPixelCharArray(data, 3);

	PixelArray pa;

	return 0;
}

int main()
{
	//return test_old();
	return test_new();
}
