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

/*
Algorithm
    1. Use a stack to maintain indices in a monotonically decreasing order
    2. Iterate over the temperatures and push to stack if current temperature is less than that of top of stack
    3. Otherwise, pop elements from the stack until the top element of the stack is no longer less than the current element
    4. For each popped element, compute the difference between the indices and store it in the position corresponding to the popped element.
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