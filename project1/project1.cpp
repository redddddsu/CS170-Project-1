#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> state;
    int total_cost = 0;
    Node *parent;
};

void move_operation(Node &parent_node, queue<Node> &node_queue) {
    int tile_zero_index = 0;
    

    //find the "zero tile" index on board
    for (int i = 0; i < parent_node.state.size(); i++) {
        if (parent_node.state[i] == 0) {
            tile_zero_index = i; 
            break;
        }
    }
    /*
    check which operations are valid
    if the tile is position in the bottom left, going down or left wouldn't be valid
    since I am doing on an array we can do this
    
    0 1 2
    3 4 5 
    6 7 8
    
    above this index of array and lets say 4 is the "zero tile"
    check:
    top: 4 - (3)
    bottom: 4 + (3)
    right: (4 % 3) + 1
    left: (4 % 3) - 1
    */
    int top = tile_zero_index - 3;
    int bottom = tile_zero_index + 3;
    int left = (tile_zero_index % 3) - 1;
    int right = (tile_zero_index % 3) + 1;

    Node child_node;
    if (top >= 0) {
        child_node = parent_node;
        child_node.total_cost += 1;
        swap(child_node.state[top], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }    
    if (bottom <= 8) {
        child_node = parent_node;
        child_node.total_cost += 1;
        swap(child_node.state[bottom], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }    
    if (left >= 0) {
        child_node = parent_node;
        child_node.total_cost += 1;
        swap(child_node.state[left], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }    
    if (right <= 8) {
        child_node = parent_node;
        child_node.total_cost += 1;
        swap(child_node.state[right], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }
}

void uniform_search(Node &problem) {
    queue<Node> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;

    // push the initial into queue
    nodes_queue.push(initial_node);

    while (true) {

        /*
        pop the first item in the queue and perform the operations base on cost
        operations being swap the 0 tile up, down, left, right        
        */
        // node = nodes.front();
        // nodes.pop();

        // move_operation(node, total_cost);

    }
}
int main() {

    return 0;
}


/*
{
1, 2, 3
4, 5, 6
7, 8, 0
}

{
1, 2, 3
4, 5, 6
0, 7, 8
}
*/