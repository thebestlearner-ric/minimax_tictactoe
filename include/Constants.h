#pragma once
#include <string>
#include <vector>
const int DIMENSION = 3;
const char X_VAL = 'X';
const char O_VAL = 'O';
const char NO_VAL = '_';

const int WINS = 1;
const int LOSES = 1;
const int ZEROS = 0;

const std::string ROW = "ROW";
const std::string COL = "COLUMN";
const std::string LEFT = "LEFT";
const std::string RIGHT = "RIGHT";

const std::vector<std::string> GRIDS { ROW, COL, LEFT, RIGHT };
