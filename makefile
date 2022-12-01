build: src/main.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h
	g++ -std=c++11 -Wall -o main src/main.cpp src/BinarySearchTree.cpp

test: src/unit_tests.cpp src/Tree.h src/BinarySearchTree.cpp src/BinarySearchTree.h
	g++ -std=c++11 -Wall -o test src/unit_tests.cpp src/BinarySearchTree.cpp

clean:
	rm -f *.o *.exe
