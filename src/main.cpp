#include <iostream>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <string.h>
#include <map>

#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "RedBlackTree.h"
#include "SplayTree.h"
using namespace std;

#define DEFAULT_SIZE 100000
#define DEFAULT_STEP 500

enum MetricType {
    INSERT,
    FIND
};

string metricTypeToString(MetricType metricType) {
    switch (metricType) {
        case INSERT: return "insert";
        case FIND: return "find";
        default: throw invalid_argument("Unrecognized metric type.");
    }
}

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
        void startMetricTest(ofstream &outfile) {
            cout << "   Running test on " << getName() << "..." << endl;
            outfile << getName() << ",";
        }

        void calcInsert(int* arr, int size, int step, ofstream &outfile) {
            startMetricTest(outfile);
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

        void calcFind(int* arr, int size, int step, ofstream &outfile) {
            startMetricTest(outfile);
            T tree = createTree();

            for (int i = 0; i < size; i += step) {
                for (int k = i; k < i + step; k++) {
                    tree.insert(arr[k]);
                }
                startTime();
                for (int k = 0; k < step; k++) {
                    tree.includes(rand() % size);
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
    for (int i = step; i <= size; i += step) {
        outfile << to_string(i) << ",";
    }
    outfile << endl;
}

void endTest(string fileName, ofstream &outfile) {
    outfile.close();
    cout << " Results can be found in " << fileName << "." << endl;
    cout << "=======================================================" << endl;
}

void runMetric(int size, int step, bool ordered, MetricType metricType) {
    string testName = (ordered ? "ordered " : "random ") + metricTypeToString(metricType);
    string fileName = "out/" + testName + ".csv";
    replace(fileName.begin(), fileName.end(), ' ', '_');
    ofstream outfile;
    startTest(size, step, testName, fileName, outfile);

    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    if (!ordered) {
        random_shuffle(arr, arr + size);
    }

    switch (metricType) {
        case INSERT:
            BinarySearchTreeMetrics<BinarySearchTree>().calcInsert(arr, size, step, outfile);
            AVLTreeMetrics<AVLTree>().calcInsert(arr, size, step, outfile);
            RedBlackTreeMetrics<RedBlackTree>().calcInsert(arr, size, step, outfile);
            SplayTreeMetrics<SplayTree>().calcInsert(arr, size, step, outfile);
            break;
        case FIND:
            BinarySearchTreeMetrics<BinarySearchTree>().calcFind(arr, size, step, outfile);
            AVLTreeMetrics<AVLTree>().calcFind(arr, size, step, outfile);
            RedBlackTreeMetrics<RedBlackTree>().calcFind(arr, size, step, outfile);
            SplayTreeMetrics<SplayTree>().calcFind(arr, size, step, outfile);
            break;
        default: throw invalid_argument("Unrecognized metric type.");
    }

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
    map<string, tuple<bool, MetricType>> functionMap;
    functionMap["orderedInsert"] = make_tuple(true, INSERT);
    functionMap["randomInsert"] = make_tuple(false, INSERT);
    functionMap["orderedFind"] = make_tuple(true, FIND);
    functionMap["randomFind"] = make_tuple(false, FIND);

    if (functions == NULL) {
        map<string, tuple<bool, MetricType>>::iterator it = functionMap.begin();
        while (it != functionMap.end()) {
            tuple<bool, MetricType> params = it->second;
            runMetric(size, step, get<0>(params), get<1>(params));
            it++;
        }
    } else {
        char* function;
        function = strtok(functions, " ");
        while (function != NULL) {
            if (functionMap.count(function)) {
                tuple<bool, MetricType> params = functionMap[function];
                runMetric(size, step, get<0>(params), get<1>(params));
            } else {
                cout << endl << "Function " << function << " not found, skipping..." << endl;
            }
            function = strtok(NULL, " ");
        }
    }
    cout << endl;

    return 0;
}
