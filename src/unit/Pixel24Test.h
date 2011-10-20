/*
 * Pixel24Test.h
 *
 *  Created on: 2011-10-18
 *      Author: master
 */

#ifndef PIXEL24TEST_H_
#define PIXEL24TEST_H_

#include "Pixel_24.h"
#include "cppunit/TestFixture.h"
#include "cppunit/extensions/HelperMacros.h"

using namespace CppUnit;

class Pixel_24_Test : public TestFixture
{
	CPPUNIT_TEST_SUITE( Pixel_24_Test );
	CPPUNIT_TEST( EmptyConstructorTest );
	CPPUNIT_TEST( BGRConstructorTest );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void) {}

	void EmptyConstructorTest(void);
	void BGRConstructorTest(void);

private:
	//local variables
	pixel24 empty;
	pixel24 red;
	pixel24 blue;
	pixel24 green;
};

#endif /* PIXEL24TEST_H_ */
