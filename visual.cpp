#include "visual.h"
#include "grid.h"
#include <iostream>

// символи для відображення шляху
const char PATH_HORIZONTAL = 205;   // ═ горизонтальна лінія
const char PATH_VERTICAL = 186;     // ║ вертикальна лінія
const char PATH_UP_RIGHT = 200;     // ╚ кут вверх-направо
const char PATH_UP_LEFT = 188;      // ╝ кут вверх-наліво
const char PATH_DOWN_RIGHT = 201;   // ╔ кут вниз-направо
const char PATH_DOWN_LEFT = 187;    // ╗ кут вниз-наліво

// відображення сітки з шляхом
void draw_grid(const std::vector<std::pair<int,int>>& route) {
    std::vector<std::vector<char>> grid_display(SIZE, std::vector<char>(SIZE, EMPTY));
    for (int row = 0; row < SIZE; ++row)
        for (int col = 0; col < SIZE; ++col)
            if (grid[row][col] == BLOCK)
                grid_display[row][col] = BLOCK;

    // вибір символу для відображення частини шляху
    auto getSymbol = [](std::pair<int,int> previous, std::pair<int,int> current, std::pair<int,int> next) -> char {
        int dr1 = current.first - previous.first;
        int dc1 = current.second - previous.second;
        int dr2 = next.first - current.first;
        int dc2 = next.second - current.second;

        if (dr1 == 0 && dr2 == 0) return PATH_HORIZONTAL;
        if (dc1 == 0 && dc2 == 0) return PATH_VERTICAL;
        if ((dr1==-1 && dc2==1)||(dc1==-1&&dr2==1)) return PATH_DOWN_RIGHT;
        if ((dr1==-1 && dc2==-1)||(dc1==1&&dr2==1)) return PATH_DOWN_LEFT;
        if ((dr1==1 && dc2==1)||(dc1==-1&&dr2==-1)) return PATH_UP_RIGHT;
        if ((dr1==1 && dc2==-1)||(dc1==1&&dr2==-1)) return PATH_UP_LEFT;
        return '*';
    };

    // формування шляху на сітці
    for (size_t i = 1; i + 1 < route.size(); ++i) {
        auto prev = route[i-1];
        auto cur = route[i];
        auto next = route[i+1];
        grid_display[cur.first][cur.second] = getSymbol(prev, cur, next);
    }

    grid_display[start_position.first][start_position.second] = START;
    grid_display[end_position.first][end_position.second] = FINISH;

    // виведення сітки
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) std::cout << "+---";
        std::cout << "+\n";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "| " << grid_display[i][j] << ' ';
        }
        std::cout << "|\n";
    }
    for (int j = 0; j < SIZE; ++j) std::cout << "+---";
    std::cout << "+\n";
}

// виведення початкової сітки
void print_initial_grid() {
    std::cout << "Initial grid:\n\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) std::cout << "+---";
        std::cout << "+\n";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << "| " << grid[i][j] << ' ';
        }
        std::cout << "|\n";
    }
    for (int j = 0; j < SIZE; ++j) std::cout << "+---";
    std::cout << "+\n";
}