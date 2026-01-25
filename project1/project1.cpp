#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    vector<int> state;
    int total_cost = 0;
};

void move_operation(Node &node, queue<Node> &node_queue, vector<Node> visited) {
    int tile_zero_index = 0;
    

    /*
    find the "zero tile" index on board
    "zero tile" is basically the empty tile on in real game
    */
    for (int i = 0; i < node.state.size(); i++) {
        if (node.state[i] == 0) {
            tile_zero_index = i; 
            break;
        }
    }

    /*
    This is checking whether the move or not is valid
    if the "zero tile" is in bottom left corner for example
    we can only swap up and down
    */
    int top = tile_zero_index - 3;
    int bottom = tile_zero_index + 3;
    int left = (tile_zero_index % 3) - 1;
    int right = (tile_zero_index % 3) + 1;

    //we use the visited vector to help us identify if a state is a repeat
    Node child_node;
    if (top >= 0) {
        child_node = node;
        child_node.total_cost += 1;
        swap(child_node.state[top], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
        visited.push_back(child_node);
    }    
    if (bottom <= 8) {
        child_node = node;
        child_node.total_cost += 1;
        swap(child_node.state[bottom], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
        visited.push_back(child_node);
    }    
    if (left >= 0) {
        child_node = node;
        child_node.total_cost += 1;
        swap(child_node.state[tile_zero_index - 1], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
        visited.push_back(child_node);
    }    
    if (right < 3) {
        child_node = node;
        child_node.total_cost += 1;
        swap(child_node.state[tile_zero_index + 1], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
        visited.push_back(child_node);
    }
}

void uniform_search(Node &problem, Node &goal) {
    queue<Node> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    // push the initial into queue
    nodes_queue.push(initial_node);
    vector<Node> visited;


    while (!nodes_queue.empty()) {

        /*
        pop the first item in the queue and perform the operations base on cost
        operations being swap the "zero tile" tile up, down, left, right        
        */
        node = nodes_queue.front();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << node.total_cost << endl;
            return;
        }
        else {
            /*
            check if the state is repetitve
            if repetitve: skip
            if not: branch
            */
            for (int i = 0; i < visited.size(); i++) {
                if (visited[i].state == node.state) {
                    continue;
                }
            }
            move_operation(node, nodes_queue, visited);
        }

    }
}
int main() {

    Node goal;
    goal.state = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    Node test;
    test.state = {1, 3, 6, 5, 0, 2, 4, 7, 8};
    uniform_search(test, goal);


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