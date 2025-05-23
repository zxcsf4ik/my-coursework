#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <utility>

// перевірка можливості ходу в задану клітинку
bool is_valid(int current_row, int current_col,
              const std::vector<std::vector<char>>& g,
              const std::vector<std::vector<bool>>& seen);

// підрахунок кількості вільних клітинок
int count_empty(const std::vector<std::vector<char>>& g);

// рекурсивний пошук шляху через всі вільні клітинки
bool dfs(int current_row, int current_col, bool ishorizontal,
         int previous_length, int visited_count, int total_free_cells,
         std::vector<std::vector<bool>>& seen,
         std::vector<std::pair<int,int>>& route);

#endif