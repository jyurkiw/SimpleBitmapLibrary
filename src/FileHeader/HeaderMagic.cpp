/*
 * FileMagic.cpp
 *
 *  Created on: 2012-01-07
 *  @author: master
 *  @version: 0.1
 */
#include "HeaderMagic.h"

BitmapHeader_Magic::BitmapHeader_Magic()
{
	magic[0] = 'B';
	magic[1] = 'M';
}
