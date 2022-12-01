#include <iostream>
#include <assert.h>
#include "BinarySearchTree.h"
#include "AVLTree.h"
using namespace std;

template <typename T>
class BaseTests {
    protected:
        virtual string getName() = 0;
        virtual T createTree() = 0;
        virtual void test_tree_specific() = 0;

    public:
        void print_current_test(string func) {
            cout << "   Running " << func << " test..." << endl;
        }

        void test_all() {
            cout << endl;
            cout << "=======================================================" << endl;
            cout << " Running " << getName() << " tests..." << endl;

            test_empty_tree();
            test_insert();
            test_to_string();
            test_remove();
            test_one_child_remove();
            test_both_children_remove();
            test_includes();
            test_purge();

            test_tree_specific();

            cout << " All " << getName() << " tests complete." << endl;
            cout << "=======================================================" << endl;
        }

        void test_empty_tree() {
            // instantiate empty tree
            print_current_test(__func__);
            T tree = createTree();

            assert(tree.isValid());
            assert(tree.getSize() == 0);
            assert(tree.getHeight() == 0);
            assert(tree.getMin() == NULL);
            assert(tree.getMax() == NULL);
        }

        void test_insert() {
            // insert single node
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(5);

            assert(tree.isValid());
            assert(tree.getSize() == 1);
            assert(tree.getHeight() == 1);
            assert(tree.getMin()->data == 5);
            assert(tree.getMax()->data == 5);

            tree.insert(5);

            assert(tree.isValid());
            assert(tree.getSize() == 1);
            assert(tree.getHeight() == 1);
            assert(tree.getMin()->data == 5);
            assert(tree.getMax()->data == 5);
        }

        void test_to_string() {
            // test sorted array
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(10);
            tree.insert(7);
            tree.insert(19);
            tree.insert(8);
            tree.insert(9);

            string str1 = tree.toString();
            string str2 = "7, 8, 9, 10, 19";
            assert(str1.compare(str2) == 0);
        }

        void test_remove() {
            // remove non-existent and existent node
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(10);
            tree.remove(8);

            assert(tree.isValid());
            assert(tree.getSize() == 1);
            assert(tree.getHeight() == 1);

            tree.remove(10);

            assert(tree.isValid());
            assert(tree.getSize() == 0);
            assert(tree.getHeight() == 0);
            assert(tree.getMin() == NULL);
            assert(tree.getMax() == NULL);
            assert(!tree.includes(10));
        }

        void test_one_child_remove() {
            // remove node with one child
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(10);
            tree.insert(12);
            tree.remove(12);

            assert(tree.isValid());
            assert(tree.getSize() == 1);
            assert(tree.getHeight() == 1);

            tree.insert(6);
            tree.remove(6);

            assert(tree.isValid());
            assert(tree.getSize() == 1);
            assert(tree.getHeight() == 1);
        }

        void test_both_children_remove() {
            // remove node with two children
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(10);
            tree.insert(12);
            tree.insert(11);
            tree.insert(20);
            tree.insert(19);
            tree.remove(12);

            assert(tree.isValid());
            assert(tree.getSize() == 4);
            assert(tree.getHeight() == 3);
        }

        void test_includes() {
            // check whether data exists in tree
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(48);
            tree.insert(99);
            tree.insert(2);
            tree.insert(-1);
            tree.insert(13);

            assert(!tree.includes(57));
            assert(tree.includes(13));
            assert(tree.includes(-1));
        }

        void test_purge() {
            // ensure tree empties
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(48);
            tree.insert(99);
            tree.insert(2);
            tree.insert(-1);
            tree.insert(13);
            tree.purge();

            assert(tree.isValid());
            assert(tree.getSize() == 0);
            assert(tree.getHeight() == 0);
            assert(tree.getMin() == NULL);
            assert(tree.getMax() == NULL);
        }

        void test_all_left_insertions(int height) {
            // repeatedly right insert
            print_current_test(__func__);
            T tree = createTree();
            for (int i = 99; i >= 0; i--) {
                tree.insert(i);
            }

            assert(tree.isValid());
            assert(tree.getSize() == 100);
            assert(tree.getHeight() == height);
            assert(tree.getMin()->data == 0);
            assert(tree.getMax()->data == 99);
        }

        void test_all_right_insertions(int height) {
            // repeatedly right insert
            print_current_test(__func__);
            T tree = createTree();
            for (int i = 0; i < 100; i++) {
                tree.insert(i);
            }

            assert(tree.isValid());
            assert(tree.getSize() == 100);
            assert(tree.getHeight() == height);
            assert(tree.getMin()->data == 0);
            assert(tree.getMax()->data == 99);
        }

        virtual ~BaseTests() {}
};

template<class T>
class BinarySearchTreeTests : public BaseTests<BinarySearchTree> {
    protected:
        string getName() override {
            return "Binary Search Tree";
        }

        T createTree() override {
            return BinarySearchTree();
        }

        void test_tree_specific() override {
            test_all_left_insertions(100);
            test_all_right_insertions(100);
        }

    public:
        BinarySearchTreeTests() {}
        ~BinarySearchTreeTests() {}
};

template<class T>
class AVLTreeTests : public BaseTests<AVLTree> {
    protected:
        string getName() override {
            return "AVL Tree";
        }

        T createTree() override {
            return AVLTree();
        }

        void test_tree_specific() override {
            // MAKE AVL TREE SPECIFIC TREES
            test_all_left_insertions(7);
            test_all_right_insertions(7);
        }

    public:
        AVLTreeTests() {}
        ~AVLTreeTests() {}
};

int main(int argc, char *argv[]) {
    BinarySearchTreeTests<BinarySearchTree> tester1 = BinarySearchTreeTests<BinarySearchTree>();
    tester1.test_all();

    AVLTreeTests<AVLTree> tester2 = AVLTreeTests<AVLTree>();
    tester2.test_all();
    cout << endl;
}
