/*
 * RunUnitTests.cpp
 *
 *  Created on: 2011-10-18
 *      Author: master
 */
#include "Pixel24Test.h"

#include "cppunit/CompilerOutputter.h"
#include "cppunit/extensions/TestFactoryRegistry.h"
#include "cppunit/ui/text/TextTestRunner.h"

using namespace CppUnit;

void runPixel24Tests()
{
	Test *suite = TestFactoryRegistry::getRegistry().makeTest();
	TextTestRunner runner;
	runner.addTest( suite );

	runner.setOutputter( new CompilerOutputter( &runner.result(), std::cerr));
	runner.run();
}

int main()
{
	runPixel24Tests();

	return 0;
}
