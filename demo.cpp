/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "node.hpp"
#include "tree.hpp"
#include "complex.hpp"

using namespace std;

int main()
{

    cout << "New binary tree" << endl;
    Tree<double> tree; // Binary tree that contains doubles.

    Node<double> root_node(1.1);

    tree.add_root(&root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(&root_node, &n1);
    tree.add_sub_node(&root_node, &n2);
    tree.add_sub_node(&n1, &n3);
    tree.add_sub_node(&n1, &n4);
    tree.add_sub_node(&n2, &n5);

    tree.runSFML();
   
    // // The tree should look like:
    // /**
    //  *       root = 1.1
    //  *     /       \
    //  *    1.2      1.3
    //  *   /  \      /
    //  *  1.4  1.5  1.6
    //  */

    cout<<"Printing pre order:"<<endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout<<"Printing post order:"<<endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
    {
        cout << node->get_value() << ", ";
        // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    } 
    cout << endl;

    cout<<"Printing in order:"<<endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
    cout << endl;

    cout<<"Printing BFS:"<<endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    cout<<"Printing DFS:"<<endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout<<"Printing Heap:"<<endl;
    for(auto node = tree.begin_make_heap_scan(); node != tree.end_make_heap_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    cout << endl;

    cout<<"tree:"<<endl;
    for (auto node : tree)
    {
        cout << node << ", ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;


    cout << "New 3-ary tree" << endl;

    Tree<double,3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(&root_node);
    three_ary_tree.add_sub_node(&root_node, &n1);
    three_ary_tree.add_sub_node(&root_node, &n2);
    three_ary_tree.add_sub_node(&root_node, &n3);
    three_ary_tree.add_sub_node(&n1, &n4);
    three_ary_tree.add_sub_node(&n2, &n5);

    three_ary_tree.runSFML();

    //  // The tree should look like:
    // /**
    //  *       root = 1.1
    //  *     /      |     \
    //  *    1.2    1.3    1.4
    //  *   /        |
    //  *  1.5      1.6
    //  */

    cout<<"Printing BFS:"<<endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    cout << endl;

    cout<<"Printing DFS:"<<endl;
    for (auto node = three_ary_tree.begin_dfs_scan(); node != three_ary_tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1, 1.2, 1.5, 1.3, 1.6, 1.4
    cout << endl;

    cout << "New complex 2-ary tree" << endl;
    Tree<Complex, 2> two_ary_complex_tree; 

    Node<Complex> root_complex_node(Complex(1.1, 2));
    Node<Complex> n1_complex(Complex(3, 4));
    Node<Complex> n2_complex(Complex(5, 6));
    Node<Complex> n3_complex(Complex(7, 8));
    Node<Complex> n4_complex(Complex(3, 1));
    Node<Complex> n5_complex(Complex(2, 10));


    two_ary_complex_tree.add_root(&root_complex_node);
    two_ary_complex_tree.add_sub_node(&root_complex_node, &n1_complex);
    two_ary_complex_tree.add_sub_node(&root_complex_node, &n2_complex);
    two_ary_complex_tree.add_sub_node(&n1_complex, &n3_complex);
    two_ary_complex_tree.add_sub_node(&n1_complex, &n4_complex);
    two_ary_complex_tree.add_sub_node(&n4_complex, &n5_complex);

    two_ary_complex_tree.runSFML();

    //  // The tree should look like:   
    // /**
    //  *       root = 1.1 + 2i
    //  *     /         |
    //  *    3 + 4i    5 + 6i
    //   *   /     |
    //  *  7 + 8i  3 + i
    //  *           |
    //  *          2 + 10i
    //  */


    cout<<"Printing pre order:"<<endl;
    for (auto node = two_ary_complex_tree.begin_pre_order(); node != two_ary_complex_tree.end_pre_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1 + 2i, 3 + 4i, 7 + 8i, 3 + i, 2 + 10i, 5 + 6i
    cout << endl;

    cout<<"Printing post order:"<<endl;
    for (auto node = two_ary_complex_tree.begin_post_order(); node != two_ary_complex_tree.end_post_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 7 + 8i, 2 + 10i, 3 + 1i, 3 + 4i, 5 + 6i, 1.1 + 2i,
    cout << endl;

    cout<<"Printing in order:"<<endl;
    for (auto node = two_ary_complex_tree.begin_in_order(); node != two_ary_complex_tree.end_in_order(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 7 + 8i, 3 + 4i, 2 + 10i, 3 + i, 1.1 + 2i, 5 + 6i
    cout << endl;

    cout<<"Printing BFS:"<<endl;
    for (auto node = two_ary_complex_tree.begin_bfs_scan(); node != two_ary_complex_tree.end_bfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1 + 2i, 3 + 4i, 5 + 6i, 7 + 8i, 3 + i, 2 + 10i
    cout << endl;

    cout<<"Printing DFS:"<<endl;
    for (auto node = two_ary_complex_tree.begin_dfs_scan(); node != two_ary_complex_tree.end_dfs_scan(); ++node)
    {
        cout << node->get_value() << ", ";
    } // prints: 1.1 + 2i, 3 + 4i, 7 + 8i, 3 + i, 2 + 10i, 5 + 6i
    cout << endl;


    return 0;


    
}
