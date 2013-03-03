CXX=clang++
FLAGS=-std=c++11 -stdlib=libc++
all:

clean:
	rm -fr build/*

lexer: 
	$(CXX) $(FLAGS) src/lexer/LuthorTest.cpp -o tests/LuthorTest.bin -Isrc/
tree:
	$(CXX) $(FLAGS) src/utils/PamelaIsleyTest.cpp -o tests/PamelaIsleyTest.bin -Isrc/
parser:
	$(CXX) $(FLAGS) src/parser/ParserTest.cpp -o tests/Parser.bin -Isrc/

 
.PHONY: all test clean lexer
