#include <vector>
/*
Given an array of integers numbers that is sorted in non-decreasing order.
Return the indices (1-indexed) of two numbers, [index1, index2], such that they add up 
to a given target number target and index1 < index2. Note that index1 and index2 cannot be equal, therefore you may not use the same element twice.

There will always be exactly one valid solution.

Your solution must use O(1) additional space.

Example 1:
Input: numbers = [1,2,3,4], target = 3
Output: [1,2]

Explanation:
The sum of 1 and 2 is 3. Since we are assuming a 1-indexed array, index1 = 1, index2 = 2. We return [1, 2].
*/

/*
Algorithm:
    1. Initialize two pointers at the start and end of the numbers array
    2. Compute the sum of the two elements
    3. If sum = target, return
    4. If sum<target increment left pointer
    5. If sum>target decrement right pointer
*/
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& numbers, int target) {
        std::vector<int>::iterator sPtr = numbers.begin();
        std::vector<int>::iterator ePtr = numbers.end() -1;

        while (*sPtr + *ePtr != target) {

            while (*sPtr + *ePtr > target){
                ePtr--;
            }

            while (*sPtr + *ePtr < target){
                sPtr++;
            }
        }

        return {static_cast<int>(sPtr - numbers.begin() + 1), 
                static_cast<int>(ePtr - numbers.begin() + 1)};
    }
};
