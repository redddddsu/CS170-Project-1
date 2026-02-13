#ifndef MIS
#define MIS

#include<iostream>
#include<map>

#include "utility.hpp"



int calculate_misplaced(Node &curr, Node &goal);
void misplaced_top(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void misplaced_bottom(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void misplaced_left(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void misplaced_right(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void mis_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, Node &goal);
void misplaced_tile_search (Node &problem, Node &goal);

#endif