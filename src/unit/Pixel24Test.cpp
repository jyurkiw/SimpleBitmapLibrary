/*
 * Pixel24Test.cpp
 *
 *  Created on: 2011-10-18
 *      Author: master
 */
#include <iostream>

#include "cppunit/extensions/HelperMacros.h"
#include "Pixel24Test.h"
#include "Pixel_24.h"

using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION( Pixel_24_Test );

void Pixel_24_Test::setUp(void)
{
	empty.set(0,0,0);
	blue.set(255, 0, 0);
	green.set(0, 255, 0);
	red.set(0, 0, 255);
	max = 255;
	hi_mid = 213;
	mid = 127;
	low_mid = 42;
	min = 0;
}

void Pixel_24_Test::EmptyConstructorTest(void)
{
	CPPUNIT_ASSERT_MESSAGE("Testing that blue = 0x00", empty.blue() == 0x00);
	CPPUNIT_ASSERT_MESSAGE("Testing that green = 0x00", empty.green() == 0x00);
	CPPUNIT_ASSERT_MESSAGE("Testing that red = 0x00", empty.red() == 0x00);
}

void Pixel_24_Test::BGRConstructorTest(void)
{
	pixel24 t_blue(255, 0, 0);
	pixel24 t_green(0, 255, 0);
	pixel24 t_red(0, 0, 255);

	CPPUNIT_ASSERT_MESSAGE("Testing blue == t_blue", blue == t_blue);
	CPPUNIT_ASSERT_MESSAGE("Testing green == t_green", green == t_green);
	CPPUNIT_ASSERT_MESSAGE("Testing red == t_red", red == t_red);
}

void Pixel_24_Test::EqualOperatorTest(void)
{
	pixel24 t_blue, t_red;
	t_blue = blue;
	t_red = red;

	CPPUNIT_ASSERT_MESSAGE("Testing t_blue.blue == 0xFF", t_blue.blue() == max);
	CPPUNIT_ASSERT_MESSAGE("Testing t_blue.green == 0x00", t_blue.green() == min);
	CPPUNIT_ASSERT_MESSAGE("Testing t_blue.red == 0x00", t_blue.red() == min);

	CPPUNIT_ASSERT_MESSAGE("Testing t_red.blue == 0x00", t_red.blue() == min);
	CPPUNIT_ASSERT_MESSAGE("Testing t_red.green == 0x00", t_red.green() == min);
	CPPUNIT_ASSERT_MESSAGE("Testing t_red.red == 0xFF", t_red.red() == max);
}

void Pixel_24_Test::EqualEqualOperatorTest(void)
{
	pixel24 t_blue(255, 0, 0);
	pixel24 t_green(0, 255, 0);
	pixel24 t_red(0, 0, 255);

	CPPUNIT_ASSERT_MESSAGE("Testing t_blue == blue", t_blue == blue);
	CPPUNIT_ASSERT_MESSAGE("Testing t_green == green", t_green == green);
	CPPUNIT_ASSERT_MESSAGE("Testing t_red == red", t_red == red);
}

void Pixel_24_Test::NotEqualOperatorTest(void)
{
	pixel24 t_blue(255, 0, 0);
	pixel24 t_green(0, 255, 0);
	pixel24 t_red(0, 0, 255);

	CPPUNIT_ASSERT_MESSAGE("Testing t_blue != green", t_blue != green);
	CPPUNIT_ASSERT_MESSAGE("Testing t_green != red", t_green != red);
	CPPUNIT_ASSERT_MESSAGE("Testing t_red != blue", t_red != blue);
}

void Pixel_24_Test::SetTest(void)
{
	pixel24 t_blue;
	t_blue.set(255,0,0);

	CPPUNIT_ASSERT_MESSAGE("Testing t_blue.blue == 0xFF", t_blue.blue() == max);
	CPPUNIT_ASSERT_MESSAGE("Testing t_blue.green == 0x00", t_blue.green() == min);
	CPPUNIT_ASSERT_MESSAGE("Testing t_blue.red == 0x00", t_blue.red() == min);
}

void Pixel_24_Test::SetBlueTest(void)
{
	pixel24 t_pixel = empty;

	CPPUNIT_ASSERT(t_pixel.blue() == min);

	t_pixel.blue(low_mid);
	CPPUNIT_ASSERT(t_pixel.blue() == low_mid);

	t_pixel.blue(mid);
	CPPUNIT_ASSERT(t_pixel.blue() == mid);

	t_pixel.blue(hi_mid);
	CPPUNIT_ASSERT(t_pixel.blue() == hi_mid);
}

void Pixel_24_Test::SetGreenTest(void)
{
	pixel24 t_pixel = empty;

	CPPUNIT_ASSERT(t_pixel.green() == min);

	t_pixel.green(low_mid);
	CPPUNIT_ASSERT(t_pixel.green() == low_mid);

	t_pixel.green(mid);
	CPPUNIT_ASSERT(t_pixel.green() == mid);

	t_pixel.green(hi_mid);
	CPPUNIT_ASSERT(t_pixel.green() == hi_mid);
}

void Pixel_24_Test::SetRedTest(void)
{
	pixel24 t_pixel = empty;

	CPPUNIT_ASSERT(t_pixel.red() == min);

	t_pixel.red(low_mid);
	CPPUNIT_ASSERT(t_pixel.red() == low_mid);

	t_pixel.red(mid);
	CPPUNIT_ASSERT(t_pixel.red() == mid);

	t_pixel.red(hi_mid);
	CPPUNIT_ASSERT(t_pixel.red() == hi_mid);
}

void Pixel_24_Test::GetBlueTest(void)
{
	CPPUNIT_ASSERT(blue.blue() == max);
	CPPUNIT_ASSERT(empty.blue() == min);
}

void Pixel_24_Test::GetGreenTest(void)
{
	CPPUNIT_ASSERT(green.green() == max);
	CPPUNIT_ASSERT(empty.green() == min);
}

void Pixel_24_Test::GetRedTest(void)
{
	CPPUNIT_ASSERT(red.red() == max);
	CPPUNIT_ASSERT(empty.red() == min);
}

bool compair_pixel_arrays(char* a, char* b, int size)
{
	for (int x = 0; x < size; x++)
		if (a[x] != b[x]) return false;

	return true;
}

void Pixel_24_Test::PackPixelTest(void)
{
	char *pparr;

	char empty_char_arr[3] = {min, min, min};
	char blue_char_arr[3] = {max, min, min};
	char green_char_arr[3] = {min, max, min};
	char red_char_arr[3] = {min, min, max};

	pparr = empty.pack_pixel();
	CPPUNIT_ASSERT(compair_pixel_arrays(pparr, empty_char_arr, 3));

	pparr = blue.pack_pixel();
	CPPUNIT_ASSERT(compair_pixel_arrays(pparr, blue_char_arr, 3));

	pparr = green.pack_pixel();
	CPPUNIT_ASSERT(compair_pixel_arrays(pparr, green_char_arr, 3));

	pparr = red.pack_pixel();
	CPPUNIT_ASSERT(compair_pixel_arrays(pparr, red_char_arr, 3));
}
