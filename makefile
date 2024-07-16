CXX = clang++
CXXFLAGS = -std=c++17 -Werror -Wall -g
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system


all: tree test

tree: demo
	./$^

demo: demo.o complex.o
	$(CXX) $(CXXFLAGS) -o demo complex.o demo.o $(SFMLFLAGS)

demo.o: demo.cpp node.hpp tree.hpp complex.o
	$(CXX) $(CXXFLAGS) -c demo.cpp

complex.o: complex.cpp complex.hpp
	$(CXX) $(CXXFLAGS) -c complex.cpp

test: test.o complex.o
	$(CXX) $(CXXFLAGS) -o test test.o complex.o $(SFMLFLAGS)

test.o: test.cpp node.hpp tree.hpp complex.hpp
	$(CXX) $(CXXFLAGS) -c test.cpp

clean:
	rm -f *.o tree demo test