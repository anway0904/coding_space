#include<vector>

/*
You are given an integer array heights where heights[i] represents the height of the i th bar
You may choose any two bars to form a container. Return the maximum amount of water a container can store.

Example 1:
Input: height = [1,7,2,5,4,7,3,6]
Output: 36

Example 2:
Input: height = [2,2,2]
Output: 4
*/

/*
Algorithm:
    1. Start with two pointers at the start and end of the height array
    2. Calculate the area of "water". min(height[left_ptr], height[right_ptr])*(right_ptr-lft_ptr)
    3. Update the max_area
    3. Increment/Decrement the lower height from the two pointers
    4. Repeat until left_ptr < right_ptr
*/
class Solution {
public:
    int maxArea(std::vector<int>& height) {
        int maxAreaFound = 0;
        int leftPtr = 0;
        int rightPtr = height.size()-1;

        while (leftPtr < rightPtr) {
            int area = std::min(height[leftPtr], height[rightPtr])*(rightPtr-leftPtr);
            if (area > maxAreaFound) maxAreaFound = area;
            if (height[leftPtr] <= height[rightPtr]) leftPtr++;
            else rightPtr--;
        }

        return maxAreaFound;
    }
};