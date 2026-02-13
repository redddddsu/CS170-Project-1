#include "uniform.hpp"

/*
for each operation (up, down, left, right)
check where the tile is positioned and see if doing a swap will be out of boundary
if the swap is legal, push onto queue
*/
void uniform_up(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int top = tile_zero_index - 3;
    Node child_node = parent;
    if (top >= 0) {
        swap(child_node.state[top], child_node.state[tile_zero_index]);
        push_queue(child_node, parent, nodes_queue, 0);
    }    
}
void uniform_down(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int bottom = tile_zero_index + 3;
    Node child_node = parent;
    if (bottom <= 8) {
        swap(child_node.state[bottom], child_node.state[tile_zero_index]);
        push_queue(child_node, parent, nodes_queue, 0);
    }    
}
void uniform_left(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int left = (tile_zero_index % 3) - 1;
    Node child_node = parent;
    if (left >= 0) {
        swap(child_node.state[tile_zero_index  - 1], child_node.state[tile_zero_index]);
        push_queue(child_node, parent, nodes_queue, 0);
    }    
}
void uniform_right(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int right = (tile_zero_index % 3) + 1;
    Node child_node = parent;
    if (right < 3) {
        swap(child_node.state[tile_zero_index  + 1], child_node.state[tile_zero_index]);
        push_queue(child_node, parent, nodes_queue, 0);
    }    
}

// hardcode the heurstic to zero because we don't need it for uniform search
void uni_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int tile_zero_index = find_zero_tile_index(node);

    uniform_up(tile_zero_index, node, nodes_queue, 0);
    uniform_down(tile_zero_index, node, nodes_queue, 0);
    uniform_left(tile_zero_index, node, nodes_queue, 0);
    uniform_right(tile_zero_index, node, nodes_queue, 0);
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
void uniform_search(Node &problem, Node &goal) {
    priority_queue<Node, vector<Node>, CompareEvalution> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    int nodes_expanded = 0;
    nodes_queue.push(initial_node);

    // use a hashmap for visited for fast search up time
    map<vector<int>, bool> visited;

    while (!nodes_queue.empty()) {
        node = nodes_queue.top();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << "Depth: " << node.depth << endl;
            cout << "Nodes Expanded: " << nodes_expanded << endl;
            cout << "Queue Size: " << visited.size() + nodes_queue.size() << endl;

            return;
        }
        else {
            if (visited[node.state]) continue;
            visited[node.state] = true;
            nodes_expanded++;
            uni_move_operation(node, nodes_queue);
        }

    }
}

