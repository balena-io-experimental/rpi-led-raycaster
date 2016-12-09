PASSTHROUGH_DEFINES = HARDWARE_DESC=adafruit-hat
CXX = g++
#CXX = arm-bcm2708hardfp-linux-gnueabi-g++

CXXFLAGS = -Wall -std=c++11 -O3 -I. -I./rpi-rgb-led-matrix/include -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads -I/opt/vc/include/interface/vmcs_host -I/opt/vc/include/interface/vmcs_host/linux -L./rpi-rgb-led-matrix/lib -L/opt/vc/lib
LIBS = -lrgbmatrix -lrt -lm -lpthread -lbcm_host -Wl,-rpath=/opt/vc/lib

RGBLIB=./rpi-rgb-led-matrix/lib/librgbmatrix.a

OBJS = main.o ray.o raycaster.o keyboard.o map.o

EXE=ledpanel

all: $(EXE)

$(EXE): $(OBJS) $(RGBLIB)
	$(CXX) -o $(EXE) $(OBJS) $(LIBS) $(CXXFLAGS)

%.o: %.cpp %.h $(DEPS) $(GLOBAL)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

%.o: %.cpp $(DEPS) $(GLOBAL)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# If the lib hasn't been built by this point, make sure to build it correctly
$(RGBLIB):
	CXX=$(CXX) CC=$(CC) $(PASSTHROUGH_DEFINES) $(MAKE) -C ./rpi-rgb-led-matrix/lib

clean:
	rm -rf $(OBJS)
	cd ./rpi-rgb-led-matrix && make clean
	rm -rf $(RGBLIB)
