#include <vector>
#include <unordered_set>
/*
You are given a a 9 x 9 Sudoku board board. A Sudoku board is valid if the following rules are followed:

1. Each row must contain the digits 1-9 without duplicates.
2. Each column must contain the digits 1-9 without duplicates.
3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without duplicates.
4. Return true if the Sudoku board is valid, otherwise return false

Note: A board does not need to be full or be solvable to be valid.
*/

/*
Algorithm:
    1. Create a vector of sets for each row, column and sub_block (27 sets)
    2. Iterate over the sudoku matrix and if element found in corresponding row, col or sub_block, return false
    3. Else add the element to the sets corresponding to the row, col and sub_block
*/
class Solution {
public:
    bool isValidSudoku(std::vector<std::vector<char>>& board) {
        int subBlock;
    
        // Creating one hash map for each row, col and subBlock (3*9)
        std::vector<std::unordered_set<int>> boardVec(27);

        for(int row=0 ; row<9 ; row++){
            for(int col=0 ; col<9 ; col++){
                if (board[row][col] == '.') continue;
                subBlock = col/3 + 3*(row/3);

                // return false if duplicate found
                if (boardVec[subBlock].find(board[row][col]) != \
                    boardVec[subBlock].end()) return false;

                else boardVec[subBlock].insert(board[row][col]);

                if (boardVec[row + 9].find(board[row][col]) != \
                    boardVec[row + 9].end()) return false;

                else boardVec[row + 9].insert(board[row][col]);

                if (boardVec[col+18].find(board[row][col]) != \
                    boardVec[col+18].end()) return false;

                else boardVec[col+18].insert(board[row][col]);

            }
        }
        return true;
    }
};
