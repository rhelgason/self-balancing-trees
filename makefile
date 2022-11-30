build: src/main.cpp src/BinarySearchTree.cpp src/BinarySearchTree.h
	g++ -std=c++11 -Wall -o main src/main.cpp src/BinarySearchTree.cpp

clean:
	rm -f *.o *.exe
