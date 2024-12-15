#include <vector>
#include <unordered_map>

/*
Given an integer array nums, return true if any value appears more than once in the array, otherwise return false.

Example 1:
Input: nums = [1, 2, 3, 3]
Output: true
*/

class Solution {
public:
    bool hasDuplicate(std::vector<int>& nums) {
        
        std::unordered_map<int, int> element_map;

        for(int i = 0 ; i<nums.size() ; i++){
            if (element_map.find(nums[i]) == element_map.end()){
                element_map[nums[i]]++ ;
            }
            else return true;
        }
        return false;
    }
};

int main(){
    return 0;
}