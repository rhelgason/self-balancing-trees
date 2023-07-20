# self-balancing-trees
Implementations and comparisons of various self-balancing trees.

## Tree Implementations

### [Binary Search Tree](https://en.wikipedia.org/wiki/Binary_search_tree)

<p align="center">
  <img src="https://github.com/rhelgason/self-balancing-trees/blob/main/img/binary_search_tree.png" alt="binary search tree"/>
</p>

This is the most basic binary tree. The key of each tree node is greater than all the keys in the node's left subtree and less than all the keys in the node's right subtree. No balancing is done during insertion or deletion, so this tree is generally inefficient when using larger data sets.

### [AVL Tree](https://en.wikipedia.org/wiki/AVL_tree)

<p align="center">
  <img src="https://github.com/rhelgason/self-balancing-trees/blob/main/img/avl_tree.png" alt="avl tree"/>
</p>

For every tree node in an AVL tree, the height of its two subtrees differ by no more than one. If this property ever becomes false during insertion or deletion, a series of rotations are performed to make the property true again. AVL trees are generally often slower during insertions and deletions because they perform ensure such strict balancing, but this guarantees optimal performance when searching for tree nodes.

### [Red-Black Tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree)

<p align="center">
  <img src="https://github.com/rhelgason/self-balancing-trees/blob/main/img/red_black_tree.png" alt="red-black tree"/>
</p>

Every node in a red-black tree also contains a single bit, representing its color, that helps with balancing the tree. The following properties always hold true:

- Every node is either red or black
- All empty leaves are black
- A red node cannot have a red child
- Every path from a given node to any of its descendant empty leaves goes through the same number of black nodes

Red-black trees are slightly faster during insertions and deletions than AVL trees because they perform fewer rotations. However, they are therefore less efficient when searching for tree nodes due to a less strict balancing.

### [Splay Tree](https://en.wikipedia.org/wiki/Splay_tree)

Splay trees balance themselves by moving recently accessed tree nodes nearer to the root. This allows splay trees to perform very well in cases where nodes need to be consistently accessed and suffer in cases where nodes are randomly accessed. For example, a splay tree could very effectively be used as a sort of caching algorithm.

## Findings (WIP)

### Ordered Insert: insert keys in numeric order

### Random Insert: insert keys in random order

### Ordered Find: find nodes while inserting keys in numeric order

### Random Find: find nodes while inserting keys in random order

## Usage
The program provides a main entrypoint for running all of the metrics on each of the tree implementations. This can be run with `./bin/main` and a few optional flags:

- `-s` (int): defines the number of tree nodes that should be included in the metric
- `-t` (int): defines the steps size for the metric output
- `-f` (string): defines the metrics that should be run for each tree. Currently functionality includes the following functions:
  - orderedInsert: insert tree nodes with an increasing int value
  - randomInsert: insert tree nodes with random int values
  - orderedFind: find a random int when tree nodes are inserted in increasing int order
  - randomFind: find a random int when tree niodes are inserted in random order

Sample usage: `./bin/main -s 1000 -t 50 -f "orderedInsert randomInsert"`

A Makefile has also been included in the top directory with a few basic commands. To build all of the files for running the metrics, use the default `make build` command. Run all of the metrics with default size and step using the `make run` command. To run all of the unit tests, use the `make test` command. Finally, all of the executable files created during compilation can be removed using `make clean`.
