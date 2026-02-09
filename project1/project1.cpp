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
    int g = 0;
    int f = 0;
    int h = 0;
};

struct CompareEvalution {
    bool operator()(Node const& n1, Node const& n2)
    {
        return n1.f > n2.f;
    }
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
void move_up(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int top = tile_zero_index - 3;
    Node child_node = parent;
    if (top >= 0) {
        child_node.g = parent.g + 1;
        child_node.depth = parent.depth + 1;
        child_node.h = heuristic;
        child_node.f = child_node.h + child_node.g;
        swap(child_node.state[top], child_node.state[tile_zero_index]);
        nodes_queue.push(child_node);
    }    
}
void move_down(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int bottom = tile_zero_index + 3;
    Node child_node = parent;
    if (bottom <= 8) {
        child_node.g = parent.g + 1;
        child_node.depth = parent.depth + 1;
        child_node.h = heuristic;
        child_node.f = child_node.h + child_node.g;
        swap(child_node.state[bottom], child_node.state[tile_zero_index]);
        nodes_queue.push(child_node);
    }    
}
void move_left(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int left = (tile_zero_index % 3) - 1;
    Node child_node = parent;
    if (left >= 0) {
        child_node.g = parent.g + 1;
        child_node.depth = parent.depth + 1;
        child_node.h = heuristic;
        child_node.f = child_node.h + child_node.g;
        swap(child_node.state[tile_zero_index - 1], child_node.state[tile_zero_index]);
        nodes_queue.push(child_node);
    }    
}
void move_right(int tile_zero_index, Node &parent, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, int heuristic) {
    int right = (tile_zero_index % 3) + 1;
    Node child_node = parent;
    if (right < 3) {
        child_node.g = parent.g + 1;
        child_node.depth = parent.depth + 1;
        child_node.h = heuristic;
        child_node.f = child_node.h + child_node.g;
        swap(child_node.state[tile_zero_index + 1], child_node.state[tile_zero_index]);
        nodes_queue.push(child_node);
    }
}

void uni_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue) {
    int tile_zero_index = find_zero_tile_index(node);

    move_up(tile_zero_index, node, nodes_queue, 0);
    move_down(tile_zero_index, node, nodes_queue, 0);
    move_left(tile_zero_index, node, nodes_queue, 0);
    move_right(tile_zero_index, node, nodes_queue, 0);
}

void uniform_search(Node &problem, Node &goal) {
    priority_queue<Node, vector<Node>, CompareEvalution> nodes_queue;
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
        node = nodes_queue.top();
        nodes_queue.pop();
        if (node.state == goal.state) {
            cout << node.depth << endl;
            cout << node.g << endl;
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
void mis_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, Node &goal) {
    int tile_zero_index = find_zero_tile_index(node);

    int h_top = (calc_misplaced_top(node, tile_zero_index, goal));
    int h_bot = (calc_misplaced_bottom(node, tile_zero_index, goal));
    int h_left = (calc_misplaced_left(node, tile_zero_index, goal));
    int h_right = (calc_misplaced_right(node, tile_zero_index, goal));

    move_up(tile_zero_index, node, nodes_queue, h_top);
    move_down(tile_zero_index, node, nodes_queue, h_bot);
    move_left(tile_zero_index, node, nodes_queue, h_left);
    move_right(tile_zero_index, node, nodes_queue, h_right);
}

void misplaced_tile_search (Node &problem, Node &goal) {
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
            cout << node.g << endl;
            return;
        }
        else {
            if (visited[node.state]) continue;
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

void man_move_operation(Node &node, priority_queue<Node, vector<Node>, CompareEvalution> &nodes_queue, Node &goal) {
    int tile_zero_index = find_zero_tile_index(node);

    int h_top = (manhattan_top(node, tile_zero_index, goal));
    int h_bot = (manhattan_bottom(node, tile_zero_index, goal));
    int h_left = (manhattan_left(node, tile_zero_index, goal));
    int h_right = (manhattan_right(node, tile_zero_index, goal));


    move_up(tile_zero_index, node, nodes_queue, h_top);
    move_down(tile_zero_index, node, nodes_queue, h_bot);
    move_left(tile_zero_index, node, nodes_queue, h_left);
    move_right(tile_zero_index, node, nodes_queue, h_right);
}

void manhattan_search(Node &problem, Node &goal) {
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
            cout << node.g << endl;
            return;
        }
        else {
            if (visited[node.state]) continue;
            visited[node.state] = true;
            man_move_operation(node, nodes_queue, goal);
        }
    }
}

int main() {

    Node goal;
    goal.state = {1, 2, 3, 4, 5, 6, 7, 8, 0};

    Node problem;
    problem.state = {0, 7, 2, 4, 6, 1, 3, 5, 8};
    misplaced_tile_search(problem, goal);


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