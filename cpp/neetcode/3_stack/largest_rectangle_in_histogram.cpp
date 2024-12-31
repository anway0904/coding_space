#include <stack>
#include <vector>

/*
Given an array of integers heights representing the histogram's bar height where the width 
of each bar is 1, return the area of the largest rectangle in the histogram. 

Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10

Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
Example 2:


Input: heights = [2,4]
Output: 4
*/

/*
Algorithm
    1. Try to form rectangles by going through every bar and current bar's height will be the height of the rectangle.
    2. For a bar with height h, extend it to the left and right. Can't extend further when we encounter a bar with a smaller height than h
    3. Use a stack with a monotonically strictly increasing nature, but instead of storing values, we store indices in the stack
    4. 
*/
class Solution {
public:
    int largestRectangleArea(std::vector<int>& heights) {
        // Stack for storing the indices and height --> pair {idx, height}
        std::stack<std::pair<int, int>> increasingStack; 
        int maxArea = 0;

        for (unsigned int i=0 ; i<heights.size() ; i++) {
            int currRectangleHeight = heights[i];
            int leftIdx = i;
            
            if (!increasingStack.empty() && currRectangleHeight == increasingStack.top().second){
                continue;
            }

            while (!increasingStack.empty() && currRectangleHeight < increasingStack.top().second){
                auto [idx, height] = increasingStack.top();
                int currArea = (i - idx)*height;
                if (currArea > maxArea) maxArea = currArea;
                increasingStack.pop();
                leftIdx = idx;
            }
            

            increasingStack.push({leftIdx, currRectangleHeight});
            auto [idx, height] = increasingStack.top();
            // std::cout << idx << " " << height << " " << maxArea << '\n';
        }

        // std::cout << "\nDONE" << std::endl;
        while (!increasingStack.empty()){
            auto [idx, height] = increasingStack.top();
            // std::cout << idx << " " << height << '\n';
            int currArea = (heights.size() - idx)*height;
            if (currArea > maxArea) maxArea = currArea;
            increasingStack.pop();
        }
        return maxArea;
    }
};