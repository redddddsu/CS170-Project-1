#include <iostream>
#include <vector>
#include <map>
#include <chrono>

using namespace std;
using namespace std::chrono;

#include "utility.hpp"
#include "manhattan.hpp"
#include "misplaced.hpp" 
#include "uniform.hpp"

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

    Node problem9;

    vector<Node> problems;
    problems.push_back(problem1);
    problems.push_back(problem2);
    problems.push_back(problem3);
    problems.push_back(problem4);
    problems.push_back(problem5);
    problems.push_back(problem6);
    problems.push_back(problem7);
    problems.push_back(problem8);

    cout << "Enter test case: " << endl;
    cout << "Test 1" << endl;
    cout << "Test 2" << endl;
    cout << "Test 3" << endl;
    cout << "Test 4" << endl;
    cout << "Test 5" << endl;
    cout << "Test 6" << endl;
    cout << "Test 7" << endl;
    cout << "Test 8" << endl;
    cout << "Custom test 9" << endl;

    int digit;
    int test_case;
    cin >> test_case;

    if (test_case == 9) {
        cout << "Enter 9 digits from 0-9" << endl;
        for (int i = 0; i < 9; i++) {
            cin >> digit;
            problem9.state.push_back(digit);
        }
        problems.push_back(problem9);
    }

    cout << "Test: " << test_case << endl;
    cout << "Uniform Search" << endl;
    auto start = high_resolution_clock::now();
    uniform_search(problems[test_case - 1], goal);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time : " << duration.count() << endl;
    cout << endl;

    cout << "Misplaced Search" << endl;
    cout << "Test: " << test_case << endl;
    start = high_resolution_clock::now();
    misplaced_tile_search(problems[test_case - 1], goal);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time : " << duration.count() << endl;
    cout << endl;

    cout << "Manhattan Search" << endl;
    cout << "Test: " << test_case << endl;
    start = high_resolution_clock::now();
    manhattan_search(problems[test_case - 1], goal);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time : " << duration.count() << endl;
    cout << endl;



    return 0;
}


