/************************************************************/
/* Author: Alex Seaver                                      */
/* Last Modified: 05/09/2018                                */
/* Purpose: Utilizes the function descriptions declarations */
/*          given by D.S. Malik to solve a Sudoku puzzle    */
/************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "sudokuSolver.h"
using namespace std;

sudoku::sudoku()
/* Constructs the 2D array with all 0s */
{
    initializeSudokuGrid();
}

sudoku::sudoku(int g[][9])
/* Constructs the 2D array */
{
    initializeSudokuGrid(g);
}

void sudoku::initializeSudokuGrid()
/* Constructs a blank grid */
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            grid[i][j] = 0;
        }
    }
}

void sudoku::initializeSudokuGrid(int g[][9])
/* Obtains the file name of the unsolved puzzle and populates the 2D array, with blank spaces denoted as 0s,
   a space between each number, and a newline character denoting each new row. */
{
    int input;
    string filename;
    ifstream inf;
    cout << "What is the name of the file where the grid is stored?\n";
    getline(cin, filename);
    inf.open(filename.c_str());
    while(inf.fail())
    {
        cout << "Not a valid file name, please try again.\n";
        getline(cin, filename);
        inf.open(filename.c_str());
    }
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            inf >> input;
            grid[i][j] = input;
        }
    }
    inf.close();
}

void sudoku::printSudokuGrid()
/* Once the puzzle has been solved, outputs a text file in the same format as the input */
{
   ofstream outf;
   outf.open("Solved.txt");
   for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            outf << grid[i][j];
            outf << " ";
        }
        outf << endl;
    }
    outf.close();
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            cout << grid[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

bool sudoku::solveSudoku()
/* Recursively solves the puzzle */
{
    int row, col;
    if (findEmptyGridSlot(row, col))
    {
        for (int num = 1; num <= 9; num++)
        {
            if (canPlaceNum(row, col, num))
            {
                grid[row][col] = num;
                if (solveSudoku()) //recursive call
                    return true;
                grid[row][col] = 0; //backtrack
            }
        }
        return false;
    }
    else
        return true; //there are no empty slots
}

bool sudoku::findEmptyGridSlot(int &row, int &col)
/* Iterates through the puzzle until a blank space is found */
{
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            row = i, col = j;
            if(grid[row][col] == 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool sudoku::canPlaceNum(int row, int col, int num)
/* Determines if a given number can be placed in a given spot */
{
    if(numAlreadyInRow(row, num) || numAlreadyInCol(col, num) || numAlreadyInBox(row, col, num))
    {
        return false;
    }
    else
        return true;
}

bool sudoku::numAlreadyInRow(int row, int num)
/* Determines if there is any instance of the given number in the row */
{
    for(int col = 0; col < 9; col++)
    {
        if(grid[row][col] == num)
        {
            return true;
        }
    }
    return false;
}

bool sudoku::numAlreadyInCol(int col, int num)
/* Determines if there is any instance of the given number in the column */
{
    for(int row = 0; row < 9; row++)
    {
        if(grid[row][col] == num)
        {
            return true;
        }
    }
    return false;
}

bool sudoku::numAlreadyInBox(int smallGridRow, int smallGridCol, int num)
/* Determines if there is any instance of the given number in the three by three box */
{
    if(smallGridRow < 3 && smallGridCol < 3)
    {
        for(int row = 0; row < 3; row++)
        {
            for(int col = 0; col < 3; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 3 && smallGridCol < 6 && smallGridCol > 2)
    {
        for(int row = 0; row < 3; row++)
        {
            for(int col = 3; col < 6; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 3 && smallGridCol < 9 && smallGridCol > 5)
    {
        for(int row = 0; row < 3; row++)
        {
            for(int col = 6; col < 9; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 6 && smallGridRow > 2 && smallGridCol < 3)
    {
        for(int row = 3; row < 6; row++)
        {
            for(int col = 0; col < 3; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 6 && smallGridRow > 2 && smallGridCol < 6 && smallGridCol > 2)
    {
        for(int row = 3; row < 6; row++)
        {
            for(int col = 3; col < 6; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 6 && smallGridCol > 2 && smallGridCol < 9 && smallGridCol > 5)
    {
        for(int row = 3; row < 6; row++)
        {
            for(int col = 6; col < 9; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 9 && smallGridRow > 5 && smallGridCol < 3)
    {
        for(int row = 6; row < 9; row++)
        {
            for(int col = 0; col < 3; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 9 && smallGridRow > 5 && smallGridCol < 6 && smallGridCol > 2)
    {
        for(int row = 6; row < 9; row++)
        {
            for(int col = 3; col < 6; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    if(smallGridRow < 9 && smallGridRow > 5 && smallGridCol < 9 && smallGridCol > 5)
    {
        for(int row = 6; row < 9; row++)
        {
            for(int col = 6; col < 9; col++)
            {
                if(grid[row][col] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
    return false;
}

