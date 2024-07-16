#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "complex.hpp"
#include <SFML/Graphics.hpp>


template <typename T>
class Node{

    private:
    static int id_counter;
    int id;

    public:
    T value;
    std::vector<Node<T>*> children;

    Node(T v): id(id_counter++), value(v){}

    const T &get_value() const{
        return value;
    }

    T &get_value(){
        return value;
    }

    void add_child(Node<T>* child){
        children.push_back(child);
    }

    void remove_children(){
        children.clear();
    }

    int getId() const {
        return id;
    }
};

template <typename T>
int Node<T>::id_counter = 0;

#endif