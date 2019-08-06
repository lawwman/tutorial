#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

vector<vector<vector<double>>> generate_train_test_data();

vector<vector<vector<double>>> generate_easy_train_test_data();

vector<vector<vector<double>>> randomize_train_data(vector<vector<vector<double>>> train_data);