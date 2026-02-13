#include "misplaced.hpp"

// calculate the misplaced tile by iterating through both array, comparing side by side the differences
int calculate_misplaced(Node &curr, Node &goal) {
    int misplaced = 0;
    for (int i = 0; i < 9; i++) {
            if (goal.state[i] != curr.state[i] && curr.state[i] != 0) {
                misplaced++;
            }
        }
    return misplaced;
}

// for all operation check if the move is legal, swap, calculate the misplaced, and pushes onto queue
void misplaced_top(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int top = tile_zero_index - 3;
    Node child_node;
    int heuristic = 0;
    if (top >= 0) {
        child_node = parent;
        swap(child_node.state[top], child_node.state[tile_zero_index]);
        heuristic = calculate_misplaced(child_node, goal);
        push_queue(child_node, parent, nodes_queue, heuristic);
    }   
}
void misplaced_bottom(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int bottom = tile_zero_index + 3;
    Node child_node;
    int heuristic = 0;
    if (bottom <= 8) {
        child_node = parent;
        swap(child_node.state[bottom], child_node.state[tile_zero_index]);
        heuristic = calculate_misplaced(child_node, goal);
        push_queue(child_node, parent, nodes_queue, heuristic);
    }    
}
void misplaced_left(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int left = (tile_zero_index % 3) - 1;
    Node child_node;
    int heuristic = 0;
    if (left >= 0) {
        child_node = parent;
        swap(child_node.state[tile_zero_index - 1], child_node.state[tile_zero_index]);
        heuristic = calculate_misplaced(child_node, goal);
        push_queue(child_node, parent, nodes_queue, heuristic);
    }    
}
void misplaced_right(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int right = (tile_zero_index % 3) + 1;
    Node child_node;
    int heuristic = 0;
    if (right < 3) {
        child_node = parent;
        swap(child_node.state[tile_zero_index + 1], child_node.state[tile_zero_index]);
        heuristic = calculate_misplaced(child_node, goal);
        push_queue(child_node, parent, nodes_queue, heuristic);
    }
}
void mis_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, Node &goal) {
    int tile_zero_index = find_zero_tile_index(node);

    misplaced_top(node, tile_zero_index, goal, nodes_queue);
    misplaced_bottom(node, tile_zero_index, goal, nodes_queue);
    misplaced_left(node, tile_zero_index, goal, nodes_queue);
    misplaced_right(node, tile_zero_index, goal, nodes_queue);

}

/*
the general algorithm that will be used by all three searches
the priority queue is focused on the evalution function so uniform search ignores it completely
priority queue focuses on the smallest evalution function
to check a node, pop it off the queue
only expand nodes when the current node isn't a dupelicate so it prevent recalculating the same nodes (is visited)
node_expanded is calculate everytime a node is going to be expanded (is not a dupelicate)
the queue size is calculate by adding all the nodes that has be been visited and the current amount of item in the queue
if the goal is reached early, the entire search is complete and stopped
*/
void misplaced_tile_search (Node &problem, Node &goal) {
    int nodes_expanded = 0;
    priority_queue<Node, vector<Node>, CompareEvalution> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    nodes_queue.push(initial_node);

    // use a hashmap for visited for fast search up time
    map<vector<int>, bool> visited;


    while (!nodes_queue.empty()) {
        node = nodes_queue.top();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << "Depth: " << node.depth << endl;
            cout << "Nodes expanded: " << nodes_expanded << endl;
            cout << "Queue Size: " << visited.size() + nodes_queue.size() << endl;
            return;
        }
        else {
            if (visited[node.state]) continue;
            visited[node.state] = true;
            nodes_expanded++;
            mis_move_operation(node, nodes_queue, goal);
        }
    }
}