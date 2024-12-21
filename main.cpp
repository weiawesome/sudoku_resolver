#include <iostream>
#include <set>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> sudokuTable;
set<pair<int, int>> fixedPairs;

bool isValid(int row, int col, int value) {
    int sqrtLength=int(sqrt(sudokuTable.size()));
    int blockRow = (row / sqrtLength) * sqrtLength,blockCol = (col / sqrtLength) * sqrtLength;

    for (int i = 0; i < sudokuTable.size(); i++) {
        if (sudokuTable[row][i] == value || sudokuTable[i][col] == value) {
            return false;
        }
    }

    for (int i = 0; i < sqrtLength; i++) {
        for (int j = 0; j < sqrtLength; j++) {
            if (sudokuTable[blockRow + i][blockCol + j] == value) {
                return false;
            }
        }
    }

    return true;
}

void printSol(int solCount) {
    int sqrtLength=int(sqrt(sudokuTable.size()));
    cout << "Solution " << solCount << ":\n";

    for (int i = 0; i < sudokuTable.size(); i++) {
        if (i % sqrtLength == 0) {
            cout << "+-------+-------+-------+" << endl;
        }

        for (int j = 0; j < sudokuTable.size(); j++) {
            if (j % sqrtLength == 0) {
                cout << "| ";
            }
            cout << sudokuTable[i][j] << " ";
        }
        cout << "|" << endl;
    }
    cout << "+-------+-------+-------+" << endl << endl;
}

void findSol(int row, int col, int& solCount) {
    if (row == sudokuTable.size()) {
        solCount++;
        printSol(solCount);
        return;
    }

    int nextRow = (col == sudokuTable.size()-1) ? row + 1 : row,nextCol = (col == sudokuTable.size()-1) ? 0 : col + 1;

    if (fixedPairs.find({row, col}) != fixedPairs.end()) {
        findSol(nextRow, nextCol, solCount);
    } else {
        for (int i = 0; i < sudokuTable.size(); i++) {
            if (isValid(row, col, i+1)) {
                sudokuTable[row][col] = i+1;
                findSol(nextRow, nextCol, solCount);
                sudokuTable[row][col] = -1;
            }
        }
    }
}

int main() {
    sudokuTable = {
        {-1, 7, -1, -1, -1, 6, -1, 4, 8},
        {-1,-1, 8, -1, -1, 7, 5, -1, -1},
        {-1,-1, -1, 5, -1, -1, -1, -1, 6},
        { 8, 9, -1, -1, -1, -1, 3, -1, -1},
        { 7, -1, -1, -1, 2, -1, 9, -1, 4},
        {-1, -1, 3, -1, -1, -1, -1, 1, 5},
        { 2, -1, -1, -1, -1, 3, -1, -1, -1},
        {-1,-1, 6, 2,-1,-1, 4,-1,-1},
        { 9, 3,-1, 4,-1,-1,-1, 8,-1}
    };

    for (int i = 0; i < sudokuTable.size(); i++) {
        for (int j = 0; j < sudokuTable[i].size(); j++) {
            if (sudokuTable[i][j] != -1) {
                fixedPairs.insert({i, j});
            }
        }
    }

    int solCount = 0;
    findSol(0, 0, solCount);

    if (solCount == 0) {
        cout << "No solution found." << endl;
    } else {
        cout << "Total solutions found: " << solCount << endl;
    }

    return 0;
}
