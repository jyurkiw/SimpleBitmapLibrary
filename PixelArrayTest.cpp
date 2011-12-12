/*
 * PixelArrayTest.cpp
 *
 *  Created on: 2011-10-26
 *      Author: master
 */

#include "PixelArrayTest.h"

#include <iostream>
#include <stdio.h>

#include <utility>

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

	int packed_length = 4 * 4 * black.write_length;

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
	packed_length = rows * cols * black.write_length;
	t_pa = new pixel_array24(rows, cols , black);

	sprintf(err_buff,
		"The assertion 0 == %d failed. Got %d == %d instead.",
		packed_length, t_pa->Packed_Array_Length(), packed_length);

	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->Packed_Array_Length() == packed_length);
}


void Pixel_Array_Test::IntIntResize_PixelArrayTest(void)
{
	char err_buff[255];

	int packed_length = rows * cols * black.write_length;
	t_pa = new pixel_array24(rows, cols, black);

	sprintf(err_buff,
		"The assertion 0 == %d failed. Got %d == %d instead.",
		packed_length, t_pa->Packed_Array_Length(), packed_length);

	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->Packed_Array_Length() == packed_length);

	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	rows = 256;
	cols = 256;
	packed_length = rows * cols * black.write_length;

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

void BuildSingleColorArray(char *char_arr, int array_len, pixel24 color)
{
	char *color_array = color.pack_pixel();

	for (int x = 0, subx = 0; x < array_len; x++, subx++)
	{
		if (subx == color.write_length) subx = 0;

		char_arr[x] = color_array[subx];
	}
}

void BuildCheckerArray(char *char_arr, int array_len, int rows, int cols, pixel24 color1, pixel24 color2)
{
	pixel24 color = color1;
	char *color_array = color.pack_pixel();

	for (int i = 0, row = 0; row < rows; row++)
	{
		if (color == color1) color = color2;
		else color = color1;
		char *color_array = color.pack_pixel();

		for (int col = 0; col < cols; col++)
		{
			if (color == color1) color = color2;
			else color = color1;
			char *color_array = color.pack_pixel();

			for (int subi = 0; subi < color.write_length; subi++, i++)
				char_arr[i] = color_array[subi];
		}
	}
}

void Pixel_Array_Test::ComparePixelArrays(char *arr2)
{
	char err_msg[1024];
	char *arr1 = t_pa->pack_pixel_array();

	sprintf(err_msg, "\nExpected:\n%s\nGot:\n%s", arr2, arr1);

	for (int x = 0; x < t_pa->packed_array_length; x++)
	{
		CPPUNIT_ASSERT_MESSAGE(err_msg, arr1[x] == arr2[x]);
	}
}

void printPixelArrayToConsole(char *p_arr)
{
	char outarr[1024];
	sprintf(outarr, "Pixel Array:\n%s", p_arr);
	std::cout << outarr << std::endl;
}

void Pixel_Array_Test::PackWhitePixelArrayTest(void)
{
	//create 4x4 grid of white pixels
	t_pa = new pixel_array24(rows, cols, white);

	char *faux_pixel_array = new char[1024];

	BuildSingleColorArray(faux_pixel_array, t_pa->packed_array_length, white);

	ComparePixelArrays(faux_pixel_array);

	delete[] faux_pixel_array;
}

void Pixel_Array_Test::PackBlackPixelArrayTest(void)
{
	//create 4x4 grid of black pixels
	t_pa = new pixel_array24(rows, cols, black);

	char *faux_pixel_array = new char[1024];

	BuildSingleColorArray(faux_pixel_array, t_pa->packed_array_length, black);

	ComparePixelArrays(faux_pixel_array);

	delete[] faux_pixel_array;
}

void Pixel_Array_Test::PackWhiteBlackCheckerPixelArrayTest(void)
{
	//create 4x4 checker grid, white then black
	t_pa = new pixel_array24(rows, cols, white);

	bool checker_black = false;

	for (int row = 0; row < rows; row++, checker_black = !checker_black)
		for (int col = 0; col < cols; col++, checker_black = !checker_black)
			if (checker_black) t_pa->set(row, col, black);

	char *faux_pixel_array = new char[1024];

	BuildCheckerArray(faux_pixel_array, t_pa->packed_array_length, rows, cols, white, black);

	ComparePixelArrays(faux_pixel_array);

	delete[] faux_pixel_array;
}

#ifdef UNITTEST
void Pixel_Array_Test::Set_packed_array_length_test(void)
{
	char err_buff[255];
	int expected_length;

	t_pa = new pixel_array24();
	t_pa->setEmpty(white);
	expected_length = (t_pa->columns + t_pa->row_padding) * t_pa->rows * t_pa->empty.write_length;

	sprintf(err_buff, "Expected len was 0, found %d instead.", t_pa->packed_array_length);
	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->packed_array_length == 0);
	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	t_pa->rows = 3;
	t_pa->columns = 2;
	t_pa->row_padding = 2;
	t_pa->set_packed_array_length();
	expected_length = (t_pa->columns + t_pa->row_padding) * t_pa->rows * t_pa->empty.write_length;

	sprintf(err_buff, "Expected len was %d, found %d instead.", expected_length, t_pa->packed_array_length);
	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->packed_array_length == expected_length);
	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	t_pa->rows = 4;
	t_pa->columns = 4;
	t_pa->row_padding = 4-(t_pa->columns % 4 == 0 ? 4 : t_pa->columns % 4);
	t_pa->set_packed_array_length();
	expected_length = (t_pa->columns + t_pa->row_padding) * t_pa->rows * t_pa->empty.write_length;

	sprintf(err_buff, "Expected len was %d, found %d instead.", expected_length, t_pa->packed_array_length);
	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->packed_array_length == expected_length);
	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	t_pa->rows = 5;
	t_pa->columns = 5;
	t_pa->row_padding = 4-(t_pa->columns % 4 == 0 ? 4 : t_pa->columns % 4);
	t_pa->set_packed_array_length();
	expected_length = (t_pa->columns + t_pa->row_padding) * t_pa->rows * t_pa->empty.write_length;

	sprintf(err_buff, "Expected len was %d, found %d instead.", expected_length, t_pa->packed_array_length);
	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->packed_array_length == expected_length);
	for (int x = 0; x < 255; x++) err_buff[x] = '\0';

	t_pa->rows = 245;
	t_pa->columns = 620;
	t_pa->row_padding = 4-(t_pa->columns % 4 == 0 ? 4 : t_pa->columns % 4);
	t_pa->set_packed_array_length();
	expected_length = (t_pa->columns + t_pa->row_padding) * t_pa->rows * t_pa->empty.write_length;

	sprintf(err_buff, "Expected len was %d, found %d instead.", expected_length, t_pa->packed_array_length);
	CPPUNIT_ASSERT_MESSAGE(err_buff, t_pa->packed_array_length == expected_length);
}

void Pixel_Array_Test::Calc_pixel_coords_by_packed_index_test(void)
{
	std::pair<int,int> loc, expected;
	t_pa = new pixel_array24(rows, cols, white);
	int index = 0;

	char err_buff_row[255];
	char err_buff_col[255];

	expected.first = 0;
	expected.second = 0;

	loc = t_pa->calc_pixel_coords_by_packed_index(index);

	sprintf(err_buff_row, "Row: Got %d. Was expecting %d.", loc.first, expected.first);
	CPPUNIT_ASSERT_MESSAGE(err_buff_row, loc.first == expected.first);

	sprintf(err_buff_col, "Col: Got %d. Was expecting %d.", loc.second, expected.second);
	CPPUNIT_ASSERT_MESSAGE(err_buff_col, loc.second == expected.second);
	for (int x = 0; x < 255; x++)
	{
		err_buff_row[x] = '\0';
		err_buff_col[x] = '\0';
	}

	expected.first = 0;
	expected.second = 1;
	index += white.write_length;

	loc = t_pa->calc_pixel_coords_by_packed_index(index);

	sprintf(err_buff_row, "Row: Got %d. Was expecting %d. info: index = %d", loc.first, expected.first, index);
	CPPUNIT_ASSERT_MESSAGE(err_buff_row, loc.first == expected.first);

	sprintf(err_buff_col, "Col: Got %d. Was expecting %d. info: index = %d", loc.second, expected.second, index);
	CPPUNIT_ASSERT_MESSAGE(err_buff_col, loc.second == expected.second);
	for (int x = 0; x < 255; x++)
	{
		err_buff_row[x] = '\0';
		err_buff_col[x] = '\0';
	}

	expected.first = 1;
	expected.second = 2;
	index += (white.write_length * cols) + white.write_length;

	loc = t_pa->calc_pixel_coords_by_packed_index(index);

	sprintf(err_buff_row, "Row: Got %d. Was expecting %d. info: index = %d", loc.first, expected.first, index);
	CPPUNIT_ASSERT_MESSAGE(err_buff_row, loc.first == expected.first);

	sprintf(err_buff_col, "Col: Got %d. Was expecting %d. info: index = %d", loc.second, expected.second, index);
	CPPUNIT_ASSERT_MESSAGE(err_buff_col, loc.second == expected.second);
	for (int x = 0; x < 255; x++)
	{
		err_buff_row[x] = '\0';
		err_buff_col[x] = '\0';
	}

	expected.first = 0;
	expected.second = 0;
	index = 0;
	bool notDone = true;

	while(notDone)
	{
		expected.second++;
		if (expected.second >= t_pa->columns)
		{
			expected.first++;
			expected.second = 0;
		}

		index += t_pa->empty.write_length;

		loc = t_pa->calc_pixel_coords_by_packed_index(index);

		sprintf(err_buff_row, "Row: Got %d (col %d). Was expecting %d (col %d). info: index = %d; pack_i = %d; colSize = %d",
				loc.first, loc.second, expected.first, expected.second,
				index, index / t_pa->empty.write_length,
				t_pa->columns + t_pa->row_padding);
		CPPUNIT_ASSERT_MESSAGE(err_buff_row, loc.first == expected.first);

		sprintf(err_buff_col, "Col: Got %d (row %d). Was expecting %d (row %d). info: index = %d; pack_i = %d; colSize = %d",
				loc.second, loc.first, expected.second, expected.first,
				index, index / t_pa->empty.write_length,
				t_pa->columns + t_pa->row_padding);
		CPPUNIT_ASSERT_MESSAGE(err_buff_col, loc.second == expected.second);
		for (int x = 0; x < 255; x++)
		{
			err_buff_row[x] = '\0';
			err_buff_col[x] = '\0';
		}

		if (expected.first == 4) notDone = false;
	}
}
#endif
