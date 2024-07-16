# System Programing 2 - assignmant 4

This project is an implementation of a tree data structure with various traversal iterators (Pre-Order, Post-Order, In-Order, BFS, DFS, and Heap). It includes a graphical user interface (GUI) for visualizing the tree using SFML.

## Table of Contents
- [Features](#features)
    - [Complex Numbers](#complex-numbers)
    - [Node](#node)
    - [Tree](#tree)
    - [Traversal Iterators](#traversal-iterators)
    - [GUI Visualization](#gui-visualization)
- [How to run](#how-to-run)
- [Tests](#tests)

## Features
There main features in this project are:

* **Complex Numbers** 
* **Node** 
* **Tree** 
* **Traversal Iterators** 
* **GUI Visualization**

### Complex Numbers
The Complex class represents complex numbers and provides functionality for comparison operations and printing.

**Key Functions:**

* **Constructor:** Initializes the real and imaginary parts of the complex number.
* **Comparison:** Provides comparison operators (`==`, `!=`, `>`, `<`) for sorting and heap operations.
* **String Representation:** The `to_string` function constructs a string with the real and imaginary parts formatted to one decimal place.
* **Print:** Overloads the `<<` operator for easy printing of complex numbers.

### Node
The Node class is a generic class template for tree nodes. Each node contains a value and a list of children.

**Key Functions:**

* **Constructor:** Initializes the node with a value.
* **Add Child:** Adds a child node to the current node.
* **Getters:** Provides access to the node's value and children.

### Tree
The Tree class is a generic class template for tree structures. It supports multiple arities, with a default binary tree implementation.

**Key Functions:**

* **Constructor:** Initializes an empty tree.
* **Add Root:** Sets the root node of the tree.
* **Add Sub Node:** Adds a child node to a specified parent node.

### Traversal Iterators
The traversal iterators allow for easy iteration over the tree nodes in different orders.

**Traversal Types:**
* **Pre-Order:** Visits the root node first, then recursively visits each subtree. Pre-Order only works with 2-ary trees.
* **Post-Order:** Recursively visits each subtree, then visits the root node. Post-Order only works with 2-ary trees.
* **In-Order:** Recursively visits the left subtree, visits the root node, then recursively visits the right subtree. In-Order only works with 2-ary trees.
* **BFS (Breadth-First Search):** Visits nodes level by level.
* **DFS (Depth-First Search):** Visits nodes by diving deep into each branch before backtracking.
* **Heap:** Converts the tree into a heap and visits nodes in the heap order.

### GUI Visualization
The project includes a graphical user interface for visualizing the tree using SFML. The GUI displays the tree structure in a window, allowing for an interactive view of the tree's layout.

## How To Run
To compile the project, use the following commands in your terminal:

```sh
make
```
This command will compile all necessary files and generate the program, which includes compiling the main program (`demo`) and tests (`test`).

```sh
make tree
```
This command will compile the main program (`demo`) and then runs it (`./demo`).


## Tests
This project includes tests to verify the correctness of the tree operations and traversal iterators. The tests are implemented using the `doctest.h` framework.

To run the tests:
```sh
make test
```
```sh
./test
```
This command compiles the test program (`test`). After compiling, running `./test` will execute the test suite.




