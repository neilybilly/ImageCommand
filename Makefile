CXX := g++
CXXFLAGS := -Wall -std=c++11

check: image_command
#	 ./image_command -T 53 -g 0:127,255,127:52:127,0,127 -J -m 210 -p 600,600 -r -1.2:1.0,-0.90:1.30 -a 0.285,0.01 -f command_julia01.ppm
# 	 ./image_command -z 13:3.1415,75:-2.711=hello
# 	 ./image_command -T 53

image_command: image_command.o JuliaSet.o MandelbrotSet.o PPM.o ColorTable.o ComplexFractal.o
	$(CXX) $(CXXFLAGS) -o $@ $^

image_command.o: image_command.cpp JuliaSet.h PPM.h ColorTable.h MandelbrotSet.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

PPM.o: PPM.cpp PPM.h
	$(CXX) $(CXXFLAGS) -c $<

ComplexFractal.o: ComplexFractal.cpp PPM.h ColorTable.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

MandelbrotSet.o: MandelbrotSet.cpp MandelbrotSet.h PPM.h ColorTable.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

JuliaSet.o: JuliaSet.cpp JuliaSet.h PPM.h ColorTable.h ComplexFractal.h
	$(CXX) $(CXXFLAGS) -c $<

ColorTable.o: ColorTable.cpp ColorTable.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	-rm -f image_command
	-rm -f *.o
	-rm -f *~
