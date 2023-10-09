//
// Created by Rolf Svenning on 17/04/2023.
//

#include "Node.h"

Node::Node(int value, int index, Node* parent, Node* leftChild, Node* rightChild) {
    v = value;
    ind = index;
    p = parent;
    l = leftChild;
    r = rightChild;
}
