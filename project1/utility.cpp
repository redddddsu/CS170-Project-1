#include "utility.hpp"

// iterate through the current node to find the empty tile
int find_zero_tile_index(Node &node) {
    int index = 0;
    for (int i = 0; i < node.state.size(); i++) {
        if (node.state[i] == 0) {
            index = i; 
            break;
        }
    }
    return index;
}

/* 
pushes node onto the queue
performs the calculation for node depth, operation cost, and evalution function
*/
void push_queue(Node &child_node, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    child_node.g = parent.g + 1;
    child_node.depth = parent.depth + 1;
    child_node.h = heuristic;
    child_node.f = child_node.h + child_node.g;
    nodes_queue.push(child_node);
}