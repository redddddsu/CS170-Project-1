#include "manhattan.hpp"

using namespace std;

void move(Node &child_node, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    child_node.g = parent.g + 1;
    child_node.depth = parent.depth + 1;
    child_node.h = heuristic;
    child_node.f = child_node.h + child_node.g;
    nodes_queue.push(child_node);
}
// void move_down(Node &child_node, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
//     int bottom = tile_zero_index + 3;
//     Node child_node = parent;
//     if (bottom <= 8) {
//         child_node.g = parent.g + 1;
//         child_node.depth = parent.depth + 1;
//         child_node.h = heuristic;
//         child_node.f = child_node.h + child_node.g;
//         nodes_queue.push(child_node);
//     }    
// }
// void move_left(Node &child_node, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
//     int left = (tile_zero_index % 3) - 1;
//     Node child_node = parent;
//     if (left >= 0) {
//         child_node.g = parent.g + 1;
//         child_node.depth = parent.depth + 1;
//         child_node.h = heuristic;
//         child_node.f = child_node.h + child_node.g;
//         nodes_queue.push(child_node);
//     }    
// }
// void move_right(Node &child_node, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
//     int right = (tile_zero_index % 3) + 1;
//     Node child_node = parent;
//     if (right < 3) {
//         child_node.g = parent.g + 1;
//         child_node.depth = parent.depth + 1;
//         child_node.h = heuristic;
//         child_node.f = child_node.h + child_node.g;
//         nodes_queue.push(child_node);
//     }
// }

int manhattan_distance(Node &currentNode, Node &goal) {
    int total_distance = 0;
    int distance;
    int goal_index;
    int current_number;
    int currX, currY, goalX, goalY;
    for (int i = 0; i < 9; i++) {
        if (currentNode.state[i] != goal.state[i] && currentNode.state[i] != 0) {
            current_number = currentNode.state[i];
            goal_index = current_number - 1;
            currX = i % 3;
            currY = i / 3;
            goalX = goal_index % 3;
            goalY = goal_index / 3;
            distance =  abs(currX - goalX) + abs(currY - goalY);
            total_distance += distance;
        }
    }
    return total_distance;

}
void manhattan_top(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int top = tile_zero_index - 3;
    Node child_node;
    int heuristic = 0;
    if (top >= 0) {
        child_node = parent;
        swap(child_node.state[top], child_node.state[tile_zero_index]);
        heuristic = manhattan_distance(child_node, goal);
        move(child_node, parent, nodes_queue, heuristic);

    }    
}
void manhattan_bottom(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int bottom = tile_zero_index + 3;
    Node child_node;
    int heuristic = 0;
    if (bottom <= 8) {
        child_node = parent;
        swap(child_node.state[bottom], child_node.state[tile_zero_index]);
        heuristic = manhattan_distance(child_node, goal);
        move(child_node, parent, nodes_queue, heuristic);
    }    
}
void manhattan_left(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int left = (tile_zero_index % 3) - 1;
    Node child_node;
    int heuristic = 0;
    if (left >= 0) {
        child_node = parent;
        swap(child_node.state[tile_zero_index - 1], child_node.state[tile_zero_index]);
        heuristic = manhattan_distance(child_node, goal);
        move(child_node, parent, nodes_queue, heuristic);
    }    
}
void manhattan_right(Node &parent, int tile_zero_index, Node &goal, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int right = (tile_zero_index % 3) + 1;
    Node child_node;
    int heuristic = 0;
    if (right < 3) {
        child_node = parent;
        swap(child_node.state[tile_zero_index + 1], child_node.state[tile_zero_index]);
        heuristic = manhattan_distance(child_node, goal);
        move(child_node, parent, nodes_queue, heuristic);
    }    
}

void man_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, Node &goal) {
    int tile_zero_index = find_zero_tile_index(node);

    manhattan_top(node, tile_zero_index, goal, nodes_queue);
    manhattan_bottom(node, tile_zero_index, goal, nodes_queue);
    manhattan_left(node, tile_zero_index, goal, nodes_queue);
    manhattan_right(node, tile_zero_index, goal, nodes_queue);


}

void manhattan_search(Node &problem, Node &goal) {
    int search_space = 0;
    priority_queue<Node, vector<Node>, CompareEvalution> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    // push the initial into queue
    nodes_queue.push(initial_node);
    map<vector<int>, bool> visited;

    while (!nodes_queue.empty()) {
        node = nodes_queue.top();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << "Depth: " << node.depth << endl;
            cout << "Search space: " << search_space << endl;
            return;
        }
        else {
            if (visited[node.state]) continue;
            visited[node.state] = true;
            search_space++;
            man_move_operation(node, nodes_queue, goal);
        }
    }
}
