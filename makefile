build: src/main.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h src/AVLTree.cpp src/AVLTree.h src/RedBlackTree.cpp src/RedBlackTree.h src/SplayTree.cpp src/SplayTree.h
	g++ -std=c++11 -Wall -o main src/main.cpp src/BinarySearchTree.cpp src/AVLTree.cpp src/RedBlackTree.cpp src/SplayTree.cpp

test: src/unit_tests.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h src/AVLTree.cpp src/AVLTree.h src/RedBlackTree.cpp src/RedBlackTree.h src/SplayTree.cpp src/SplayTree.h
	g++ -std=c++11 -Wall -o test src/unit_tests.cpp src/BinarySearchTree.cpp src/AVLTree.cpp src/RedBlackTree.cpp src/SplayTree.cpp

clean:
	rm -f *.o *.exe
