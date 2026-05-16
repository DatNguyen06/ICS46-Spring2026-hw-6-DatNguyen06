#ifndef BST_H
#define BST_H
#include <stack>
#include <iostream>
using namespace std;

constexpr int NWORDS = 45392;

struct Node
{
    string key;
    int value;
    Node * left, * right;
    int height;
    Node(const string & new_key, Node * new_left=nullptr, Node * new_right=nullptr)
        : key(new_key),
          value(0),
          left(new_left), right(new_right),
          height(1)
    { }

    int size() const {
        int left_size = (left != nullptr) ? left->size() : 0;
        int right_size = (right != nullptr) ? right->size() : 0;
        return left_size + right_size + 1;
    }
};

struct BST
{
    Node * root;
    const string name;
    int count;

    struct iterator {
        stack<Node*> stk;
        BST* tree;

        iterator() : tree(nullptr) {}
        
        iterator(Node* root, BST* t) : tree(t) {
            Node* current = root;
            while (current != nullptr) {
                stk.push(current);
                current = current->left;
            }
        }
        
        string operator*() { return stk.top()->key; }
        
        Node* operator->() { return stk.top(); }
        
        iterator& operator++() {
            Node* current = stk.top();
            stk.pop();
            current = current->right;
            while (current != nullptr) {
                stk.push(current);
                current = current->left;
            }
            return *this;
        }
        
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
        
        bool operator==(const iterator& other) { return stk.empty() == other.stk.empty(); }
        bool operator!=(const iterator& other) { return stk.empty() != other.stk.empty(); }
    };

    iterator begin() { return iterator(root, this); }
    iterator end()   { return iterator(nullptr, this); }

    BST(const string & new_name)
        : root(nullptr), name(new_name), count(0) { }

    virtual void insert( const string & word) = 0;
    virtual bool find( const string & word ) const = 0;
    virtual void remove( const string & word ) = 0;

    virtual bool is_empty() const = 0;
    virtual int size() const { return count; }
    virtual int get_height() const = 0;

    void pre_order_print(ostream & out, Node * t);
    void in_order_print(ostream & out, Node * t);
    void post_order_print(ostream & out, Node * t);

    void print(ostream & out) {
        for (auto e : *this)
            out << e << ' ';
    }

    virtual ~BST();
    BST(const BST & L) = delete;
    BST& operator =(const BST & L) = delete;
};

ostream & operator << (ostream & out, BST & L);

void error(string word, string msg);
void insert_all_words(int k, string file_name, BST & L);
void find_all_words(int k, string file_name, BST & L);
void remove_all_words(int k, string file_name, BST & L);
void measure_BST(string file_name, BST & L);
void measure_BSTs(string input_file);

#endif