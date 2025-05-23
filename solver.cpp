#include "solver.h"
#include "grid.h"

// перевірка можливості ходу в задану клітинку
bool is_valid(int current_row, int current_col,
              const std::vector<std::vector<char>>& g,
              const std::vector<std::vector<bool>>& seen) {
    return current_row >= 0 && current_row < SIZE && current_col >= 0 && current_col < SIZE &&
           g[current_row][current_col] != BLOCK && !seen[current_row][current_col];
}

// підрахунок кількості вільних клітинок
int count_empty(const std::vector<std::vector<char>>& g) {
    int count = 0;
    for (auto& row : g)
        for (char c : row)
            if (c != BLOCK) count++;
    return count;
}

// рекурсивний пошук шляху через всі вільні клітинки
bool dfs(int current_row, int current_col, bool ishorizontal,
         int previous_length, int visited_count, int total_free_cells,
         std::vector<std::vector<bool>>& seen,
         std::vector<std::pair<int,int>>& route) {
    // перевірка досягнення фінішу та проходження всіх клітинок
    if (std::make_pair(current_row, current_col) == end_position && visited_count == total_free_cells)
        return true;

    // вибір напрямку руху
    std::vector<std::pair<int,int>> directions = ishorizontal ?
        std::vector<std::pair<int,int>>{{0,1},{0,-1}} : // горизонтальний рух
        std::vector<std::pair<int,int>>{{1,0},{-1,0}};  // вертикальний рух

    // перебір всіх можливих ходів
    for (auto [delta_row, delta_col] : directions) {
        for (int segment_length = 1; segment_length <= SIZE; ++segment_length) {
            if (segment_length == previous_length) continue;

            std::vector<std::pair<int,int>> segment;
            bool is_valid_move = true;
            int next_row = current_row, next_col = current_col;

            // перевірка можливості ходу заданої довжини
            for (int i = 1; i <= segment_length; ++i) {
                next_row += delta_row;
                next_col += delta_col;
                if (!is_valid(next_row, next_col, grid, seen)) {
                    is_valid_move = false;
                    break;
                }
                segment.emplace_back(next_row, next_col);
            }

            if (!is_valid_move) continue;

            // спроба зробити хід
            for (auto [sx, sy] : segment) seen[sx][sy] = true;
            route.insert(route.end(), segment.begin(), segment.end());

            // рекурсивний пошук далі
            if (dfs(next_row, next_col, !ishorizontal, segment_length,
                   visited_count + segment.size(), total_free_cells, seen, route))
                return true;

            // відміна ходу якщо шлях не знайдено
            for (auto [sx, sy] : segment) seen[sx][sy] = false;
            route.resize(route.size() - segment.size());
        }
    }

    return false;
}
