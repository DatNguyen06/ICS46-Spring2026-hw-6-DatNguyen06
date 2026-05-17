#include "bst.h"
#include "bstree.h"
#include "avltree.h"
#include <fstream>
int main()
{
    AVLTree avl;
    avl.insert("aa");
    avl.insert("bb");
    avl.insert("cc");
    cout << "height: " << avl.get_height() << endl; // should be 2
    avl.remove("bb");
    cout << "height: " << avl.get_height() << endl; // should be 1
    avl.remove("aa");
    cout << "height: " << avl.get_height() << endl; // should be 1
    avl.remove("cc");
    cout << "height: " << avl.get_height() << endl; // should be 0
    // // measure_BSTs("src/shortrandom.txt");
    // measure_BSTs("src/random.txt");
    // // // measure_BSTs("src/shortsorted.txt");
    // measure_BSTs("src/sorted.txt");
}
