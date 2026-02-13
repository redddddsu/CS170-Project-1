#ifndef UN
#define UN

#include<iostream>
#include<map>

#include "utility.hpp"

void uniform_up(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);
void uniform_down(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);
void uniform_right(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);
void uniform_left(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic);

void uni_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue);
void uniform_search(Node &problem, Node &goal);
#endif