#include "input.h"
#include "grid.h"
#include <iostream>
#include <sstream>
#include <string>

// зчитування координат блоків які потрібно обходити від користувача
void user_input_blocks() {
    std::cout << "Enter the coordinates of the blocks you want to set (format: x,y).\n";
    std::cout << "Enter one or more separated by spaces. Type \"start\" to begin, or \"exit\" to quit.\n";

    std::string input_line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input_line);

        if (input_line == "start") {
            break;
        }
        if (input_line == "exit") {
            exit(0);
        }
        std::stringstream ss(input_line);
        std::string coordinates;
        while (ss >> coordinates) {
            size_t pos = coordinates.find(',');
            if (pos != std::string::npos) {
                int col_position = std::stoi(coordinates.substr(0,pos));
                int row_position = std::stoi(coordinates.substr(pos+1));
                int actual_row = SIZE - 1 - row_position;
                if (col_position >= 0 && col_position < SIZE &&
                    row_position >= 0 && row_position < SIZE &&
                    std::make_pair(actual_row,col_position) != start_position &&
                    std::make_pair(actual_row,col_position) != end_position) {
                    grid[actual_row][col_position] = BLOCK;
                    } else {
                        std::cout << "Invalid coordinates: " << coordinates << std::endl;
                    }
            } else {
                std::cout << "Invalid coordinate format: " << coordinates << std::endl;
            }
        }
    }
}

