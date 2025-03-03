#include <vector>
#include <algorithm>
/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] 
such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.
Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
*/

/*
Algorithm
    1. Sort the array
    2. Iterate over the array
    3. Initialize two pointers, one at idx next to current element, and one at the end of the array
    4. calculate the sum of the three elements
    5. If the sum=0, append the elements to the answer
        1. Increment the left pointer until it is not equal to its current value and <right pointer
    6. If sum<0, increment left pointer, else if sum>0, increment the right pointer
*/
class Solution {
public:
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        std::vector<std::vector<int>> ans;
        std::sort(nums.begin(), nums.end());

        std::vector<int>::iterator iter1 = nums.begin();
        std::vector<int>::iterator iter2 = nums.end() - 1;

        for(int i = 0 ; i<nums.size()-2 ; i++){
            if (i>0 && nums[i] == nums[i-1]) continue;

            iter1 = nums.begin() + i + 1;
            iter2 = nums.end() - 1;

            while (iter1 < iter2){
                if (*iter1 + *iter2 + nums[i] == 0){
                    ans.push_back({nums[i], *iter1, *iter2}); iter1++;
                    while(*iter1 == *(iter1-1) && iter1<iter2) iter1++;
                }
                else if (*iter1 + *iter2 + nums[i] > 0) iter2--;
                else iter1++;
            }
        }
        return ans;
    }
};