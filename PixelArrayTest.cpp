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

	rows = 256;
	cols = 256;
	t_pa = new pixel_array24(rows, cols, white);

	CPPUNIT_ASSERT(t_pa->Rows() == rows);
}

void Pixel_Array_Test::ColumnsTest(void)
{
	t_pa = new pixel_array24(rows, cols, black);

	CPPUNIT_ASSERT(t_pa->Columns() == cols);

	delete t_pa;
	t_pa = 0;

	rows = 256;
	cols = 256;
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

	rows = 256;
	cols = 256;
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

	rows = 256;
	cols = 256;
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
	p = t_pa->get(0,0);

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
	t_pa = new pixel_array24(rows, cols, white);
	pixel24 n_p(127, 127, 127);
	pixel24 g_p;

	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			t_pa->set(y, x, n_p);
		}
	}

	char err_buff[100];

	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			g_p = t_pa->get(y, x);

			if (g_p != n_p)
			{
				for(int i = 0; i < 100; i++) err_buff[i] = '\0';

				sprintf(err_buff, "Assertion failure while comparing R(%d)G(%d)B(%d) and R(%d)G(%d)B(%d).",
					g_p.red(), g_p.green(), g_p.blue(),
					n_p.red(), n_p.green(), n_p.blue());

				CPPUNIT_ASSERT_MESSAGE(err_buff, g_p == n_p);
			}
			else
			{
				CPPUNIT_ASSERT(g_p == n_p);
			}
		}
	}
}

void Pixel_Array_Test::IntIntGet_WhileNotEmpty_Test(void)
{
	t_pa = new pixel_array24(rows, cols, white);
	pixel24 n_p(127, 127, 127);
	pixel24 g_p;

	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			t_pa->set(y, x, n_p);
		}
	}

	char err_buff[100];

	for (int x = 0; x < cols; x++)
	{
		for (int y = 0; y < rows; y++)
		{
			g_p = t_pa->get(y, x);

			if (g_p != n_p)
			{
				for(int i = 0; i < 100; i++) err_buff[i] = '\0';

				sprintf(err_buff, "Assertion failure while comparing R(%d)G(%d)B(%d) and R(%d)G(%d)B(%d).",
					g_p.red(), g_p.green(), g_p.blue(),
					n_p.red(), n_p.green(), n_p.blue());

				CPPUNIT_ASSERT_MESSAGE(err_buff, g_p == n_p);
			}
			else
			{
				CPPUNIT_ASSERT(g_p == n_p);
			}
		}
	}
}

void Pixel_Array_Test::PixelSetEmptyTest(void)
{
	t_pa = new pixel_array24(rows, cols, white);

	CPPUNIT_ASSERT(t_pa->getEmpty() == white);

	t_pa->setEmpty(black);

	CPPUNIT_ASSERT(t_pa->getEmpty() == black);
}

void Pixel_Array_Test::PackPixelArrayTest(void)
{
	rows = 7;
	cols = 7;

	int phony_padding_len = cols % 4;
	if (cols < 4) phony_padding_len = 4 % cols;
	int padded_row_len = cols + phony_padding_len;

	int phony_packed_array_len = rows * padded_row_len * white.write_length;
	pixel24 pix_dat = black;

	char *phony_pixel_pack_array = new char[phony_packed_array_len];
	char *pixel_data = pix_dat.pack_pixel();
	char *empty_data = white.pack_pixel();

	int c_t = 0;
	int p_t = 0;

	while(c_t < phony_packed_array_len)
	{
		p_t++;
		if (p_t >= pix_dat.write_length)
		{
			if (((c_t / pix_dat.write_length) % padded_row_len) < cols)
			{
				if (pix_dat == white) pix_dat = black;
				else pix_dat = white;
			}
			else
			{
				pix_dat = white;
			}
			p_t = 0;
			pixel_data = pix_dat.pack_pixel();
		}

		phony_pixel_pack_array[c_t] = pixel_data[p_t];
		c_t++;
	}

	t_pa = new pixel_array24(rows, cols, white);

	for (int r = 0; r < rows; r++)
		for (int c = 0; c < cols; c++)
			if ((r * cols) + c % 2 == 0) t_pa->set(r, c, black);
			else t_pa->set(r, c, white);

	char *pixel_pack_array = t_pa->pack_pixel_array();

	for (int x = 0, mx = t_pa->Packed_Array_Length(); x < mx; x++)
		CPPUNIT_ASSERT(phony_pixel_pack_array[x] == pixel_pack_array[x]);

	phony_pixel_pack_array = 0;
	pixel_data = 0;
	empty_data = 0;
	pixel_pack_array = 0;
}
