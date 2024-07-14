#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "complex.hpp"
#include "node.hpp"
#include "tree.hpp"

TEST_CASE("Testing Complex class")
{
    Complex c1(1, 2);
    Complex c2(3, 4);
    Complex c3(4, 6);
    Complex c4(2, 2);
    Complex c5(1, 2);

    CHECK(c1.get_real() == 1);
    CHECK(c1.get_imag() == 2);

    CHECK((c1 + c2) == c3);
    CHECK((c1 - c2) == c4);
    CHECK((c1 * c2) == Complex(-5, 10));
    CHECK((c1 / c2) == Complex(0.44, 0.08));

    CHECK(c1 == c5);
    CHECK(c1 != c2);
}

TEST_CASE("Tree Iterators") {
    // Create nodes
    Node<float>* root = new Node<float>(1.1);
    Node<float>* node2 = new Node<float>(1.2);
    Node<float>* node3 = new Node<float>(1.3);
    Node<float>* node4 = new Node<float>(1.4);
    Node<float>* node5 = new Node<float>(1.5);
    Node<float>* node6 = new Node<float>(1.6);

    Tree<float, 3> tree;

    tree.add_root(root);
    tree.add_sub_node(root, node2);
    tree.add_sub_node(root, node3);
    tree.add_sub_node(node2, node4);
    tree.add_sub_node(node2, node5);
    tree.add_sub_node(node3, node6);


    SUBCASE("BFS Iterator") {

        auto it = tree.begin_bfs_scan();
        CHECK(it->get_value() == 1.1);
        ++it;
        CHECK(it->get_value() == 1.2);
        ++it;
        CHECK(it->get_value() == 1.3);
        ++it;
        CHECK(it->get_value() == 1.4);
        ++it;
        CHECK(it->get_value() == 1.5);
        ++it;
        CHECK(it->get_value() == 1.6);
        ++it;
        CHECK(it == tree.end_bfs_scan());
    }

    // SUBCASE("DFS Iterator") {

    // }

}