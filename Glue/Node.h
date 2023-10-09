//
// Created by Rolf Svenning on 17/04/2023.
//

#ifndef IMPLEMENTATIONS_NODE_H
#define IMPLEMENTATIONS_NODE_H


class Node {
public:
    Node(int value = -1, int index = -1, Node* parent = nullptr, Node* = nullptr, Node* = nullptr);
    int v;
    long ind;
    Node* p;
    Node* l;
    Node* r;
};


#endif //IMPLEMENTATIONS_NODE_H
