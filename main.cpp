/*********************************/
/* Author: Alex Seaver           */
/* Last Modified: 05/09/2018     */
/* Purpose: Solve Sudoku Puzzles */
/*********************************/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "sudokuSolver.h"
#include "sudokuSolver.cpp"
using namespace std;

int main()
{
    char done;
    cout << "This program is able to solve Sudoku Puzzles.\n";
    do
    {
        int g[9][9];
        sudoku g1(g);
        if(g1.solveSudoku())
        {
            cout << "The puzzle has been solved.\n";
        }
        if(!g1.solveSudoku())
        {
            cout << "This puzzle has no solution.\n";
        }
        g1.printSudokuGrid();
        cout << "Would you like to exit the program? {Y/N}\n";
        cin >> done;
        cin.ignore();
    } while(done != 'Y' && done != 'y');
    cout << "Thank you for using the SudokuSolver. Press Enter to exit.\n";
    cin.get();
    return 0;
}
