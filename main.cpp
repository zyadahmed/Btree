#include <iostream>
#include "Btree.h"
using namespace std;
int main() {
    Btree<int, 2> btree;

    btree.insert(8);
    btree.insert(3);
    btree.insert(10);
    btree.insert(1);
    btree.insert(6);
    btree.insert(14);
    btree.insert(4);
    btree.insert(7);
    btree.insert(13);

    cout << "InOrder Traversal: ";
    btree.inOrderTraversal();
    cout << "Root Elements: ";
    btree.printRoot();
    return 0;
}
