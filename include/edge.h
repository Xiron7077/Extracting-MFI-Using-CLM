#ifndef EDGE
#define EDGE

#include "node.h"
#include <vector>

class Node;

class Edge {
public:
    Node* to = nullptr;
    std::vector<Node*> neighbours;
    Node* next = nullptr;
    int weight{};
};

#endif // EDGE