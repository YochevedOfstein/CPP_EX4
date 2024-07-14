CXX = clang++
CXXFLAGS = -std=c++11 -Werror -Wall -g


all: tree

tree: demo
	./$^

demo: demo.o
	$(CXX) $(CXXFLAGS) -o demo demo.o

demo.o: demo.cpp node.hpp tree.hpp complex.o
	$(CXX) $(CXXFLAGS) -c demo.cpp

complex.o: complex.cpp complex.hpp
	$(CXX) $(CXXFLAGS) -c complex.cpp

clean:
	rm -f *.o tree demo