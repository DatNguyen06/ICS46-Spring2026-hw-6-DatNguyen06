#include <iostream>
#include "bst.h"
#include "bstree.h"
#include "avltree.h"
#include <fstream>
#include "timer.h"

void delete_tree(Node * t)
{
    if (t == nullptr) return;
    delete_tree(t -> left);
    delete_tree(t->right);
    delete t;
}

BST::~BST()
{
    delete_tree(root);
}

void BST::in_order_print(ostream & out, Node * t)
{
    if (t == nullptr) return;
    in_order_print(out, t -> left);
    out << t -> key << ' ';
    in_order_print(out, t -> right);
}

void BST::pre_order_print(ostream & out, Node * t)
{
    if (t == nullptr) return;
    out << t -> key << ' ';
    pre_order_print(out, t -> left);
    pre_order_print(out, t -> right);
}

void BST::post_order_print(ostream & out, Node * t)
{
    if (t == nullptr) return;
    post_order_print(out, t -> left);
    post_order_print(out, t -> right);
    out << t -> key << ' ';
}

ostream & operator << (ostream & out, BST & L)
{
    L.print(out);
    return out;
}

void error(string word, string msg)
{
    cerr << word << " : " << msg << '\n';
}

void insert_all_words(int k, string file_name, BST & L)
{
    ifstream in(file_name);
    if (in.fail())
        error(file_name, "could not open file");

    string word;
    int words_to_insert = k * NWORDS / 10;

    Timer t;
    double elapsed;
    t.start();

    for (int i = 0; i < words_to_insert; i++)
    {
        in >> word;
        L.insert(word);
    }

    t.elapsedUserTime(elapsed);
    cout << elapsed << ' ';
}

void find_all_words(int k, string file_name, BST & L)
{
    ifstream in(file_name);
    if (in.fail())
        error(file_name, "could not open file");

    string word;
    int words_to_find = k * NWORDS / 10;

    Timer t;
    double elapsed;
    t.start();

    for (int i = 0; i < words_to_find; i++)
    {
        in >> word;
        L.find(word);
    }

    t.elapsedUserTime(elapsed);
    cout << elapsed << ' ';
}

void remove_all_words(int k, string file_name, BST & L)
{
    ifstream in(file_name);
    if (in.fail())
        error(file_name, "could not open file");

    string word;
    int words_to_remove = k * NWORDS / 10;

    Timer t;
    double elapsed;
    t.start();

    for (int i = 0; i < words_to_remove; i++)
    {
        in >> word;
        L.remove(word);
    }

    t.elapsedUserTime(elapsed);
    cout << elapsed << ' ';
}

void measure_BST(string file_name, BST & L)
{
    insert_all_words(10, file_name, L);
    find_all_words(10, file_name, L);
    remove_all_words(10, file_name, L);
    if (!L.is_empty()) error(L.name, "is not empty");
}

void measure_BSTs(string input_file)
{
    for (int i = 1; i <= 10; ++i)
    {
        BSTree bst;
        AVLTree avl;
        cout << "\ti = " << i << ' ';
        insert_all_words(i, input_file, bst);
        find_all_words(i, input_file, bst);
        remove_all_words(i, input_file, bst);
        insert_all_words(i, input_file, avl);
        find_all_words(i, input_file, avl);
        remove_all_words(i, input_file, avl);
    }
}