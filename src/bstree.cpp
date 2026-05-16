#include <iostream> 
#include "bstree.h"

BSTree::BSTree() : BST("BSTree") {}

bool BSTree::is_empty() const
{
  if (root == nullptr) return 1;
  return 0;
}

Node * BSTree::insert_node(Node * t, string key) {
  if (t == nullptr) return new Node(key);
  if (t -> key < key) t -> right = insert_node(t -> right, key);
  if (t -> key > key) t -> left = insert_node(t -> left, key);
  return t;
}

void BSTree::insert(const string & key)
{
  root = insert_node(root, key);
  count++;
}

Node * BSTree::find_node(Node * t, string key)
{
  if (t == nullptr) return nullptr;
  if (t -> key == key) return t;
  if (t -> key < key) return find_node(t -> right, key);
  if (t -> key > key) return find_node(t -> left, key);
  return nullptr;
}

bool BSTree::find(const string & key) const
{
  if (find_node(root, key) == nullptr) return false;
  return true;
}

Node * BSTree::left_most(Node * t)
{
  if (t -> left == nullptr) return t;
  if (t -> left != nullptr) return left_most(t -> left);
}


Node * BSTree::delete_node(Node * t, string key)
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
      temp = left_most(t -> right);
      t -> key = temp -> key;
      t -> right = delete_node(t -> right, temp -> key);
      return t;
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
  if (t -> key > key) t -> left = delete_node(t->left, key);

  return t;
}

void BSTree::remove(const string & key)
{
    if (find(key))
    {
        root = delete_node(root, key);
        count--;
    }
}
int BSTree::compute_height(Node * t)
{
  if ( t == nullptr) return 0;
  int left_height = compute_height(t->left);
  int right_height = compute_height(t->right);
  return max(left_height, right_height) + 1;
}

int BSTree::get_height() const
{
  return compute_height(root);
}