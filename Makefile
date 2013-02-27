CXX=clang++
# need to find a way to auto detect platform
PLATFORM=i486-linux-gnu
LIB_CXX=/usr/local/src/libcxx/lib/libc++.so
FLAGS=-std=c++11 -stdlib=libc++
all:

clean:
	rm -fr build/*

lexer: 
	$(CXX) $(FLAGS) src/lexer/LuthorTest.cpp -o tests/LuthorTest.bin -Isrc/

 
.PHONY: all test clean lexer
