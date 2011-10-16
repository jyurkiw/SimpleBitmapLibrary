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
#include <boost/cstdint.hpp>

#include "bmp.h"

using namespace std;

void printPixel(pixel24 *p24)
{
	cout << setw(2) << hex << setfill('0') << p24->blue << " " <<
			setw(2) << hex << setfill('0') << p24->green << " " <<
			setw(2) << hex << setfill('0') << p24->red << endl;
}

int main()
{
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

	return 0;
}
