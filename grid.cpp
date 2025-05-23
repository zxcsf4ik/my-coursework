#include "grid.h"

// базові константи для розміру та символів
const int SIZE = 7;
const char EMPTY = ' ';
const char BLOCK = '#';
const char START = 'S';
const char FINISH = 'F';

// початкова конфігурація сітки
std::vector<std::vector<char>> grid = {
    {' ', ' ', ' ', ' ', ' ', ' ', 'F'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', '#', '#', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', '#', '#'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'S', ' ', ' ', ' ', ' ', ' ', ' '}
};

std::pair<int,int> start_position = {6,0};
std::pair<int,int> end_position = {0,6};