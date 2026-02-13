#include "utility.hpp"

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