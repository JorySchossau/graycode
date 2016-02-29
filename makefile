CXX=g++
CPPFLAGS=-std=c++11
EXE_NAME=test_graycode

gtest:
	cd googletest/googletest && cmake .
	cd googletest/googletest && make

test: clean
test: gtest
test: CXX += -I"googletest/googletest/include" -L"googletest/googletest"
test: CPPFLAGS += -pthread -lgtest
test: test_graycode

run: test
run:
	@./test_graycode

test_graycode: test_graycode.o
	$(CXX) $(CPPFLAGS) -o ${EXE_NAME} $^

clean:
	rm -f *.o test_graycode
