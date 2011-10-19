/*
 * Pixel24Test.cpp
 *
 *  Created on: 2011-10-18
 *      Author: master
 */
#include <iostream>

#include "cppunit/extensions/HelperMacros.h"
#include "Pixel24Test.h"
#include "../src/Pixel_24.h"

using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION( Pixel_24_Test );

void Pixel_24_Test::setUp(void)
{
	blue.set(0xFF, 0x00, 0x00);
	red.set(0x00, 0x00, 0xFF);
	green.set(0x00, 0xFF, 0x00);
}

void Pixel_24_Test::EmptyConstructorTest(void)
{
	CPPUNIT_ASSERT_MESSAGE("Testing that blue = 0x00", empty.blue == 0x00);
	CPPUNIT_ASSERT_MESSAGE("Testing that green = 0x00", empty.green == 0x00);
	CPPUNIT_ASSERT_MESSAGE("Testing that red = 0x00", empty.red == 0x00);
}

void Pixel_24_Test::BGRConstructorTest(void)
{
	pixel24 t_blue(0xFF, 0x00, 0x00);
	pixel24 t_green(0x00, 0xFF, 0x00);
	pixel24 t_red(0x00, 0x00, 0xFF);

	CPPUNIT_ASSERT_MESSAGE("Testing blue == t_blue", blue == t_blue);
	CPPUNIT_ASSERT_MESSAGE("Testing green == t_green", green == t_green);
	CPPUNIT_ASSERT_MESSAGE("Testing red == t_red", red == t_red);
}
