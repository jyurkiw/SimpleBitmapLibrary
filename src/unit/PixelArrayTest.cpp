/*
 * PixelArrayTest.cpp
 *
 *  Created on: 2011-10-26
 *      Author: master
 */

#include "PixelArrayTest.h"

#include <iostream>
#include <stdio.h>

#include "PixelArrayTest.h"
#include "PixelArray.h"
#include "Pixel_24.h"

using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION( Pixel_Array_Test );

void Pixel_Array_Test::setUp(void)
{
	white.set(0,0,0);
	black.set(255,255,255);
}

void Pixel_Array_Test::tearDown(void) {}

void Pixel_Array_Test::EmptyConstructorTest(void)
{
	pixel_array t_pa;

	CPPUNIT_ASSERT(t_pa.Rows() == 0);
	CPPUNIT_ASSERT(t_pa.Columns() == 0);
	CPPUNIT_ASSERT(t_pa.Packed_Array_Length() == 0);
}

void Pixel_Array_Test::IntIntPixelPointer_ConstructorTest(void)
{
	char err_buff[255];

	int rows = 3;
	int columns = 3;
	int packed_length = 0;
	pixel_array t_pa(rows, columns ,&black);

	sprintf(err_buff,
		"The assertion 0 == %d failed. Got %d == %d instead.",
		packed_length, t_pa.Packed_Array_Length(), packed_length);

	CPPUNIT_ASSERT(t_pa.Rows() == rows);
	CPPUNIT_ASSERT(t_pa.Columns() == columns);
	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa.Packed_Array_Length() == packed_length);
}

void Pixel_Array_Test::RowsTest(void)
{
	int rows = 4;
	int cols = 4;
	pixel_array *t_pa = new pixel_array(rows, cols, &black);

	CPPUNIT_ASSERT(t_pa->Rows() == rows);

	delete t_pa;
	t_pa = 0;

	rows = 256;
	cols = 256;
	t_pa = new pixel_array(rows, cols, &white);

	CPPUNIT_ASSERT(t_pa->Rows() == rows);
}

void Pixel_Array_Test::ColumnsTest(void)
{
	int rows = 4;
	int cols = 4;
	pixel_array *t_pa = new pixel_array(rows, cols, &black);

	CPPUNIT_ASSERT(t_pa->Columns() == cols);

	delete t_pa;
	t_pa = 0;

	rows = 256;
	cols = 256;
	t_pa = new pixel_array(rows, cols, &white);

	CPPUNIT_ASSERT(t_pa->Columns() == cols);
}

void Pixel_Array_Test::PackedArrayLengthTest(void)
{
	CPPUNIT_ASSERT(true);
}


void Pixel_Array_Test::IntIntResize_PixelArrayTest(void)
{
	CPPUNIT_ASSERT(true);
}

void Pixel_Array_Test::IntIntGetTest(void)
{
	CPPUNIT_ASSERT(true);
}

void Pixel_Array_Test::IntIntSetTest(void)
{
	CPPUNIT_ASSERT(true);
}

void Pixel_Array_Test::PixelSetEmptyTest(void)
{
	CPPUNIT_ASSERT(true);
}

void Pixel_Array_Test::PackPixelParrayTest(void)
{
	CPPUNIT_ASSERT(true);
}
