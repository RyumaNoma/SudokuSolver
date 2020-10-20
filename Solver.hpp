#pragma once
#include <vector>

namespace SudokuSolver
{
    std::vector<std::vector<int>> solve(const std::vector<std::vector<int>> question);
    bool is_finish(const std::vector<std::vector<int>> board);
    void restrict(std::vector<std::vector<std::vector<bool>>>& probably, int x, int y, int number);
    void decide_number(std::vector<std::vector<int>>& ans, const std::vector<std::vector<std::vector<bool>>>& probably);

    void print_board(const std::vector<std::vector<int>> board);
}