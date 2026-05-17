#include <iostream>
#include "avltree.h"

AVLTree::AVLTree() : BST("AVLTree"){}

int AVLTree::get_height(Node * node)
{
    if (node == nullptr) return 0;
    return node -> height;
}
int AVLTree::get_balance(Node * node)
{
    if (node == nullptr) return 0;
    return (get_height(node->left) - get_height(node->right));
}
void AVLTree::set_height(Node * node)
{
    node -> height = max(get_height(node->left), get_height(node->right)) + 1;
}
Node * AVLTree::right_rotate(Node * y)
{
    Node * x = y -> left;
    y -> left = x -> right;
    x -> right = y;
    set_height(y);
    set_height(x);
    return x;
}
Node * AVLTree::left_rotate(Node * x)
{
    Node * y = x -> right;
    x -> right = y -> left;
    y -> left = x;
    set_height(x);
    set_height(y);
    return y;
}

Node * AVLTree::rebalance(Node * t)
{
    if (get_balance(t) > 1 && get_balance(t -> left) >= 0)
    {
        return right_rotate(t);
    }
    if (get_balance(t) > 1 && get_balance(t -> left) < 0)
    {
        t->left = left_rotate(t->left);
        return right_rotate(t);
    }
    if (get_balance(t) < -1 && get_balance(t -> right) <= 0)
    {
        return left_rotate(t);
    }
    if (get_balance(t) <-1 && get_balance(t -> right) > 0)
    {
        t -> right = right_rotate(t->right);
        return left_rotate(t);
    }
    return t;
}
Node * AVLTree::insert_node(Node * t, string key)
{
    if (t == nullptr) return new Node(key);
    if (t -> key < key) t -> right = insert_node(t -> right, key);
    else if (t -> key > key) t -> left = insert_node(t -> left, key);
    set_height(t);
    return rebalance(t);
}

void AVLTree::insert(const string & key)
{
    root = insert_node(root, key);
    count++;
}
Node * AVLTree::find_node(Node * t, string key)
{
    if (t == nullptr) return nullptr;
    if (t -> key == key) return t;
    if (t -> key < key) return find_node(t -> right, key);
    if (t -> key > key) return find_node(t -> left, key);
    return nullptr;
}

bool AVLTree::find(const string & key) const
{
    if (AVLTree::find_node(root, key) == nullptr) return false;
    return true;
}

Node * AVLTree::delete_node(Node * t, string key)
{
    Node * temp = nullptr;
    if (t == nullptr) return nullptr;

    if (t -> key == key)
  {
    if (t -> right == nullptr && t -> left == nullptr)
    {
      delete t;
      return nullptr;
    }
    else if (t-> right != nullptr && t -> left != nullptr)
    {
        Node * temp = t->right;
        while (temp->left != nullptr) temp = temp->left;
        t -> key = temp -> key;
        t -> right = delete_node(t -> right, temp -> key);
        set_height(t);
        return rebalance(t);
    }

    else if (t -> right != nullptr) 
    {
      temp = t -> right;
      delete t;
      return temp;
    }
    else if (t -> left != nullptr)
    {
      temp = t -> left;
      delete t;
      return temp;
    }
  }

    if (t -> key < key) t -> right = delete_node(t->right, key);
    else if (t -> key > key) t -> left = delete_node(t->left, key);

    set_height(t);
    return rebalance(t);
}

void AVLTree::remove(const string & key)
{
    if (find_node(root, key) != nullptr) {
        root = delete_node(root, key);
        count--;
    }
}

bool AVLTree::is_empty() const
{
    if (root == nullptr) return 1;
    return 0;
}
int AVLTree::get_height() const
{
    return get_height(root);
}