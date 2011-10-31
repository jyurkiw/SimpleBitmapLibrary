/*
 * PixelArrayTest.h
 *
 *  Created on: 2011-10-26
 *      Author: master
 */

#ifndef PIXELARRAYTEST_H_
#define PIXELARRAYTEST_H_

#include "Pixel_24.h"

#include "PixelArray.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

using namespace CppUnit;

typedef PixelArray<pixel24> pixel_array24;

class Pixel_Array_Test : public TestFixture
{
	CPPUNIT_TEST_SUITE( Pixel_Array_Test );
	CPPUNIT_TEST( EmptyConstructorTest );
	CPPUNIT_TEST( IntIntPixelPointer_ConstructorTest );
	CPPUNIT_TEST( RowsTest );
	CPPUNIT_TEST( ColumnsTest );
	CPPUNIT_TEST( PackedArrayLengthTest );
	CPPUNIT_TEST( IntIntResize_PixelArrayTest );
	CPPUNIT_TEST( IntIntGet_WhileEmpty_Test );
	CPPUNIT_TEST( IntIntSetTest );
	CPPUNIT_TEST( IntIntGet_WhileNotEmpty_Test );
	CPPUNIT_TEST( PixelSetEmptyTest );
	CPPUNIT_TEST( PackPixelArrayTest );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp(void);
	void tearDown(void);

	void EmptyConstructorTest(void);
	void IntIntPixelPointer_ConstructorTest(void);
	void RowsTest(void);
	void ColumnsTest(void);
	void PackedArrayLengthTest(void);
	void IntIntResize_PixelArrayTest(void);
	void IntIntGet_WhileEmpty_Test(void);
	void IntIntSetTest(void);
	void IntIntGet_WhileNotEmpty_Test(void);
	void PixelSetEmptyTest(void);
	void PackPixelArrayTest(void);

private:
	pixel24 white;
	pixel24 black;
	pixel_array24 *t_pa;

	int rows, cols;
};

#endif /* PIXELARRAYTEST_H_ */
