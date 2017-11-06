EXENAME = testimage
OBJS = testimage.o png.o rgbapixel.o image.o
EXENAME1 = testscene
OBJS1 = testscene.o png.o rgbapixel.o image.o scene.o


CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME) $(EXENAME1)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

$(EXENAME1) : $(OBJS1)
	$(LD) $(OBJS1) $(LDFLAGS) -o $(EXENAME1)

png.o : png.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp

scene.o : scene.cpp scene.h
	$(CXX) $(CXXFLAGS) scene.cpp

testimage.o : testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

testscene.o : testscene.cpp scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp

clean :
	-rm -f *.o $(EXENAME)
