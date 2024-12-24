#include <string>
#include <vector>

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

Example 1:
Input: n = 3
Output: ["((()))","(()())","(())()","()(())","()()()"]

Example 2:
Input: n = 1
Output: ["()"]
*/

class Solution {
public:
    void addBracket(int openCount, int closeCount, 
                    int n, std::string str, std::vector<std::string> &output){
        if (openCount == closeCount && openCount+closeCount == 2*n){
            output.push_back(str);
            return;
        }

        if (openCount < n) {
            addBracket(openCount+1, closeCount, n, str + "(", output);
        }

        if (openCount > closeCount) {
            addBracket(openCount, closeCount+1, n, str + ")", output);
        }
    }
    std::vector<std::string> generateParenthesis(int n) {
        std::vector<std::string> output;

        if (n == 0) return {""};
        if (n == 1) return {"()"};

        addBracket(0, 0, n, "", output);

        return output;
    }
};