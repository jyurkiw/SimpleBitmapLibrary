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
	CPPUNIT_TEST( EqualOperatorTest );
	CPPUNIT_TEST( EqualEqualOperatorTest );
	CPPUNIT_TEST( NotEqualOperatorTest );
	CPPUNIT_TEST( SetTest );
	CPPUNIT_TEST( SetBlueTest );
	CPPUNIT_TEST( SetGreenTest );
	CPPUNIT_TEST( SetRedTest );
	CPPUNIT_TEST( GetBlueTest );
	CPPUNIT_TEST( GetGreenTest );
	CPPUNIT_TEST( GetRedTest );
	CPPUNIT_TEST( PackPixelTest );
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void) {}

	void EmptyConstructorTest(void);
	void BGRConstructorTest(void);
	void EqualOperatorTest(void);
	void EqualEqualOperatorTest(void);
	void NotEqualOperatorTest(void);
	void SetTest(void);
	void SetBlueTest(void);
	void SetGreenTest(void);
	void SetRedTest(void);
	void GetBlueTest(void);
	void GetGreenTest(void);
	void GetRedTest(void);
	void PackPixelTest(void);

private:
	//local variables
	pixel24 empty;
	pixel24 red;
	pixel24 blue;
	pixel24 green;
	char max;
	char hi_mid;
	char mid;
	char low_mid;
	char min;
};

#endif /* PIXEL24TEST_H_ */
