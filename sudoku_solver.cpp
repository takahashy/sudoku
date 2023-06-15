/*
    sudoku solver
    Author: Yuma Takahashi

        Solves a sudoku puzzle using backtracking algorithm

*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <set>

using namespace std;

#define NUM 9
typedef vector<vector<int>> vecs;
typedef vector<int> vec;

vecs readSudoku(string filename);
bool solveSudoku(vecs &grid);
bool solved(vecs grid, int &row, int &col);
bool validRow(vecs grid, int row, int num);
bool validCol(vecs grid, int col, int num);
bool validSub(vecs grid, int row, int col, int num);
bool allValid(vecs grid, int row, int col, int num);
void printSudoku(vecs grid);

vecs readSudoku(string filename)
{
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "FILE ERROR: File not found";
        exit(EXIT_FAILURE);
    }

    vecs grid;
    vec row;
    int index = 1, num = 0;

    while (!infile.eof()) {
        infile >> num;
        row.push_back(num);
        if (index % 9 == 0) {
            grid.push_back(row);
            row.clear();
        }
        index++;
    }
    
    return grid;
}

bool solveSudoku(vecs &sudoku)
{
    int row, col;
    if (solved(sudoku, row, col)) return true;

    for (int num = 1; num <= 9; num++) {
        if (allValid(sudoku, row, col, num)) {
            sudoku[row][col] = num;
            if (solveSudoku(sudoku)) return true;
            sudoku[row][col] = 0;
        }
    }
    return false;
}

bool solved(vecs grid, int &row, int &col)
{
    for (int i = 0; i < NUM; i++) {
        for (int j = 0; j < NUM; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                return false;
            }
        }
    }
    return true;
}


bool validRow(vecs grid, int row, int num)
{
    for (int col = 0; col < 9; col++) {
        if (grid[row][col] == num) return false;
    }
    return true;
}

bool validCol(vecs grid, int col, int num)
{
    for (int row = 0; row < 9; row++) {
        if (grid[row][col] == num) return false;
    }
    return true;
}

bool validSub(vecs grid, int row, int col, int num)
{
    int start_row = row / 3 * 3;
    int start_col = col / 3 * 3;
    for (int i = start_row; i < start_row + 3; i++) {
        for (int j = start_col; j < start_col + 3; j++) {
            if (grid[i][j] == num) return false;
        }
    }
    return true;
}

bool allValid(vecs grid, int row, int col, int num)
{
    return validRow(grid, row, num) && validCol(grid, col, num) && validSub(grid, row, col, num);
}


void printSudoku(vecs sudoku)
{
    for (vec x : sudoku) {
        for (int y : x) {
            cout << y << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./sudoku [*filename]";
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        vecs board = readSudoku(argv[i]);

        if (solveSudoku(board)) {
            cout << "\033[92mCan be solved!\033[0m\n";
        } else {
            cout << "\033[91mCANNOT be solved\033[0m\n";
        }
        printSudoku(board);

    }
}

