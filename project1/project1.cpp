#include <iostream>
#include <vector>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "utility.hpp"
#include "manhattan.hpp"

/*
find the "zero tile" index on board
"zero tile" is basically the empty tile on in real game
*/


/*
This is checking whether the move or not is valid
if the "zero tile" is in bottom left corner for example
we can only swap up and down
*/
// void move_up(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
//     int top = tile_zero_index - 3;
//     Node child_node = parent;
//     if (top >= 0) {
//         child_node.g = parent.g + 1;
//         child_node.depth = parent.depth + 1;
//         child_node.h = heuristic;
//         child_node.f = child_node.h + child_node.g;
//         swap(child_node.state[top], child_node.state[tile_zero_index]);
//         nodes_queue.push(child_node);
//     }    
// }
// void move_down(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
//     int bottom = tile_zero_index + 3;
//     Node child_node = parent;
//     if (bottom <= 8) {
//         child_node.g = parent.g + 1;
//         child_node.depth = parent.depth + 1;
//         child_node.h = heuristic;
//         child_node.f = child_node.h + child_node.g;
//         swap(child_node.state[bottom], child_node.state[tile_zero_index]);
//         nodes_queue.push(child_node);
//     }    
// }
// void move_left(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
//     int left = (tile_zero_index % 3) - 1;
//     Node child_node = parent;
//     if (left >= 0) {
//         child_node.g = parent.g + 1;
//         child_node.depth = parent.depth + 1;
//         child_node.h = heuristic;
//         child_node.f = child_node.h + child_node.g;
//         swap(child_node.state[tile_zero_index - 1], child_node.state[tile_zero_index]);
//         nodes_queue.push(child_node);
//     }    
// }
// void move_right(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
//     int right = (tile_zero_index % 3) + 1;
//     Node child_node = parent;
//     if (right < 3) {
//         child_node.g = parent.g + 1;
//         child_node.depth = parent.depth + 1;
//         child_node.h = heuristic;
//         child_node.f = child_node.h + child_node.g;
//         swap(child_node.state[tile_zero_index + 1], child_node.state[tile_zero_index]);
//         nodes_queue.push(child_node);
//     }
// }

void uni_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int tile_zero_index = find_zero_tile_index(node);

    // move_up(tile_zero_index, node, nodes_queue, 0);
    // move_down(tile_zero_index, node, nodes_queue, 0);
    // move_left(tile_zero_index, node, nodes_queue, 0);
    // move_right(tile_zero_index, node, nodes_queue, 0);
}

void uniform_search(Node &problem, Node &goal) {
    priority_queue<Node, vector<Node>, CompareEvalution> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    int search_space = 0;
    // push the initial into queue
    nodes_queue.push(initial_node);
    map<vector<int>, bool> visited;


    while (!nodes_queue.empty()) {

        /*
        pop the first item in the queue and perform the operations base on cost
        operations being swap the "zero tile" tile up, down, left, right        
        */
        node = nodes_queue.top();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << "Depth: " << node.depth << endl;
            cout << "Search space: " << search_space << endl;
            return;
        }
        else {
            /*
            check if the state is repetitve
            if repetitve: skip
            if not: branch
            */
            if (visited[node.state]) continue;
            visited[node.state] = true;
            search_space++;
            uni_move_operation(node, nodes_queue);
        }

    }
}



int calc_misplaced_top(Node &parent, int tile_zero_index, Node &goal) {
    int top = tile_zero_index - 3;
    Node temp_node;
    int cost = 0;
    if (top >= 0) {
        temp_node = parent;
        swap(temp_node.state[top], temp_node.state[tile_zero_index]);
        for (int i = 0; i < 9; i++) {
            if (goal.state[i] != temp_node.state[i] && temp_node.state[i] != 0) {
                cost++;
            }
        }
    }   
    return cost; 
}
int calc_misplaced_bottom(Node &parent, int tile_zero_index, Node &goal) {
    int bottom = tile_zero_index + 3;
    Node temp_node;
    int cost = 0;
    if (bottom <= 8) {
        temp_node = parent;
        swap(temp_node.state[bottom], temp_node.state[tile_zero_index]);
        for (int i = 0; i < 9; i++) {
            if (goal.state[i] != temp_node.state[i] && temp_node.state[i] != 0) {
                cost++;
            }
        }
    }    
    return cost; 
}
int calc_misplaced_left(Node &parent, int tile_zero_index, Node &goal) {
    int left = (tile_zero_index % 3) - 1;
    Node temp_node;
    int cost = 0;
    if (left >= 0) {
        temp_node = parent;
        swap(temp_node.state[tile_zero_index - 1], temp_node.state[tile_zero_index]);
        for (int i = 0; i < 9; i++) {
            if (goal.state[i] != temp_node.state[i] && temp_node.state[i] != 0) {
                cost++;
            }
        }
    }    
    return cost;
}
int calc_misplaced_right(Node &parent, int tile_zero_index, Node &goal) {
    int right = (tile_zero_index % 3) + 1;
    Node temp_node;
    int cost = 0;
    if (right < 3) {
        temp_node = parent;
        swap(temp_node.state[tile_zero_index + 1], temp_node.state[tile_zero_index]);
        for (int i = 0; i < 9; i++) {
            if (goal.state[i] != temp_node.state[i] && temp_node.state[i] != 0) {
                cost++;
            }
        }
    }
    return cost;
}
void mis_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, Node &goal) {
    int tile_zero_index = find_zero_tile_index(node);

    int h_top = (calc_misplaced_top(node, tile_zero_index, goal));
    int h_bot = (calc_misplaced_bottom(node, tile_zero_index, goal));
    int h_left = (calc_misplaced_left(node, tile_zero_index, goal));
    int h_right = (calc_misplaced_right(node, tile_zero_index, goal));

    // move_up(tile_zero_index, node, nodes_queue, h_top);
    // move_down(tile_zero_index, node, nodes_queue, h_bot);
    // move_left(tile_zero_index, node, nodes_queue, h_left);
    // move_right(tile_zero_index, node, nodes_queue, h_right);
}

void misplaced_tile_search (Node &problem, Node &goal) {
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
            mis_move_operation(node, nodes_queue, goal);
        }
    }
}





int main() {

    Node goal;
    goal.state = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    Node problem1;
    problem1.state = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    Node problem2;
    problem2.state = {1, 2, 3, 4, 5, 6, 0, 7, 8};

    Node problem3;
    problem3.state = {1, 2, 3, 5, 0, 6, 4, 7, 8};

    Node problem4;
    problem4.state = {1, 3, 6, 5, 0, 2, 4, 7, 8};

    Node problem5;
    problem5.state = {1, 3, 6, 5, 0, 7, 4, 8, 2};

    Node problem6;
    problem6.state = {1, 6, 7, 5, 0, 3, 4, 8, 2};

    Node problem7;
    problem7.state = {7, 1, 2, 4, 8, 5, 6, 3, 0};

    Node problem8;
    problem8.state = {0, 7, 2, 4, 6, 1, 3, 5, 8};

    vector<Node> problems;
    problems.push_back(problem1);
    problems.push_back(problem2);
    problems.push_back(problem3);
    problems.push_back(problem4);
    problems.push_back(problem5);
    problems.push_back(problem6);
    problems.push_back(problem7);
    problems.push_back(problem8);

    // cout << "Uniform Search" << endl;
    // for (int i = 0; i < problems.size(); i++) {
    //     cout << "Problem: " << i + 1 << endl;
    //     auto start = high_resolution_clock::now();
    //     uniform_search(problems[i], goal);
    //     auto stop = high_resolution_clock::now();
    //     auto duration = duration_cast<microseconds>(stop - start);
    //     cout << "Time : " << duration.count() << endl;
    //     cout << endl;
    // }

    //     cout << "Misplaced Search" << endl;
    // for (int i = 0; i < problems.size(); i++) {
    //     cout << "Problem: " << i + 1 << endl;
    //     auto start = high_resolution_clock::now();
    //     misplaced_tile_search(problems[i], goal);
    //     auto stop = high_resolution_clock::now();
    //     auto duration = duration_cast<microseconds>(stop - start);
    //     cout << "Time : " << duration.count() << endl;
    //     cout << endl;
    // }   

    cout << "Manhattan Search" << endl;
    for (int i = 0; i < problems.size(); i++) {
        cout << "Problem: " << i + 1 << endl;
        auto start = high_resolution_clock::now();
        manhattan_search(problems[i], goal);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time : " << duration.count() << endl;
        cout << endl;
    }

    return 0;
}


