#No installer. Current 'all' target will build and run the unit tests
#General Variables
CPPC = g++
OFLAG = -c
SRCDIR = src
BINDIR = bin
UNITDIR = unit
BLDDIR = build

DEBUGFLAG = -DDEBUG

DBG1 = ${DEBUGFLAG}=1

GDBDBG = -g -O0 -fno-inline

#PixelData.h
PDAT = ${SRCDIR}

P24T = Pixel24Test
UNITPATH = ${SRCDIR}/${UNITDIR}
P24TCPP = ${UNITPATH}/${P24T}.cpp
P24TO = ${BLDDIR}/${P24T}.o

PA = PixelArray
PAPATH = ${SRCDIR}/${PA}
PACPP = ${PAPATH}/${PA}.cpp
PAO = ${BLDDIR}/${PA}.o

P24 = Pixel_24
P24PATH = ${SRCDIR}/${P24}
P24CPP = ${P24PATH}/${P24}.cpp
P24O = ${BLDDIR}/${P24}.o

RUT = RunUnitTests
RUTCPP = ${UNITPATH}/${RUT}.cpp
RUTO = ${BLDDIR}/${RUT}.o

#UNIT variables
CPPUNITLIB = -lcppunit
UNITEXE = RunUnitTests

#MAKE ALL
all: ${P24}.o ${P24T}.o ${RUT}.o
	${CPPC} ${P24O} ${P24TO} ${RUTO} ${CPPUNITLIB} -o ${BINDIR}/${UNITEXE}
	make docs
	${BINDIR}/${UNITEXE}

#MAKE Pixel_24.o
Pixel_24.o: ${P24CPP}
	${CPPC} ${OFLAG} -I${PDAT} ${P24CPP} -o ${P24O} 

#MAKE PixelArray.o
PixelArray.o: ${PACPP}
	${CPPC} ${OFLAG} -I${PDAT} ${PACPP} -o ${PAO}

#MAKE Pixel24Test.o
Pixel24Test.o: #${P24TCPP}
	${CPPC} ${OFLAG} -I${PDAT} -I${P24PATH} ${CPPUNITLIB} ${P24TCPP} -o ${P24TO}

#MAKE RunUnitTests.o
RunUnitTests.o: ${RUTCPP}
	${CPPC} ${OFLAG} -I${PDAT} -I${P24PATH} ${CPPUNITLIB} ${RUTCPP} -o ${RUTO}

#MAKE clean
clean:
	rm ${P24O} ${PAO} ${P24TO} ${RUTO} ${BINDIR}/${UNITEXE}

#MAKE docs
docs:
	doxygen