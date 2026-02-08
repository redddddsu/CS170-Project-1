#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <map>

using namespace std;

struct Node {
    vector<int> state;
    int depth = 0;
    int total_cost = 0;
};

/*
find the "zero tile" index on board
"zero tile" is basically the empty tile on in real game
*/
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
This is checking whether the move or not is valid
if the "zero tile" is in bottom left corner for example
we can only swap up and down
*/
void move_up(int tile_zero_index, Node &parent, queue<Node> &node_queue, int cost) {
    int top = tile_zero_index - 3;
    Node child_node = parent;
    if (top >= 0) {
        child_node.depth++;
        child_node.total_cost += cost;
        swap(child_node.state[top], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }    
}
void move_down(int tile_zero_index, Node &parent, queue<Node> &node_queue, int cost) {
    int bottom = tile_zero_index + 3;
    Node child_node = parent;
    if (bottom <= 8) {
        child_node.depth++;
        child_node.total_cost += cost;
        swap(child_node.state[bottom], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }    
}
void move_left(int tile_zero_index, Node &parent, queue<Node> &node_queue, int cost) {
    int left = (tile_zero_index % 3) - 1;
    Node child_node = parent;
    if (left >= 0) {
        child_node.depth++;
        child_node.total_cost += cost;
        swap(child_node.state[tile_zero_index - 1], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }    
}
void move_right(int tile_zero_index, Node &parent, queue<Node> &node_queue, int cost) {
    int right = (tile_zero_index % 3) + 1;
    Node child_node = parent;
    if (right < 3) {
        child_node.depth++;
        child_node.total_cost += cost;
        swap(child_node.state[tile_zero_index + 1], child_node.state[tile_zero_index]);
        node_queue.push(child_node);
    }
}

void uni_move_operation(Node &node, queue<Node> &node_queue) {
    int tile_zero_index = find_zero_tile_index(node);

    move_up(tile_zero_index, node, node_queue, 1);
    move_down(tile_zero_index, node, node_queue, 1);
    move_left(tile_zero_index, node, node_queue, 1);
    move_right(tile_zero_index, node, node_queue, 1);
}

void uniform_search(Node &problem, Node &goal) {
    queue<Node> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    // push the initial into queue
    nodes_queue.push(initial_node);
    map<vector<int>, bool> visited;


    while (!nodes_queue.empty()) {

        /*
        pop the first item in the queue and perform the operations base on cost
        operations being swap the "zero tile" tile up, down, left, right        
        */
        node = nodes_queue.front();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << node.depth << endl;
            cout << node.total_cost << endl;
            return;
        }
        else {
            /*
            check if the state is repetitve
            if repetitve: skip
            if not: branch
            */
            bool seen = false;    
            for (int i = 0; i < visited.size(); i++) {
                if (visited[node.state]) {
                    seen = true;
                    break;
                }
           
            }
            if (seen) {
                continue;
            }
            visited[node.state] = true;
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
void mis_move_operation(Node &node, queue<Node> &node_queue, Node &goal) {
    int tile_zero_index = find_zero_tile_index(node);

    int lowest_cost = 0;
    vector<int>all_misplaced_cost;

    all_misplaced_cost.push_back(calc_misplaced_top(node, tile_zero_index, goal));
    all_misplaced_cost.push_back(calc_misplaced_bottom(node, tile_zero_index, goal));
    all_misplaced_cost.push_back(calc_misplaced_left(node, tile_zero_index, goal));
    all_misplaced_cost.push_back(calc_misplaced_right(node, tile_zero_index, goal));

    for (int i = 0; i < 4; i++) {
        lowest_cost = min(all_misplaced_cost[i], lowest_cost);
    }
    if (lowest_cost == all_misplaced_cost[0]) {
        move_up(tile_zero_index, node, node_queue, lowest_cost);
    }    
    else if (lowest_cost == all_misplaced_cost[1]) {
        move_down(tile_zero_index, node, node_queue, lowest_cost);
    }    
    else if (lowest_cost == all_misplaced_cost[2]) {
        move_left(tile_zero_index, node, node_queue, lowest_cost);
    }    
    else if (lowest_cost == all_misplaced_cost[3]) {
        move_right(tile_zero_index, node, node_queue, lowest_cost);
    }
}

void misplaced_tile_search (Node &problem, Node &goal) {
    queue<Node> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    // push the initial into queue
    nodes_queue.push(initial_node);
    map<vector<int>, bool> visited;


    while (!nodes_queue.empty()) {
        node = nodes_queue.front();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << node.total_cost << endl;
            return;
        }
        else {
            bool seen = false;    
            for (int i = 0; i < visited.size(); i++) {
                if (visited[node.state]) {
                    seen = true;
                    break;
                }
           
            }
            if (seen) {
                continue;
            }
            visited[node.state] = true;
            mis_move_operation(node, nodes_queue, goal);
        }
    }
}




int manhattan_distance(Node &currentNode, Node &goal) {
    int total_distance = 0;
    int distance;
    int goal_index;
    int current_number;
    int currX, currY, goalX, goalY;
    for (int i = 0; i < 9; i++) {
        if (currentNode.state[i] != goal.state[i] && currentNode.state[i] != 0) {
            goal_index = current_number - 1;
            currX = i % 3;
            currY = i / 3;
            goalX = goal_index % 3;
            goalY = goal_index / 3;
            distance =  abs(currX - goalX) + abs(currY - goalY);
            total_distance += distance;
        }
    }
    return distance;

}
int manhattan_top(Node &parent, int tile_zero_index, Node &goal) {
    int top = tile_zero_index - 3;
    Node temp_node;
    int distance_cost = 0;
    if (top >= 0) {
        temp_node = parent;
        swap(temp_node.state[top], temp_node.state[tile_zero_index]);
        distance_cost = manhattan_distance(temp_node, goal);
    }   
    return distance_cost; 
}
int manhattan_bottom(Node &parent, int tile_zero_index, Node &goal) {
    int bottom = tile_zero_index + 3;
    Node temp_node;
    int distance_cost = 0;
    if (bottom >= 0) {
        temp_node = parent;
        swap(temp_node.state[bottom], temp_node.state[tile_zero_index]);
        distance_cost = manhattan_distance(temp_node, goal);
    }   
    return distance_cost; 
}
int manhattan_left(Node &parent, int tile_zero_index, Node &goal) {
    int left = (tile_zero_index % 3) - 1;
    Node temp_node;
    int distance_cost = 0;
    if (left >= 0) {
        temp_node = parent;
        swap(temp_node.state[tile_zero_index - 1], temp_node.state[tile_zero_index]);
        distance_cost = manhattan_distance(temp_node, goal);
    }   
    return distance_cost; 
}
int manhattan_right(Node &parent, int tile_zero_index, Node &goal) {
    int right = (tile_zero_index % 3) + 1;
    Node temp_node;
    int distance_cost = 0;
    if (right >= 0) {
        temp_node = parent;
        swap(temp_node.state[tile_zero_index - 1], temp_node.state[tile_zero_index]);
        distance_cost = manhattan_distance(temp_node, goal);
    }   
    return distance_cost; 
}

void man_move_operation(Node &node, queue<Node> &node_queue, Node &goal) {
    int tile_zero_index = find_zero_tile_index(node);
    int lowest_cost = 0;
    vector<int>all_manhattan_cost;

    all_manhattan_cost.push_back(calc_misplaced_top(node, tile_zero_index, goal) + manhattan_top(node, tile_zero_index, goal));
    all_manhattan_cost.push_back(calc_misplaced_bottom(node, tile_zero_index, goal) + manhattan_bottom(node, tile_zero_index, goal));
    all_manhattan_cost.push_back(calc_misplaced_left(node, tile_zero_index, goal)+ manhattan_left(node, tile_zero_index, goal));
    all_manhattan_cost.push_back(calc_misplaced_right(node, tile_zero_index, goal)+ manhattan_right(node, tile_zero_index, goal));


    for (int i = 0; i < 4; i++) {
        lowest_cost = min(all_manhattan_cost[i], lowest_cost);
    }
    if (lowest_cost == all_manhattan_cost[0]) {
        move_up(tile_zero_index, node, node_queue, lowest_cost);
    }    
    else if (lowest_cost == all_manhattan_cost[1]) {
        move_down(tile_zero_index, node, node_queue, lowest_cost);
    }    
    else if (lowest_cost == all_manhattan_cost[2]) {
        move_left(tile_zero_index, node, node_queue, lowest_cost);
    }    
    else if (lowest_cost == all_manhattan_cost[3]) {
        move_right(tile_zero_index, node, node_queue, lowest_cost);
    }
}

void manhattan_search(Node &problem, Node &goal) {
    queue<Node> nodes_queue;
    Node initial_node;
    initial_node.state = problem.state;
    Node node;
    // push the initial into queue
    nodes_queue.push(initial_node);
    map<vector<int>, bool> visited;

    while (!nodes_queue.empty()) {
        node = nodes_queue.front();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << node.total_cost << endl;
            return;
        }
        else {
            bool seen = false;    
            for (int i = 0; i < visited.size(); i++) {
                if (visited[node.state]) {
                    seen = true;
                    break;
                }
           
            }
            if (seen) {
                continue;
            }
            visited[node.state] = true;
            man_move_operation(node, nodes_queue, goal);
        }
    }
}

int main() {

    Node goal;
    goal.state = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    Node test;
    test.state = {1, 2, 3, 4, 5, 6, 0, 7, 8};
    manhattan_search(test, goal);


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