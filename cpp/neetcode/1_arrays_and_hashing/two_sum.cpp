#include <vector>
#include <unordered_map>

/*
Given an array of integers nums and an integer target, return the indices i and j such that nums[i] + nums[j] == target and i != j.

You may assume that every input has exactly one pair of indices i and j that satisfy the condition.

Return the answer with the smaller index first.

Example 1:
Input: 
nums = [3,4,5,6], target = 7
Output: [0,1]

Explanation: nums[0] + nums[1] == 7, so we return [0, 1].
*/

/*
Algorithm:
    1. Iterate over nums
    2. For each element, find target-element in the map
    3. If found, return answer
    4. If not found add the current element and its index to the map
*/

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        std::unordered_map<int, int> map;
        std::vector<int> ans;

        for (int i = 0 ; i<nums.size() ; i++){
            auto map_it = map.find(target - nums[i]);
            if (map_it == map.end()){
                map[nums[i]] = i;
            }
            
            else{
                ans.push_back(map_it->second);
                ans.push_back(i);
                return ans;
            }
        }
    }
};
