CC = g++
CXXFLAGS = -std=c++11 -g -Wall -Werror -Wextra -pedantic -ansi
SIZE=""
STEP=""

build: src/main.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h src/AVLTree.cpp src/AVLTree.h src/RedBlackTree.cpp src/RedBlackTree.h src/SplayTree.cpp src/SplayTree.h
	$(CC) $(CXXFLAGS) -o bin/main src/main.cpp src/BinarySearchTree.cpp src/AVLTree.cpp src/RedBlackTree.cpp src/SplayTree.cpp -std=c++11

run: bin/main
	./bin/main

test: src/unit_tests.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h src/AVLTree.cpp src/AVLTree.h src/RedBlackTree.cpp src/RedBlackTree.h src/SplayTree.cpp src/SplayTree.h
	$(CC) $(CXFLAGS) -o bin/test src/unit_tests.cpp src/BinarySearchTree.cpp src/AVLTree.cpp src/RedBlackTree.cpp src/SplayTree.cpp -std=c++11

runTest: bin/test
	./bin/test

clean:
	rm -f *.o *.exe
