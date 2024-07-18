// 324460682 yocheved@davidowitz.net

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

    CHECK(c1 == c5);
    CHECK(c1 != c2);

    SUBCASE("Complex tree")
    {
        Node<Complex> root(Complex(1, 2));
        Node<Complex> n1(Complex(3, 4));
        Node<Complex> n2(Complex(5, 6));
        Node<Complex> n3(Complex(7, 8));
        Node<Complex> n4(Complex(3, 1));
        Node<Complex> n5(Complex(2, 10));

        Tree<Complex, 2> tree;

        tree.add_root(&root);
        tree.add_sub_node(&root, &n1);
        tree.add_sub_node(&root, &n2);
        tree.add_sub_node(&n1, &n3);
        tree.add_sub_node(&n1, &n4);
        tree.add_sub_node(&n2, &n5);

        auto it = tree.begin_bfs_scan();
        CHECK(it->get_value() == Complex(1, 2));
        ++it;
        CHECK(it->get_value() == Complex(3, 4));
        ++it;
        CHECK(it->get_value() == Complex(5, 6));
        ++it;
        CHECK(it->get_value() == Complex(7, 8));
        ++it;
        CHECK(it->get_value() == Complex(3, 1));
        ++it;
        CHECK(it->get_value() == Complex(2, 10));
        ++it;
        CHECK(it == tree.end_bfs_scan());

    }
}


TEST_CASE("Binary tree"){

    Node<int> root(1);
    Node<int> node2(2);
    Node<int> node3(3);
    Node<int> node4(4);
    Node<int> node5(5);
    Node<int> node6(6);

    Tree<int, 2> tree;

    tree.add_root(&root);
    tree.add_sub_node(&root, &node2);
    tree.add_sub_node(&root, &node3);
    tree.add_sub_node(&node2, &node4);
    tree.add_sub_node(&node2, &node5);
    tree.add_sub_node(&node3, &node6);

    SUBCASE("To many children"){

        Node<int> node7(7);

        CHECK_THROWS(tree.add_sub_node(&root, &node7));
        CHECK_THROWS(tree.add_sub_node(&node2, &node7));

    }

    SUBCASE("BFS Iterator") {

        auto it = tree.begin_bfs_scan();
        CHECK(it->get_value() == 1);
        ++it;
        CHECK(it->get_value() == 2);
        ++it;
        CHECK(it->get_value() == 3);
        ++it;
        CHECK(it->get_value() == 4);
        ++it;
        CHECK(it->get_value() == 5);
        ++it;
        CHECK(it->get_value() == 6);
        ++it;
        CHECK(it == tree.end_bfs_scan());
    }

    SUBCASE("Pre Order Iterator") {

        auto it = tree.begin_pre_order();
        CHECK(it->get_value() == 1);
        ++it;
        CHECK(it->get_value() == 2);
        ++it;
        CHECK(it->get_value() == 4);
        ++it;
        CHECK(it->get_value() == 5);
        ++it;
        CHECK(it->get_value() == 3);
        ++it;
        CHECK(it->get_value() == 6);
        ++it;
        CHECK(it == tree.end_pre_order());
    }

    SUBCASE("Post Order Iterator") {

        auto it = tree.begin_post_order();
        CHECK(it->get_value() == 4);
        ++it;
        CHECK(it->get_value() == 5);
        ++it;
        CHECK(it->get_value() == 2);
        ++it;
        CHECK(it->get_value() == 6);
        ++it;
        CHECK(it->get_value() == 3);
        ++it;
        CHECK(it->get_value() == 1);
        ++it;
        CHECK(it == tree.end_post_order());
    }


    SUBCASE("In Order Iterator") {

        auto it = tree.begin_in_order();
        CHECK(it->get_value() == 4);
        ++it;
        CHECK(it->get_value() == 2);
        ++it;
        CHECK(it->get_value() == 5);
        ++it;
        CHECK(it->get_value() == 1);
        ++it;
        CHECK(it->get_value() == 6);
        ++it;
        CHECK(it->get_value() == 3);
        ++it;
        CHECK(it == tree.end_in_order());
    }

    SUBCASE("DFS Iterator") {

        auto it = tree.begin_dfs_scan();
        CHECK(it->get_value() == 1);
        ++it;
        CHECK(it->get_value() == 2);
        ++it;
        CHECK(it->get_value() == 4);
        ++it;
        CHECK(it->get_value() == 5);
        ++it;
        CHECK(it->get_value() == 3);
        ++it;
        CHECK(it->get_value() == 6);
        ++it;
        CHECK(it == tree.end_dfs_scan());
    }

    SUBCASE("Heap Iterator") {

        auto it = tree.begin_make_heap_scan();

        CHECK(it->get_value() == 1);
        ++it;
        CHECK(it->get_value() == 2);
        ++it;
        CHECK(it->get_value() == 3);
        ++it;
        CHECK(it->get_value() == 4);
        ++it;
        CHECK(it->get_value() == 5);
        ++it;
        CHECK(it->get_value() == 6);
        ++it;
        CHECK(it == tree.end_make_heap_scan());

    }

}

TEST_CASE("Empty tree"){

    Tree<int, 2> tree;

    CHECK(tree.get_root() == nullptr);

    CHECK(tree.begin_bfs_scan() == tree.end_bfs_scan());
    CHECK(tree.begin_pre_order() == tree.end_pre_order());
    CHECK(tree.begin_post_order() == tree.end_post_order());
    CHECK(tree.begin_in_order() == tree.end_in_order());
    CHECK(tree.begin_dfs_scan() == tree.end_dfs_scan());
    CHECK(tree.begin_make_heap_scan() == tree.end_make_heap_scan());

}

TEST_CASE("3-ary tree"){

    Node<double> root(1.1);
    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);
    Node<double> n6(1.7);

    Tree<double, 3> tree;

    tree.add_root(&root);
    tree.add_sub_node(&root, &n1);
    tree.add_sub_node(&root, &n2);
    tree.add_sub_node(&root, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);
    tree.add_sub_node(&n3, &n6);

    SUBCASE("To many children"){

        Node<double> n7(1.8);

        CHECK_THROWS(tree.add_sub_node(&root, &n7));

    }

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
        CHECK(it->get_value() == 1.7);
        ++it;
        CHECK(it == tree.end_bfs_scan());
    }

    SUBCASE("DFS Iterator"){
        auto it = tree.begin_dfs_scan();
        CHECK(it->get_value() == 1.1);
        ++it;
        CHECK(it->get_value() == 1.2);
        ++it;
        CHECK(it->get_value() == 1.5);
        ++it;
        CHECK(it->get_value() == 1.3);
        ++it;
        CHECK(it->get_value() == 1.6);
        ++it;
        CHECK(it->get_value() == 1.4);
        ++it;
        CHECK(it->get_value() == 1.7);
        ++it;
        CHECK(it == tree.end_dfs_scan());
    }

    SUBCASE("Iterators- throwing exception"){

        CHECK_THROWS(tree.begin_pre_order());
        CHECK_THROWS(tree.begin_post_order());
        CHECK_THROWS(tree.begin_in_order());
        CHECK_THROWS(tree.begin_make_heap_scan());
    }

}

TEST_CASE("Heap"){

    Node<int> root(1);
    Node<int> node2(3);
    Node<int> node3(54);
    Node<int> node4(2);
    Node<int> node5(7);
    Node<int> node6(67);

    Tree<int, 2> tree;

    tree.add_root(&root);
    tree.add_sub_node(&root, &node2);
    tree.add_sub_node(&root, &node3);
    tree.add_sub_node(&node3, &node4);
    tree.add_sub_node(&node3, &node6);
    tree.add_sub_node(&node6, &node5);

    auto it = tree.begin_make_heap_scan();
    CHECK(it->get_value() == 1);
    ++it;
    CHECK(it->get_value() == 2);
    ++it;
    CHECK(it->get_value() == 3);
    ++it;
    CHECK(it->get_value() == 7);
    ++it;
    CHECK(it->get_value() == 54);
    ++it;
    CHECK(it->get_value() == 67);
    ++it;
    CHECK(it == tree.end_make_heap_scan());

    Tree<int, 3> tree2;

    tree2.add_root(&root);
    tree2.add_sub_node(&root, &node2);
    tree2.add_sub_node(&root, &node3);
    tree2.add_sub_node(&root, &node4);
    tree2.add_sub_node(&node2, &node5);
    tree2.add_sub_node(&node2, &node6);
    
    CHECK_THROWS(tree2.begin_make_heap_scan());

}
