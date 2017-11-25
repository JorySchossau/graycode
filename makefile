SHELL := /bin/bash
GTESTFLAGS := -I googletest/googletest/include -L googletest/build/googlemock/gtest -lgtest 
CXX=g++
CPPFLAGS=-std=c++11 -O3
EXE_NAME=test_graycode

all: clean
all: gtest
all: test_graycode

gtest:
ifeq (,$(wildcard googletest/build/googlemock/gtest/libgtest.a))
	mkdir -p googletest/build
	cd googletest/build && cmake .. -Dgtest_disable_pthreads=ON && make -j4 gtest
endif

run: test_graycode
run:
	@./test_graycode

test_graycode: | gtest
	$(CXX) -o $(EXE_NAME) test_graycode.cpp $(CPPFLAGS) $(GTESTFLAGS)

clean:
	rm -f *.o test_graycode
