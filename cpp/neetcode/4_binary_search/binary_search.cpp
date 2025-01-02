#include <vector>

/*
Given an array of integers nums which is sorted in ascending order, 
and an integer target, write a function to search target in nums. 
If target exists, then return its index. Otherwise, return -1.

You must write an algorithm with O(log n) runtime complexity. 

Example 1:
Input: nums = [-1,0,3,5,9,12], target = 9
Output: 4

Explanation: 9 exists in nums and its index is 4
Example 2:

Input: nums = [-1,0,3,5,9,12], target = 2
Output: -1

Explanation: 2 does not exist in nums so return -1
*/

class Solution {
public:
    int search(std::vector<int>& nums, int target) {
        int leftPointer = 0;
        int rightPointer = nums.size()-1;
        int midpointIdx = 0;

        while (nums[midpointIdx] != target) {
            midpointIdx = (leftPointer + rightPointer)/2;
            if (target < nums[midpointIdx]) {
                rightPointer = midpointIdx - 1;
            }
            else if (target > nums[midpointIdx]) {
                leftPointer = midpointIdx + 1;
            }

            if (leftPointer > rightPointer) return -1;
        }
        return midpointIdx;
    }
};