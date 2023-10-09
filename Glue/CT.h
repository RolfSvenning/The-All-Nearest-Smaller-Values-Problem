//
// Created by Rolf Svenning on 19/04/2023.
//

#ifndef IMPLEMENTATIONS_CT_H
#define IMPLEMENTATIONS_CT_H

#include "Node.h"

class CT{
public:
    CT(Node* childPointer, int indexTo);
    Node* childPtr;
    int indTo;
};

#endif //IMPLEMENTATIONS_CT_H
