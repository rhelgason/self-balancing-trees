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
            test_get_min();
            test_get_max();
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
            assert(*(tree.getMin()) == 5);
            assert(*(tree.getMax()) == 5);

            tree.insert(5);

            assert(tree.isValid());
            assert(tree.getSize() == 1);
            assert(tree.getHeight() == 1);
            assert(*(tree.getMin()) == 5);
            assert(*(tree.getMax()) == 5);
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

        void test_get_min() {
            // get minimum on empty and non-empty tree
            print_current_test(__func__);
            T tree = createTree();

            assert(tree.getMin() == NULL);

            tree.insert(43);
            tree.insert(-1);
            tree.insert(7);

            assert(*(tree.getMin()) == -1);
        }

        void test_get_max() {
            // get maximum on empty and non-empty tree
            print_current_test(__func__);
            T tree = createTree();

            assert(tree.getMax() == NULL);

            tree.insert(-99);
            tree.insert(-81);
            tree.insert(-33);

            assert(*(tree.getMax()) == -33);
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
            // repeatedly left insert
            print_current_test(__func__);
            T tree = createTree();
            for (int i = 99; i >= 0; i--) {
                tree.insert(i);
            }

            assert(tree.isValid());
            assert(tree.getSize() == 100);
            assert(tree.getHeight() == height);
            assert(*(tree.getMin()) == 0);
            assert(*(tree.getMax()) == 99);
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
            assert(*(tree.getMin()) == 0);
            assert(*(tree.getMax()) == 99);
        }

        void test_left_left_insertion() {
            // self balancing left left case
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(34);
            tree.insert(234);
            tree.insert(2);
            tree.insert(-76);
            tree.insert(29);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);

            tree.insert(-3);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
        }

        void test_left_right_insertion() {
            // self balancing left right case
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(55);
            tree.insert(87);
            tree.insert(32);
            tree.insert(0);
            tree.insert(40);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);

            tree.insert(33);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
        }

        void test_right_right_insertion() {
            // self balancing right right case
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(-10);
            tree.insert(-66);
            tree.insert(0);
            tree.insert(-4);
            tree.insert(3);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);

            tree.insert(24932);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
        }

        void test_right_left_insertion() {
            // self balancing right left case
            print_current_test(__func__);
            T tree = createTree();
            tree.insert(-953);
            tree.insert(-2270);
            tree.insert(-477);
            tree.insert(14);
            tree.insert(-612);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);

            tree.insert(-505);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
        }

        void test_left_left_deletion() {
            // self balancing left left case
            print_current_test(__func__);
            T tree = createTree();
            for (int i = 0; i < 15; i++) {
                tree.insert(i);
            }

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(4);
            tree.remove(6);
            tree.remove(8);
            tree.remove(10);
            tree.remove(12);
            tree.remove(14);
            tree.remove(9);

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(13);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
        }

        void test_left_right_deletion() {
            // self balancing left right case
            print_current_test(__func__);
            T tree = createTree();
            for (int i = 0; i < 15; i++) {
                tree.insert(i);
            }

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(0);
            tree.remove(2);
            tree.remove(8);
            tree.remove(10);
            tree.remove(12);
            tree.remove(14);
            tree.remove(9);

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(13);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
        }

        void test_right_right_deletion() {
            // self balancing right right case
            print_current_test(__func__);
            T tree = createTree();
            for (int i = 0; i < 15; i++) {
                tree.insert(i);
            }

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(0);
            tree.remove(2);
            tree.remove(4);
            tree.remove(6);
            tree.remove(8);
            tree.remove(10);
            tree.remove(1);

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(5);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
        }

        void test_right_left_deletion() {
            // self balancing right left case
            print_current_test(__func__);
            T tree = createTree();
            for (int i = 0; i < 15; i++) {
                tree.insert(i);
            }

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(0);
            tree.remove(2);
            tree.remove(4);
            tree.remove(6);
            tree.remove(12);
            tree.remove(14);
            tree.remove(1);

            assert(tree.isValid());
            assert(tree.getHeight() == 4);

            tree.remove(5);

            assert(tree.isValid());
            assert(tree.getHeight() == 3);
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
            test_all_left_insertions(7);
            test_all_right_insertions(7);
            test_left_left_insertion();
            test_left_right_insertion();
            test_right_right_insertion();
            test_right_left_insertion();
            test_left_left_deletion();
            test_left_right_deletion();
            test_right_right_deletion();
            test_right_left_deletion();
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
