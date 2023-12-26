EXE = pa3

OBJS_EXE = RGBAPixel.o lodepng.o PNG.o main.o qtree.o qtree-given.o

CXX = clang++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
#LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm
LDFLAGS = -std=c++1y -lpthread -lm 

all : pa3

$(EXE) : $(OBJS_EXE)
	$(LD) $(OBJS_EXE) $(LDFLAGS) -o $(EXE)

#object files
RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

qtree.o : qtree.h qtree-private.h qtree.cpp cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) qtree.cpp -o $@

qtree-given.o : qtree.h qtree-private.h qtree-given.cpp cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) qtree-given.cpp -o $@

main.o : main.cpp cs221util/PNG.h cs221util/RGBAPixel.h qtree.h qtree.h
	$(CXX) $(CXXFLAGS) main.cpp -o main.o

clean :
	-rm -f *.o $(EXE) images-output/*.png
