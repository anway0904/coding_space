#include <string>
#include <stack>

/*
You are given a string s consisting of the following characters: '(', ')', '{', '}', '[' and ']'.

The input string s is valid if and only if:

Every open bracket is closed by the same type of close bracket.
Open brackets are closed in the correct order.
Every close bracket has a corresponding open bracket of the same type.
Return true if s is a valid string, and false otherwise.

Example 1:

Input: s = "[]"

Output: true
Example 2:

Input: s = "([{}])"

Output: true
Example 3:

Input: s = "[(])"

Output: false
Explanation: The brackets are not closed in the correct order.
*/

class Solution {
public:
    bool isValid(std::string s) {
        std::stack<char> brackets;
    
        int n = s.length();
        if (n%2 != 0) return false;
        if (s[0] == ')' || s[0] == ']' || s[0] == '}') return false;
        if (s[n-1] == '(' || s[n-1] == '[' || s[n-1] == '{') return false;

        for (const auto &b : s){
            if (b == '(' || b == '[' || b == '{'){
                brackets.push(b);
            }

            else{
                if (brackets.size() == 0) return false;
                char top_bracket = brackets.top();
                if (b == ')'){
                    if(top_bracket == '(') brackets.pop();
                    else return false;
                }

                else if (b == '}'){
                    if(top_bracket == '{') brackets.pop();
                    else return false;
                }

                else if (b == ']'){
                    if(top_bracket == '[') brackets.pop();
                    else return false;
                }
            }
        }

        if (brackets.size()) return false;
        return true;
    }
};