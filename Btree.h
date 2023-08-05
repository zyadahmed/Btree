#ifndef BINARYTREE_BTREE_H
#define BINARYTREE_BTREE_H
using namespace std;
#include <iostream>

template <class T, int order>
struct bTreeNode {
    int elements;
    T items[2 * order - 1];
    bTreeNode* children[2 * order];

    bTreeNode() : elements(0) {
        for (int i = 0; i < 2 * order - 1; ++i) {
            items[i] = T();
        }
        for (int i = 0; i < 2 * order; ++i) {
            children[i] = nullptr;
        }
    }
};

template <class T, int order>
class Btree {
public:
    Btree() {
        root = new bTreeNode<T, order>;
        root->elements = 0;
    }

    bool search(bTreeNode<T, order>* node, const T& key) {
        if (node == nullptr) {
            return false;
        }

        for (int i = 0; i < node->elements; ++i) {
            if (node->items[i] == key) {
                return true;
            } else if (node->items[i] > key) {
                return search(node->children[i], key);
            }
        }

        return search(node->children[node->elements], key);
    }

    void insert(const T& item) {
        insertInTree(root, item);
    }

    void inOrderTraversal() {
        inOrder(root);
    }
    void printRoot(){
        cout<<"\n";
        for(int i =0 ;i<root->elements;i++){
            cout<<root->items[i]<<"\t";
        }
        cout<<endl;
    }
    void printLeftAndRightHeight() {
        int leftHeight = getHeight(root->children[0]);
        int rightHeight = getHeight(root->children[1]);

        cout << "Left Height: " << leftHeight << endl;
        cout << "Right Height: " << rightHeight << endl;
    }

private:
    bTreeNode<T, order>* root;

    void split(bTreeNode<T, order>* parent, int childIndex) {
        bTreeNode<T, order>* child = parent->children[childIndex];
        bTreeNode<T, order>* newChild = new bTreeNode<T, order>;
        int median = child->elements / 2;
        newChild->elements = median;

        for (int i = 0; i < median; ++i) {
            newChild->items[i] = child->items[i + median];
        }

        if (child->children[0]) {
            for (int i = 0; i <= median; ++i) {
                newChild->children[i] = child->children[i + median];
            }
        }

        child->elements = median;

        parent->children[childIndex + 1] = newChild;
        for (int i = parent->elements; i > childIndex; --i) {
            parent->children[i + 1] = parent->children[i];
        }
        parent->children[childIndex + 1] = newChild;
        parent->items[childIndex] = child->items[median - 1];
        parent->elements++;
    }

    void insertNotFull(bTreeNode<T, order>* node, const T& item) {
        int location = node->elements - 1;
        while (location >= 0 && item < node->items[location]) {
            node->items[location + 1] = node->items[location];
            location--;
        }
        node->items[location + 1] = item;
        node->elements++;
    }

    bool isLeaf(bTreeNode<T, order>* node) {
        return node->children[0] == nullptr;
    }


    bTreeNode<T, order>* getParent(bTreeNode<T, order>* current, bTreeNode<T, order>* child) {
        if (current == nullptr || current->children[0] == nullptr) {
            return nullptr;
        }
        for (int i = 0; i <= current->elements; ++i) {
            if (current->children[i] == child) {
                return current;
            }
            if (i == current->elements || current->children[i]->items[0] > child->items[0]) {
                return getParent(current->children[i], child);
            }
        }
        return nullptr;
    }
    void insertInTree(bTreeNode<T, order>* node, const T& item) {
        if (isLeaf(node)) {
            if (node->elements < 2 * order - 1) {
                insertNotFull(node, item);
            } else {
                // If leaf is full, split the node
                bTreeNode<T, order>* parent = getParent(root, node);
                if (parent == nullptr) {
                    // Create a new root and split the current root
                    bTreeNode<T, order>* newRoot = new bTreeNode<T, order>;
                    newRoot->children[0] = root;
                    split(newRoot, 0);
                    root = newRoot;
                } else {
                    int childIndex = getChildIndex(parent, node);
                    split(parent, childIndex);
                }
                insertInTree(root, item);
            }
        } else {
            int index = node->elements - 1;
            while (index >= 0 && item < node->items[index]) {
                index--;
            }
            index++;
            if (node->children[index] != nullptr && node->children[index]->elements == 2 * order - 1) {
                split(node, index);
                if (item > node->items[index]) {
                    index++;
                }
            }
            if (node->children[index] != nullptr) {
                insertInTree(node->children[index], item);
            }
        }
    }
    int getChildIndex(bTreeNode<T, order>* parent, bTreeNode<T, order>* child) {
        for (int i = 0; i <= parent->elements; ++i) {
            if (parent->children[i] == child) {
                return i;
            }
        }
        return -1;
    }
    int getHeight(bTreeNode<T, order>* node) {
        if (node == nullptr)
            return 0;

        int leftHeight = getHeight(node->children[0]);
        int rightHeight = getHeight(node->children[1]);

        return 1 + max(leftHeight, rightHeight);
    }

    void inOrder(bTreeNode<T, order>* node) {
        if (node == nullptr)
            return;

        int total = node->elements;

        for (int i = 0; i < total; ++i)
            inOrder(node->children[i]);

        for (int i = 0; i < total; ++i)
            cout << node->items[i] << " ";

        inOrder(node->children[total]);
    }
};

#endif // BINARYTREE_BTREE_H
