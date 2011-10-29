#No installer. Current 'all' target will build and run the unit tests

#UNIT variables
CPPUNITLIB = -lcppunit
UNITEXE = RunUnitTests

#MAKE ALL
all: Pixel_24.o PixelArray.o Pixel24Test.o PixelArrayTest.o RunUnitTests.o
	g++ build/Pixel_24.o build/PixelArray.o build/Pixel24Test.o build/PixelArrayTest.o build/RunUnitTests.o -lcppunit -o bin/RunUnitTests

#MAKE Pixel_24.o
Pixel_24.o: src/Pixel_24/Pixel_24.cpp
	g++ -c -Isrc src/Pixel_24/Pixel_24.cpp -o build/Pixel_24.o 

#MAKE PixelArray.o
#PixelArray.o: src/PixelArray/PixelArray.cpp
#	g++ -c -Isrc src/PixelArray/PixelArray.cpp -o build/PixelArray.o
PixelArray.o: src/PixelArray/PixelArray.cpp Pixel_24.o
	g++ -c -Isrc -Isrc/Pixel_24 build/Pixel_24.o src/PixelArray/PixelArray.cpp -o build/PixelArray.o

#MAKE Pixel24Test.o
Pixel24Test.o: src/unit/Pixel24Test.cpp
	g++ -c -Isrc -Isrc/Pixel_24 -lcppunit src/unit/Pixel24Test.cpp -o build/Pixel24Test.o

#MAKE PixelArrayTest.o
PixelArrayTest.o:  src/unit/PixelArrayTest.cpp
	g++ -c -Isrc -Isrc/PixelArray -Isrc/Pixel_24 -lcppunit src/unit/PixelArrayTest.cpp -o build/PixelArrayTest.o

#MAKE RunUnitTests.o
RunUnitTests.o: src/unit/RunUnitTests.cpp
	g++ -c -Isrc -Isrc/Pixel_24 -Isrc/PixelArray -lcppunit src/unit/RunUnitTests.cpp -o build/RunUnitTests.o

#MAKE clean
clean:
	rm build/Pixel_24.o build/PixelArray.o build/Pixel24Test.o build/PixelArrayTest.o build/RunUnitTests.o bin/RunUnitTests

#MAKE docs
docs:
	doxygen

.PHONY: valgrind
#MAKE valgrind
valgrind: Pixel_24.o.valgrind PixelArray.o.valgrind Pixel24Test.o.valgrind PixelArrayTest.o.valgrind RunUnitTests.o.valgrind
	g++ -g -O0 -fno-inline build/Pixel_24.o.valgrind build/PixelArray.o.valgrind build/Pixel24Test.o.valgrind build/PixelArrayTest.o.valgrind build/RunUnitTests.o.valgrind -lcppunit -o bin/RunUnitTests.valgrind

#MAKE Pixel_24.o.valgrind
Pixel_24.o.valgrind: src/Pixel_24/Pixel_24.cpp
	g++ -g -O0 -fno-inline -c -Isrc src/Pixel_24/Pixel_24.cpp -o build/Pixel_24.o.valgrind

#MAKE PixelArray.o.valgrind
PixelArray.o.valgrind: src/PixelArray/PixelArray.cpp
	g++ -g -O0 -fno-inline -c -Isrc src/PixelArray/PixelArray.cpp -o build/PixelArray.o.valgrind

#MAKE Pixel24Test.o.valgrind
Pixel24Test.o.valgrind: src/unit/Pixel24Test.cpp
	g++ -g -O0 -fno-inline -c -Isrc -Isrc/Pixel_24 -lcppunit src/unit/Pixel24Test.cpp -o build/Pixel24Test.o.valgrind

#MAKE PixelArrayTest.o.valgrind
PixelArrayTest.o.valgrind:  src/unit/PixelArrayTest.cpp
	g++ -g -O0 -fno-inline -c -Isrc -Isrc/PixelArray -Isrc/Pixel_24 -lcppunit src/unit/PixelArrayTest.cpp -o build/PixelArrayTest.o.valgrind

#MAKE RunUnitTests.o.valgrind
RunUnitTests.o.valgrind: src/unit/RunUnitTests.cpp
	g++ -g -O0 -fno-inline -c -Isrc -Isrc/Pixel_24 -Isrc/PixelArray -lcppunit src/unit/RunUnitTests.cpp -o build/RunUnitTests.o.valgrind

.PHONY: run_valgrind
#MAKE run valgrind
run_valgrind:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes bin/RunUnitTests.valgrind
