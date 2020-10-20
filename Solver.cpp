#include "Solver.hpp"
#include <iostream>

std::vector<std::vector<int>> SudokuSolver::solve(const std::vector<std::vector<int>> question)
{
    std::vector<std::vector<int>> ans = question;

    std::vector<std::vector<std::vector<bool>>> probably(9, std::vector<std::vector<bool>>(9, std::vector<bool>(10, true)));

    // 土のマスにも0は置けない
    for (size_t y = 0; y < 9; ++y)
    {
        for (size_t x = 0; x < 9; ++x)
        {
            probably[y][x][0] = false;
        }
    }    

    // すでに確定してるマスのprobablyを確定させる
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            if (question[y][x] != 0)
            {
                for (int i = 1; i <= 9; ++i)
                {
                    if (i == question[y][x]) continue;

                    probably[y][x][i] = false;
                }
                
            }
        }
        
    }
    
    while (!SudokuSolver::is_finish(ans))
    {        
        for (int y = 0; y < 9; ++y)
        {
            for (int x = 0; x < 9; ++x)
            {
                if (ans[y][x] == 0) continue;

                SudokuSolver::restrict(probably, x, y, ans[y][x]);
            }
        }

        SudokuSolver::decide_number(ans, probably);
    }

    return ans;
}

bool SudokuSolver::is_finish(const std::vector<std::vector<int>> board)
{
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            if (board[y][x] == 0) return false;
        }
        
    }
    
    return true;
}

void SudokuSolver::restrict(std::vector<std::vector<std::vector<bool>>>& probably, int x, int y, int number)
{
    // horizontaly
    for (int i = 0; i < 9; ++i)
    {
        if (i == x) continue;
        
        probably[y][i][number] = false;
    }
    
    //verticaly
    for (int i = 0; i < 9; ++i)
    {
        if (i == y) continue;

        probably[i][x][number] = false;
    }
    
    // block
    int startX = x / 3 * 3;
    int endX = startX + 2;
    int startY = y / 3 * 3;
    int endY = startY + 2;

    for (int i = startY; i <= endY; ++i)
    {
        for (int j = startX; j <= endX; ++j)
        {
            if (j == x && i == y) continue;

            probably[i][j][number] = false;
        }
    }
    
}

void SudokuSolver::decide_number(std::vector<std::vector<int>>& ans, const std::vector<std::vector<std::vector<bool>>>& probably)
{
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            if (ans[y][x] == 0)
            {
                int count = 0;
                int idx = 0;
                for (int i = 1; i <= 9; ++i)
                {
                    if (probably[y][x][i])
                    {
                        ++count;
                        idx = i;
                    }
                }
                
                if (count == 1)
                {
                    ans[y][x] = idx;
                }
            }
        }
    }
    
}

void SudokuSolver::print_board(const std::vector<std::vector<int>> board)
{
    std::cout << "-------------------" << std::endl;
    for (int y = 0; y < 9; ++y)
    {
        for (int x = 0; x < 9; ++x)
        {
            std::cout << board[y][x] << ' ';
            if (x % 3 == 2) std::cout << ' ';
        }
        std::cout << std::endl;
        if (y % 3 == 2) std::cout << std::endl;
    }
    std::cout << "-------------------" << std::endl;
}