
#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <sstream> 
#include <iomanip>
#include <algorithm>
#include "node.hpp"
#include <SFML/Graphics.hpp>


template <typename T, size_t K = 2>
class Tree{

    protected:
    Node<T>* root;

    public:
    Tree(): root(nullptr){};

    ~Tree() {

        for(auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it){
            it->remove_children();
        }
        root = nullptr;
    }

    Node<T>* get_root(){
        return root;
    }

    void add_root(Node<T>* newRoot){
        this->root = newRoot;
    }

    void add_sub_node(Node<T>* parent, Node<T>* child){
        if (!parent || !child) return;
        if(parent->children.size() < K){ 
            for(Node<T>* children : parent->children){
                if(children == child){
                    return;
                }
            }
            parent->add_child(child);
        }
        else{
            throw std::invalid_argument("Parent has too many children");
        }
    }
    
    void remove_sub_node(Node<T> parent, Node<T> child){
        if(!parent) return;
        parent.remove_child(child);
    }


    Node<T>* get_sub_node(Node<T> parent, T value){
        for(int i = 0; i < parent.children.size(); i++){
            if(parent.children[i]->value == value){
                return parent.children[i];
            }
        }
        return nullptr;
    }

    //////////////////////////////////////////////////////////////Iterators//////////////////////////////////////////////////////////////////

    class InOrderIterator{

        private:
        std::stack<Node<T>*> stack;
        Node<T>* current;

        void pushLeftmost(Node<T>* node) {
            while (node != nullptr) {
                stack.push(node);
                if (node->children.empty()) {
                    node = nullptr;
                } else {
                    node = node->children[0];
                }
            }
        }

        public:
        InOrderIterator(Node<T>* root) : current(nullptr) {
            pushLeftmost(root);
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            }
        }

        T& operator*() {
            return current->get_value();
        }

        Node<T>* operator->() {
            return current;
        }

        InOrderIterator& operator++() {
            if (current == nullptr) return *this;
            Node<T>* node = current;
            if (node->children.size() > 1) {
                pushLeftmost(node->children[1]);
            }
            if (!stack.empty()) {
                current = stack.top();
                stack.pop();
            } else {
                current = nullptr;
            }
            return *this;
        }

        bool operator==(const InOrderIterator& other) const {
            return current == other.current;
        }

        bool operator!=(const InOrderIterator& other) const {
            return !(*this == other);
        }
    };



    class PreOrderIterator{

        private:
        std::stack<Node<T>*> stack;

        public:
        PreOrderIterator(Node<T>* root) {
            if (root) {
                stack.push(root);
            }
        }

        T& operator*() const {
            return stack.top()->get_value();
        }

        Node<T>* operator->() const {
            return stack.top();
        }

        PreOrderIterator& operator++() {
            if (!stack.empty()) {
                Node<T>* node = stack.top();
                stack.pop();
                for (int i = node->children.size() - 1; i >= 0; --i) {
                    stack.push(node->children[i]);
                }
            }
            return *this;
        }

        bool operator==(const PreOrderIterator& other) const {
            if (stack.empty() && other.stack.empty()) {
                return true;
            }
            if (stack.empty() || other.stack.empty()) {
                return false;
            }
            return stack.top() == other.stack.top();
        }

        bool operator!=(const PreOrderIterator& other) const {
            return !(*this == other);
        }
    };


    class PostOrderIterator{

        private:
        std::stack<Node<T>*> stack;
        std::vector<int> visitedIds;

        void pushLeftmostNode(Node<T>* node) {
            while (node != nullptr) {
                stack.push(node);
                if (node->children.empty()) {
                    node = nullptr;
                } else {
                    node = node->children[0];
                }
            }
        }

        public:
        PostOrderIterator() : stack(), visitedIds() {}

        PostOrderIterator(Node<T>* root) {
            pushLeftmostNode(root);
        }

        T& operator*() {
            return stack.top()->get_value();
        }

        Node<T>* operator->() {
            return stack.top();
        }

        PostOrderIterator& operator++() {
            if(stack.empty()){
                return *this;
            }

            Node<T>* node = stack.top();
            stack.pop();
            visitedIds.push_back(node->getId());

            if (!stack.empty()) {
                Node<T>* parent = stack.top();
                auto it = std::find(parent->children.begin(), parent->children.end(), node);
                if (it != parent->children.end() && ++it != parent->children.end()) {
                    pushLeftmostNode(*it);
                }
            }

            return *this;
        }

        bool operator==(const PostOrderIterator& other) const{
            return stack == other.stack;
        }

        bool operator!=(const PostOrderIterator& other) const{
            return !(*this == other);
        }
    };

    class BFSIterator{ 

        private:
        std::queue<Node<T>*> myQueue;

        public:
        BFSIterator(Node<T>* root) {
            if (root) {
                myQueue.push(root);
            }
        }

        T& operator*() {
            return myQueue.front()->get_value(); 
        }

        Node<T>* operator->() {
            return myQueue.front(); 
        }

        BFSIterator& operator++() {
            if(!myQueue.empty()){
                Node<T>* node = myQueue.front();
                myQueue.pop();  

                if(!node->children.empty()){
                    for (Node<T>* child : node->children) {
                        if(child){
                            myQueue.push(child);
                        }
                    }
                }
            }
            return *this;
        }

        bool operator==(const BFSIterator& other) const{
            if (myQueue.empty() && other.myQueue.empty()) {
                return true;
            }
            if (myQueue.empty() || other.myQueue.empty()) {
                return false;
            }
            return myQueue.front() == other.myQueue.front();
        }

        bool operator!=(const BFSIterator& other) const{
            return !(*this == other); 
        }

    };



    class DFSIterator{

    private:
        std::stack<Node<T>*> stack;  

    public:
        DFSIterator(Node<T>* root) {
            if (root) {
                stack.push(root);   
            }
        }

        T& operator*() {
            return stack.top()->get_value();    
        }

        Node<T>* operator->() {
            return stack.top();    
        }

        DFSIterator& operator++() {
            if (!stack.empty()) {
                Node<T>* node = stack.top();
                stack.pop();   
                for (int i = node->children.size() - 1; i >= 0; --i) {
                    if(node->children[i]){
                        stack.push(node->children[i]);
                    }
                }
            }
            return *this;
        }

        bool operator==(const DFSIterator& other) const{
            if (stack.empty() && other.stack.empty()) {
                return true;
            }
            if (stack.empty() || other.stack.empty()) {
                return false;
            }
            return stack.top() == other.stack.top();  
        }

        bool operator!=(const DFSIterator& other) const{
            return !(*this == other); 
        }

    };


    class HeapIterator{
    private:
        std::vector<Node<T>*> heap;
        int currentId;

    public:
        HeapIterator(Node<T>* root) : currentId(0) {
            if (root == nullptr) {
                currentId = -1; 
                return;
            }

            std::queue<Node<T>*> bfsQueue;
            bfsQueue.push(root);

            while (!bfsQueue.empty()) {
                Node<T>* current = bfsQueue.front();
                bfsQueue.pop();

                heap.push_back(current);
                for (Node<T>* child : current->children) {
                    bfsQueue.push(child);
                }
            }

            std::make_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) {
                return a->get_value() > b->get_value();
            });
        }

        T& operator*() const {
            return heap[currentId]->get_value();
        }

        Node<T>* operator->() const {
            return heap[currentId];
        }

        HeapIterator& operator++() {
            if (currentId >= heap.size()) {
                currentId = -1; 
            } else {
                std::pop_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) {
                    return a->get_value() > b->get_value(); 
                });
                heap.pop_back();
                if (heap.empty()) {
                    currentId = -1; 
                }
            }
            return *this;
        }

        bool operator==(const HeapIterator& other) const {
            if (currentId == -1 && other.currentId == -1) {
                return true;
            }
            return currentId == other.currentId;
        }

        bool operator!=(const HeapIterator& other) const {
            return !(*this == other);
        }
    };


    BFSIterator begin() {
        return begin_bfs_scan();
    }

    BFSIterator end() {
        return end_bfs_scan();
    }

    PreOrderIterator begin_pre_order(){
        if(K == 2){
            return PreOrderIterator(root);
        }
        throw std::invalid_argument("PreOrderIterator only works for binary trees");
    }

   PreOrderIterator end_pre_order(){
        if(K == 2){
            return PreOrderIterator(nullptr);
        }
        throw std::invalid_argument("PreOrderIterator only works for binary trees");
    }

    InOrderIterator begin_in_order(){
        if(K == 2){
            return InOrderIterator(root);
        }
        throw std::invalid_argument("InOrderIterator only works for binary trees");
    }

    InOrderIterator end_in_order(){
        if(K == 2){
            return InOrderIterator(nullptr);
        }
        throw std::invalid_argument("InOrderIterator only works for binary trees");
    }

    PostOrderIterator begin_post_order(){
        if(K == 2){
            return PostOrderIterator(root);
        }
        throw std::invalid_argument("PostOrderIterator only works for binary trees");
    }

    PostOrderIterator end_post_order(){
        if(K == 2){
            return PostOrderIterator(nullptr);
        }
        throw std::invalid_argument("PostOrderIterator only works for binary trees");
    }

    BFSIterator begin_bfs_scan(){
        return BFSIterator(root);
    }

    BFSIterator end_bfs_scan(){
        return BFSIterator(nullptr);
    }

    DFSIterator begin_dfs_scan(){
        return DFSIterator(root);
    }

    DFSIterator end_dfs_scan(){
        return DFSIterator(nullptr);
    }

    HeapIterator begin_make_heap_scan(){
        if(K == 2){
            return HeapIterator(root);
        }
        throw std::invalid_argument("HeapIterator only works for binary trees");  
    }

    HeapIterator end_make_heap_scan(){
        if(K == 2){
        return HeapIterator(nullptr);
        }
        throw std::invalid_argument("HeapIterator only works for binary trees");
    }

    ////////////////////////////////////////////////////////////////Drawing//////////////////////////////////////////////////////////////


    void runSFML() {
        sf::RenderWindow window(sf::VideoMode(1000, 800), "Tree Visualizations");

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            throw std::invalid_argument("Font not found");
        }

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear(sf::Color::White);
            if (root) {
                drawTree(window, root, 0, 0, 400, font);
            } else {
                std::cout << "Tree root is nullptr or empty" << std::endl;
            }
            window.display();
        }
    }

    void drawTree(sf::RenderWindow &window, Node<T>* node, float x, float y, float offset, sf::Font &font) {
        if (!node) {
            return;
        }
        float windowCenterX = window.getSize().x / 2.0f;
        float windowCenterY = 150.0f; 

        float nodeX = windowCenterX + x;
        float nodeY = windowCenterY + y;

        sf::CircleShape circle(30);
        circle.setFillColor(sf::Color::White);
        circle.setOutlineThickness(1);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition(nodeX, nodeY);
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        if constexpr (std::is_same<T, Complex>::value) {
            text.setString(node->get_value().to_string()); 
        } else {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << node->get_value();
            text.setString(ss.str());
        }
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(nodeX + 10, nodeY + 15);
        window.draw(text);

        float childXOffset = offset / 2.0f;
        float childYOffset = 100.0f; 

        for (size_t i = 0; i < node->children.size(); ++i) {
            float childX = x + childXOffset * (i - (node->children.size() - 1) / 2.0f);
            float childY = y + childYOffset;

            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(nodeX + 30, nodeY + 60), sf::Color::Black),
                sf::Vertex(sf::Vector2f(windowCenterX + childX + 30, windowCenterY + childY + 30), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines);

            drawTree(window, node->children[i], childX, childY, childXOffset, font);
        }
    }

};


template <typename T, size_t K>
std::ostream& operator<<(std::ostream& os, Tree<T, K>& tree) {
    for (auto it = tree.begin_bfs(); it != tree.end_bfs(); ++it) {
        Node<T>* node = *it;
        os << node->get_value() << " ";
    }
    return os;
}


#endif
