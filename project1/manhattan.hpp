#ifndef MAN
#define MAN

#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <map>
#include <iostream>

using namespace std;

#include "utility.hpp"

int manhattan_distance(Node &currentNode, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void manhattan_top(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void manhattan_bottom(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue); 
void manhattan_right(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void manhattan_left(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void man_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, Node &goal);
void manhattan_search(Node &problem, Node &goal);


void push_queue(Node &child_node, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);
// void move_down(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);
// void move_left(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);
// void move_right(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);



#endif
