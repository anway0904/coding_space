#include <vector>
/*
Given n non-negative integers representing an elevation map where the width of each bar is 1, 
compute how much water it can trap after raining.

Example 1:
Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
Output: 6
Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
In this case, 6 units of rain water (blue section) are being trapped.

Example 2:
Input: height = [4,2,0,3,2,5]
Output: 9
*/

/*
Algorithm
    1. Initialize a left and right pointer at the start and end of the height array
    2. Calculate the height of "water" in between the left and right pointer --> min(height[leftPtr], height[rightPtr])
    3. Calculate the area of the "water" --> (curr_height - prev_height)*(rightPtr - leftPtr - 1)
    4. Need to subtract the previous height to not calculate the same area twice
    5. As you iterate over the array, subtract the area of "blocks" from the calculated water area.
*/
class Solution {
public:
    int trap(std::vector<int>& height) {
        int currWaterHeight = 0;
        int prevWaterHeight = 0;
        int currWaterArea = 0;
        int leftPtr = 0;
        int rightPtr = height.size() - 1;

        while (leftPtr < rightPtr) {
            
            currWaterHeight = std::min(height[leftPtr], height[rightPtr]);
            if (currWaterHeight > prevWaterHeight) {
                currWaterArea += (currWaterHeight - prevWaterHeight) * (rightPtr - leftPtr - 1);
                prevWaterHeight = currWaterHeight;
            }
            if (height[leftPtr] <= height[rightPtr]) {
                leftPtr++;
                if (currWaterArea && leftPtr < rightPtr) {
                    currWaterArea -= std::min(prevWaterHeight, height[leftPtr]);
                }
            }
            else {
                rightPtr--;
                if (currWaterArea && leftPtr < rightPtr) {
                    currWaterArea -= std::min(prevWaterHeight, height[rightPtr]);
                }
            }
        }
        return currWaterArea;
    }
};