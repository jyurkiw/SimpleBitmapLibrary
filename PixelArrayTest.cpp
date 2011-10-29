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
	white.set(1,1,1);
	black.set(255,255,255);

	rows = 4;
	cols = 4;

	t_pa = 0;
}

void Pixel_Array_Test::tearDown(void)
{
	if (t_pa != 0) delete t_pa;
}

void Pixel_Array_Test::EmptyConstructorTest(void)
{
	t_pa = new pixel_array24();

	CPPUNIT_ASSERT(t_pa->Rows() == 0);
	CPPUNIT_ASSERT(t_pa->Columns() == 0);
	CPPUNIT_ASSERT(t_pa->Packed_Array_Length() == 0);
}

void Pixel_Array_Test::IntIntPixelPointer_ConstructorTest(void)
{
	char err_buff[255];

	int packed_length = 0;
	t_pa = new pixel_array24(rows, cols, black);

	CPPUNIT_ASSERT(t_pa->Rows() == rows);
	CPPUNIT_ASSERT(t_pa->Columns() == cols);
}

void Pixel_Array_Test::RowsTest(void)
{
	t_pa = new pixel_array24(rows, cols, black);

	CPPUNIT_ASSERT(t_pa->Rows() == rows);

	delete t_pa;
	t_pa = 0;

//	rows = 256;
//	cols = 256;
	rows = 8;
	cols = 8;
	t_pa = new pixel_array24(rows, cols, white);

	CPPUNIT_ASSERT(t_pa->Rows() == rows);
}

void Pixel_Array_Test::ColumnsTest(void)
{
	t_pa = new pixel_array24(rows, cols, black);

	CPPUNIT_ASSERT(t_pa->Columns() == cols);

	delete t_pa;
	t_pa = 0;

//	rows = 256;
//	cols = 256;
	rows = 8;
	cols = 8;
	t_pa = new pixel_array24(rows, cols, white);

	CPPUNIT_ASSERT(t_pa->Columns() == cols);
}

void Pixel_Array_Test::PackedArrayLengthTest(void)
{
	char err_buff[255];

	int packed_length = 0;
	t_pa = new pixel_array24(rows, cols, black);

	sprintf(err_buff,
		"The assertion 0 == %d failed. Got %d == %d instead.",
		packed_length, t_pa->Packed_Array_Length(), packed_length);

	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->Packed_Array_Length() == packed_length);

	delete t_pa;
	t_pa = 0;

	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

//	rows = 256;
//	cols = 256;
	rows = 8;
	cols = 8;
	packed_length = 0;
	t_pa = new pixel_array24(rows, cols , black);

	sprintf(err_buff,
		"The assertion 0 == %d failed. Got %d == %d instead.",
		packed_length, t_pa->Packed_Array_Length(), packed_length);

	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->Packed_Array_Length() == packed_length);
}


void Pixel_Array_Test::IntIntResize_PixelArrayTest(void)
{
	char err_buff[255];

	int packed_length = 0;
	t_pa = new pixel_array24(rows, cols, black);

	sprintf(err_buff,
		"The assertion 0 == %d failed. Got %d == %d instead.",
		packed_length, t_pa->Packed_Array_Length(), packed_length);

	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->Packed_Array_Length() == packed_length);

	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

//	rows = 256;
//	cols = 256;
	rows = 8;
	cols = 8;
	packed_length = 0;

	t_pa->Resize_PixelArray(rows, cols);

	sprintf(err_buff,
		"The assertion 0 == %d failed. Got %d == %d instead.",
		packed_length, t_pa->Packed_Array_Length(), packed_length);

	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->Packed_Array_Length() == packed_length);
}


void Pixel_Array_Test::IntIntGet_WhileEmpty_Test(void)
{
	char err_buff[255];
	t_pa = new pixel_array24(rows, cols, black);
	pixel24 p;
	p = t_pa->get(1,1);

	sprintf(err_buff,
		"1. The assertion R(%d) G(%d) B(%d) == R(%d) G(%d) B(%d) failed.",
		p.red(), p.green(), p.blue(),
		black.red(), black.green(), black.blue());

	CPPUNIT_ASSERT_MESSAGE(err_buff, p == black);

	delete t_pa;
	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	t_pa = new pixel_array24(rows, cols, white);
	p = t_pa->get(1,1);

	sprintf(err_buff,
		"2. The assertion R(%d) G(%d) B(%d) == R(%d) G(%d) B(%d) failed.",
		p.red(), p.green(), p.blue(),
		white.red(), white.green(), white.blue());

	CPPUNIT_ASSERT_MESSAGE(err_buff, p == white);

	delete t_pa;
	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	t_pa = new pixel_array24(rows, cols, white);
	p = t_pa->get(2,2);

	sprintf(err_buff,
		"3. The assertion R(%d) G(%d) B(%d) == R(%d) G(%d) B(%d) failed.",
		p.red(), p.green(), p.blue(),
		white.red(), white.green(), white.blue());

	CPPUNIT_ASSERT_MESSAGE(err_buff, p == white);

	delete t_pa;
	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	t_pa = new pixel_array24(rows, cols, black);
	p = t_pa->get(3,3);

	sprintf(err_buff,
		"4. The assertion R(%d) G(%d) B(%d) == R(%d) G(%d) B(%d) failed.",
		p.red(), p.green(), p.blue(),
		black.red(), black.green(), black.blue());

	CPPUNIT_ASSERT_MESSAGE(err_buff, p == black);
}

void Pixel_Array_Test::IntIntSetTest(void)
{
	CPPUNIT_ASSERT(true);
}

void Pixel_Array_Test::IntIntGet_WhileNotEmpty_Test(void)
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
