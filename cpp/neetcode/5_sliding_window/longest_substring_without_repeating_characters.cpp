#include <string>
#include <unordered_set>
/*
Given a string s, find the length of the longest substring without repeating characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        std::unordered_set<char> hashSet;
        int windowL = 0;
        int longestLen = 0;

        for (int windowR=0 ; windowR<s.length() ; windowR++){
            while (hashSet.find(s[windowR]) != hashSet.end()){
                hashSet.erase(s[windowL]);
                windowL++;
            }
            hashSet.insert(s[windowR]);
            longestLen = std::max(windowR-windowL+1, longestLen);
        }
        return longestLen;
    }
};