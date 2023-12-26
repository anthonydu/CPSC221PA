EXEChain = pa1
OBJS  = PNG.o RGBAPixel.o lodepng.o main.o block.o chain.o chain_given.o

CXX = g++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y -lpthread -lm

all : pa1

$(EXEChain) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEChain)

main.o : main.cpp block.o chain.o cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) main.cpp

block.o : block.cpp block.h
	$(CXX) $(CXXFLAGS) block.cpp

chain.o : chain.cpp chain_private.h chain.h
	$(CXX) $(CXXFLAGS) chain.cpp

chain_given.o : chain_given.cpp chain.h
	$(CXX) $(CXXFLAGS) chain_given.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXEChain)
