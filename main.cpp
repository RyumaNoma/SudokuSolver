#include "Solver.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(void)
{
    std::ifstream input("input.txt");
    if (!input.is_open())
    {
        std::cout << "cannot open!" << std::endl;
        return -1;
    }

    std::vector<std::vector<int>> board(9, std::vector<int>(9, 0));
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            char c;
            input >> c;
            board[y][x] = (int)c - '0';
        }
    }

    input.close();

    std::vector<std::vector<int>> ans = SudokuSolver::solve(board);

    SudokuSolver::print_board(ans);
    
    return 0;
}