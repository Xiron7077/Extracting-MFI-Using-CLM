#ifndef NODE
#define NODE

#include <vector>
#include "edge.h"

class Edge;

class Node {
public:
    char data{};
    int weight{};
    std::vector<Edge*> edges;
};

#endif // NODE