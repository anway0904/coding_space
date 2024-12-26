#include <vector>
/*
You are given an m x n integer matrix matrix with the following two properties:

Each row is sorted in non-decreasing order.
The first integer of each row is greater than the last integer of the previous row.
Given an integer target, return true if target is in matrix or false otherwise.

You must write a solution in O(log(m * n)) time complexity.

Example 1:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
Output: true

Example 2:
Input: matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
Output: false
*/
class Solution {
public:
    bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
        int oneDIdx;
        int rows = matrix.size();
        int cols = matrix[0].size();

        int leftIdx = 0;
        int rightIdx = (rows*cols)-1;
        int midpointIdx = 0;

        while (matrix[midpointIdx/cols][midpointIdx%cols] != target) {
            midpointIdx = (leftIdx + rightIdx)/2;
            if (target < matrix[midpointIdx/cols][midpointIdx%cols]) {
                rightIdx = midpointIdx - 1;
            }
            else if (target > matrix[midpointIdx/cols][midpointIdx%cols]) {
                leftIdx = midpointIdx + 1;
            }

            if (leftIdx > rightIdx) return false;
        }
        return true;
    }
};