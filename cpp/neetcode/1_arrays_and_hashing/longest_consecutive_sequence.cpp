#include<vector>
#include<unordered_set>
/*
Given an array of integers nums, return the length of the longest consecutive sequence of elements that can be formed.
A consecutive sequence is a sequence of elements in which each element is exactly 1 greater than the previous element.
The elements do not have to be consecutive in the original array.

You must write an algorithm that runs in O(n) time.

Example 1:
Input: nums = [2,20,4,10,3,4,5]
Output: 4

Explanation: The longest consecutive sequence is [2, 3, 4, 5].
*/

/*
Algorithm:
    1. Add all the elements of the array to a set
    2. Define a pair {0, 0}, that denotes the start and end of the max range
    3. Iterate over nums:
        1. If the current element is in between the range above, do nothing
        2. Else, decrement the current element as long as the decremented value is in the set.
        3. Increment the current element as long as the incremented value is in the set.
        4. If this range is greater than the current range (from pair), update the pair
*/
class Solution {
public:
    int longestConsecutive(std::vector<int>& nums) {
        std::unordered_set<int> numsSet;
        std::pair<int, int> currRange(0, 0);

        if (nums.size() == 0) return 0;

        for (const auto & n : nums){
            numsSet.insert(n);
        }

        int currElement, currStart, currEnd;

        for (const auto & s: nums){
            if (s >= currRange.first && s <= currRange.second) continue;
            
            currElement = s;
            while (numsSet.find(currElement-1) != numsSet.end()){
                currElement --;
            }
            currStart = currElement;

            currElement = s;
            while (numsSet.find(currElement+1) != numsSet.end()){
                currElement ++;
            }
            currEnd = currElement;
            
            if (std::abs(currRange.second - currRange.first) < \
                std::abs(currEnd - currStart)){
                currRange.first = currStart;
                currRange.second = currEnd;
            }
        }
        return (currRange.second - currRange.first + 1);
    }
};
