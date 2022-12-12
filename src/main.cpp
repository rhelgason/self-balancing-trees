#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
using namespace std;

#define NUM_TREES = 3;

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

void orderedInsert(int size, int step) {
    string filename = "out/ordered_insert.csv";
    cout << endl;
    cout << "=======================================================" << endl;
    cout << " Comparing ordered insert..." << endl;
    ofstream outfile;
    outfile.open(filename);
    outfile << ",";
    for (int i = step; i < size; i += step) {
        outfile << to_string(i) << ",";
    }
    outfile << endl;

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

    delete [] arr;
    outfile.close();
    cout << " Results can be found in " << filename << "." << endl;
    cout << "=======================================================" << endl;
}

void randomInsert(int size, int step) {
    string filename = "out/random_insert.csv";
    cout << endl;
    cout << "=======================================================" << endl;
    cout << " Comparing random insert..." << endl;
    ofstream outfile;
    outfile.open(filename);
    outfile << ",";
    for (int i = step; i < size; i += step) {
        outfile << to_string(i) << ",";
    }
    outfile << endl;

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

    delete [] arr;
    outfile.close();
    cout << " Results can be found in " << filename << "." << endl;
    cout << "=======================================================" << endl;
}

int main(int argc, char *argv[]) {
    int size = 100000;
    int step = 500;

    orderedInsert(size, step);
    randomInsert(size, step);
    cout << endl;

    return 0;
}
