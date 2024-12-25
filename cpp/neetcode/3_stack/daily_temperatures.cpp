#include <vector>
#include <stack>
/*
Given an array of integers temperatures represents the daily temperatures, 
return an array answer such that answer[i] is the number of days you have 
to wait after the ith day to get a warmer temperature. If there is no future 
day for which this is possible, keep answer[i] == 0 instead.

Example 1:
Input: temperatures = [73,74,75,71,69,72,76,73]
Output: [1,1,4,2,1,1,0,0]

Example 2:
Input: temperatures = [30,40,50,60]
Output: [1,1,1,0]

Example 3:
Input: temperatures = [30,60,90]
Output: [1,1,0]
*/
class Solution {
public:
    std::vector<int> dailyTemperatures(std::vector<int>& temperatures) {
        std::stack<std::pair<int, int>> decreasingStack;
        std::vector<int> answer(temperatures.size(), 0);

        for (int i=0 ; i<temperatures.size() ; i++) {
            while(!decreasingStack.empty() && temperatures[i] > decreasingStack.top().first) {
                auto pair = decreasingStack.top(); // {value index}
                answer[pair.second] =  i - pair.second;
                decreasingStack.pop(); 
            }
            decreasingStack.push({temperatures[i], i});
        }
        
        return answer;
    }
};