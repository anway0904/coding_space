#include <unordered_map>
#include <vector>
#include <queue>

/*
Given an integer array nums and an integer k, return the k most frequent elements within the array.
The test cases are generated such that the answer is always unique.
You may return the output in any order.

Example 1:
Input: nums = [1,2,2,3,3,3], k = 2
Output: [2,3]

Algorithm:
1. Traverse through the array and store the count of each element in the map.
2. Push the counts into a heap, keeping the heap size to k. 
3. Use a min-heap to ensure that the smallest frequency in the top k is at the top of the heap,
   making it easier to discard less frequent elements.
4. Extract elements from the heap and return them.
*/
class Solution {
public:
    std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> mp;
        std::unordered_map<int, int>::iterator it;
        std::vector<int> resultVec;

        if (k == nums.size()) return nums;

        for(auto n : nums){
            mp[n] ++;
        }

        std::priority_queue<std::pair<int, int>, 
                            std::vector<std::pair<int, int>>> pq;

        for (const auto& pair : mp) {
            pq.push({pair.second, pair.first});
        }

        int s = pq.size();
        while (pq.size() != (s-k)) {
            resultVec.push_back(pq.top().second);
            pq.pop();
        }

        return resultVec;
    }
};