#ifndef NODE
#define NODE

#include <vector>
#include <queue>

using namespace std;


struct Node {
    vector<int> state;
    int depth = 0;
    int g = 0;
    int f = 0;
    int h = 0;
};

struct CompareEvalution {
    bool operator()(Node const& n1, Node const& n2)
    {
        return n1.f > n2.f;
    }
};

int find_zero_tile_index(Node &node);
void push_queue(Node &child_node, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);


#endif
