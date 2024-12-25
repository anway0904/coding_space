#include <string>
#include <unordered_map>
#include <iostream>
/*
Given two strings s and t, return true if the two strings are anagrams of each other, otherwise return false.

An anagram is a string that contains the exact same characters as another string, but the order of the characters can be different.

Example 1:
Input: s = "racecar", t = "carrace"
Output: true
*/

/*
Algorithm
    1. Iterate over both the strings
    2. Add the characters along with the count to a map for each string
    3. Return true if both maps are identical
*/
class Solution {
public:
    bool isAnagram(std::string s, std::string t) {
        std::unordered_map<char, int> map1, map2;

        for(int i=0 ; i<s.length() ; i++){
            map1[s[i]] ++;
            map2[t[i]] ++;
        } 
        return map1 == map2;
    }
};

int main(){
    Solution solution;
    bool ans = solution.isAnagram("racecar", "carrace");
    std::cout << ans << '\n';
}