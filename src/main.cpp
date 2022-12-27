#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <string>
#include <map>

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "SplayTree.h"
using namespace std;

#define DEFAULT_SIZE 100000
#define DEFAULT_STEP 500

typedef void (*functionPtr) (int, int);

template <typename T>
class BaseMetrics {
    private:
        chrono::steady_clock::time_point start;

        void startTime() {
            start = chrono::steady_clock::now();
        }

        void stopTime(int step, ofstream &outfile) {
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            auto elapsedTime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            outfile << to_string(float(elapsedTime) / float(step)) << ",";
        }

    protected:
        virtual string getName() = 0;
        virtual T createTree() = 0;

    public:
        void startTest(ofstream &outfile) {
            cout << "   Running test on " << getName() << "..." << endl;
            outfile << getName() << ",";
        }

        void calcInsert(int* arr, int size, int step, ofstream &outfile) {
            startTest(outfile);
            T tree = createTree();

            for (int i = 0; i < size; i += step) {
                startTime();
                for (int k = i; k < i + step; k++) {
                    tree.insert(arr[k]);
                }
                stopTime(step, outfile);
            }

            outfile << endl;
        }

        virtual ~BaseMetrics() {}
};

template<class T>
class BinarySearchTreeMetrics : public BaseMetrics<BinarySearchTree> {
    protected:
        string getName() override {
            return "Binary Search Tree";
        }

        T createTree() override {
            return BinarySearchTree();
        }

    public:
        BinarySearchTreeMetrics() {}
        ~BinarySearchTreeMetrics() {}
};

template<class T>
class AVLTreeMetrics : public BaseMetrics<AVLTree> {
    protected:
        string getName() override {
            return "AVL Tree";
        }

        T createTree() override {
            return AVLTree();
        }

    public:
        AVLTreeMetrics() {}
        ~AVLTreeMetrics() {}
};

template<class T>
class RedBlackTreeMetrics : public BaseMetrics<RedBlackTree> {
    protected:
        string getName() override {
            return "Red Black Tree";
        }

        T createTree() override {
            return RedBlackTree();
        }

    public:
        RedBlackTreeMetrics() {}
        ~RedBlackTreeMetrics() {}
};

template<class T>
class SplayTreeMetrics : public BaseMetrics<SplayTree> {
    protected:
        string getName() override {
            return "Splay Tree";
        }

        T createTree() override {
            return SplayTree();
        }

    public:
        SplayTreeMetrics() {}
        ~SplayTreeMetrics() {}
};

void startTest(int size, int step, string testName, string fileName, ofstream &outfile) {
    outfile.open(fileName);
    cout << endl;
    cout << "=======================================================" << endl;
    cout << " Comparing " << testName << "..." << endl;
    outfile << ",";
    for (int i = step; i < size; i += step) {
        outfile << to_string(i) << ",";
    }
    outfile << endl;
}

void endTest(string fileName, ofstream &outfile) {
    outfile.close();
    cout << " Results can be found in " << fileName << "." << endl;
    cout << "=======================================================" << endl;
}

void orderedInsert(int size, int step) {
    string testName = "ordered insert";
    string fileName = "out/ordered_insert.csv";
    ofstream outfile;
    startTest(size, step, testName, fileName, outfile);

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    BinarySearchTreeMetrics<BinarySearchTree> tester1 = BinarySearchTreeMetrics<BinarySearchTree>();
    tester1.calcInsert(arr, size, step, outfile);
    AVLTreeMetrics<AVLTree> tester2 = AVLTreeMetrics<AVLTree>();
    tester2.calcInsert(arr, size, step, outfile);
    RedBlackTreeMetrics<RedBlackTree> tester3 = RedBlackTreeMetrics<RedBlackTree>();
    tester3.calcInsert(arr, size, step, outfile);
    SplayTreeMetrics<SplayTree> tester4 = SplayTreeMetrics<SplayTree>();
    tester4.calcInsert(arr, size, step, outfile);

    delete [] arr;
    endTest(fileName, outfile);
}

void randomInsert(int size, int step) {
    string testName = "random insert";
    string fileName = "out/random_insert.csv";
    ofstream outfile;
    startTest(size, step, testName, fileName, outfile);

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    random_shuffle(arr, arr + size);

    BinarySearchTreeMetrics<BinarySearchTree> tester1 = BinarySearchTreeMetrics<BinarySearchTree>();
    tester1.calcInsert(arr, size, step, outfile);
    AVLTreeMetrics<AVLTree> tester2 = AVLTreeMetrics<AVLTree>();
    tester2.calcInsert(arr, size, step, outfile);
    RedBlackTreeMetrics<RedBlackTree> tester3 = RedBlackTreeMetrics<RedBlackTree>();
    tester3.calcInsert(arr, size, step, outfile);
    SplayTreeMetrics<SplayTree> tester4 = SplayTreeMetrics<SplayTree>();
    tester4.calcInsert(arr, size, step, outfile);

    delete [] arr;
    endTest(fileName, outfile);
}

int main(int argc, char *argv[]) {
    // get command line arguments
    int size = DEFAULT_SIZE;
    int step = DEFAULT_STEP;
    char* functions = NULL;
    int c;
    while ((c = getopt (argc, argv, "s:t:f:")) != -1) {
        switch(c) {
            case 's':
                try {
                    size = stoi(optarg);
                } catch (exception &err) {
                    cout << endl << "Encountered error on size: " << err.what() << endl;
                    return 1;
                }
                break;
            case 't':
                try {
                    step = stoi(optarg);
                } catch (exception &err) {
                    cout << endl << "Encountered error on step: " << err.what() << endl;
                    return 1;
                }
                break;
            case 'f':
                functions = optarg;
                break;
            default:
                cout << endl << "Unknown command line argument encountered." << endl;
                break;
        }
    }
    cout << endl << "Running tests with size " << size << " and step " << step << "." << endl;

    // define function map
    // C++ does not support reflection, simple workaround
    map<string, functionPtr> functionMap;
    functionMap["orderedInsert"] = orderedInsert;
    functionMap["randomInsert"] = randomInsert;

    if (functions == NULL) {
        orderedInsert(size, step);
        randomInsert(size, step);
    } else {
        char* function;
        function = strtok(functions, " ");
        while (function != NULL) {
            if (functionMap.count(function)) {
                functionMap[function](size, step);
            } else {
                cout << endl << "Function " << function << " not found, skipping..." << endl;
            }
            function = strtok(NULL, " ");
        }
    }
    cout << endl;

    return 0;
}
