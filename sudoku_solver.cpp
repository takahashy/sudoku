#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef vector<vector<int>> intvec;

intvec sudoku(string filename)
{
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "FILE ERROR: File not found";
        exit(EXIT_FAILURE);
    }

    vector<vector<int>> grid;
    vector<int> row;
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

solveSudoku(intvec sudoku)
{
    
}

void printSudoku(intvec sudoku)
{
    for (vector<int> x : sudoku) {
        for (int y : x) {
            cout << y << " ";
        }
        cout << "\n";
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: ./sudoku [filename]";
        exit(EXIT_FAILURE);
    }

    intvec board = sudoku(argv[1]);

    printSudoku(board);
}

