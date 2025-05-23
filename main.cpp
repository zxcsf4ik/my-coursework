#include <iostream>
#include <vector>
#include "grid.h"
#include "solver.h"
#include "visual.h"
#include "input.h"

int main() {
    while (true) {
        // Ініціалізація сітки
        grid = {
            {' ', ' ', ' ', ' ', ' ', ' ', 'F'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', '#', '#', ' '},
            {' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' ', ' ', '#', '#'},
            {' ', ' ', ' ', ' ', ' ', ' ', ' '},
            {'S', ' ', ' ', ' ', ' ', ' ', ' '}
        };

        print_initial_grid();

        // взаємодія з користувачем
        std::cout << "Do you want to use this grid? (yes / no / exit): ";
        std::string user_choice;
        std::getline(std::cin, user_choice);

        if (user_choice == "exit") {
            break;
        }
        if (user_choice == "no") {
            // Очистити сітку, залишити тільки старт та фініш
            grid = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, EMPTY));
            grid[start_position.first][start_position.second] = START;
            grid[end_position.first][end_position.second] = FINISH;

            print_initial_grid();
            user_input_blocks();
            print_initial_grid();
        } else if (user_choice != "yes") {
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        // пошук шляху
        int total_free_cells = count_empty(grid);
        std::vector<std::vector<bool>> seen(SIZE, std::vector<bool>(SIZE, false));
        std::vector<std::pair<int,int>> route;
        seen[start_position.first][start_position.second] = true;
        route.push_back(start_position);

        // спроба знайти шлях спочатку горизонтально, потім вертикально
        bool path_found = dfs(start_position.first, start_position.second,
                              true, 0, 1, total_free_cells, seen, route) ||
                          dfs(start_position.first, start_position.second,
                              false, 0, 1, total_free_cells, seen, route);

        if (path_found) {
            std::cout << "Path found:\n\n";
            draw_grid(route);
        } else {
            std::cout << "No valid path found.\n";
        }

        std::cout << "\nPress Enter to try again or type \"exit\" to quit.\n";
        std::getline(std::cin, user_choice);
        if (user_choice == "exit") break;
    }

    return 0;
}
