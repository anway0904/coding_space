#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <functional>
#include <iostream>
/*
You are given an array of strings tokens that represents a valid arithmetic expression in Reverse Polish Notation.

Return the integer that represents the evaluation of the expression.

The operands may be integers or the results of other operations.
The operators include '+', '-', '*', and '/'.
Assume that division between integers always truncates toward zero.

Example 1:
Input: tokens = ["1","2","+","3","*","4","-"]
Output: 5

Explanation: ((1 + 2) * 3) - 4 = 5
*/

class Solution {
public:
    int evalRPN(std::vector<std::string>& tokens) {
        std::stack<int> polishStack;
        std::unordered_map<std::string, std::function<int(int, int)>> op {
            {"+", [](int a, int b){return a+b;}},
            {"-", [](int a, int b){return a-b;}},
            {"*", [](int a, int b){return a*b;}},
            {"/", [](int a, int b){return a/b;}},
        };

        for (const auto &token : tokens){
            if (token != "+"  && token != "-" && token != "*" && token != "/") { 
                std::cout << token << '\n'; 
                polishStack.push(std::stoi(token));
            }

            else {
                int num2 = polishStack.top();
                polishStack.pop();
                int num1 = polishStack.top();
                polishStack.pop();
                polishStack.push(op[token](num1, num2));
            }
        }

        return polishStack.top();
    }
};