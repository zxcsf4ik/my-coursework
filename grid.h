#ifndef GRID_H
#define GRID_H

#include <vector>
#include <utility>

// базові константи для розміру та символів
extern const int SIZE;
extern const char EMPTY;
extern const char BLOCK;
extern const char START;
extern const char FINISH;

// початкова конфігурація сітки
extern std::vector<std::vector<char>> grid;
extern std::pair<int,int> start_position;
extern std::pair<int,int> end_position;

#endif
