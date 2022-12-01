build: src/main.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h src/AVLTree.cpp src/AVLTree.h
	g++ -std=c++11 -Wall -o main src/main.cpp src/BinarySearchTree.cpp src/AVLTree.cpp

test: src/unit_tests.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h src/AVLTree.cpp src/AVLTree.h
	g++ -std=c++11 -Wall -o test src/unit_tests.cpp src/BinarySearchTree.cpp src/AVLTree.cpp

clean:
	rm -f *.o *.exe
