#include<string>
#include<iterator>
/*
Given a string s, return true if it is a palindrome, otherwise return false.

A palindrome is a string that reads the same forward and backward. It is also case-insensitive 
and ignores all non-alphanumeric characters.

Example 1:
Input: s = "Was it a car or a cat I saw?"

Output: true
Explanation: After considering only alphanumerical characters we have "wasitacaroracatisaw", which is a palindrome.
*/

/*
Algorithm:
    1. Initialize two pointers at the start and end of the numbers array
    2. Increment left pointer until alpha-numeric found
    3. Decrement right pointer until alpha-numeric found
    4. Return false if left pointer != right pointer
*/

class Solution {
public:
    bool isPalindrome(std::string s) {
        std::string::iterator sPtr = s.begin();
        std::string::iterator ePtr = s.end();

        while (sPtr < ePtr){
            while(!std::isalnum(*sPtr) && sPtr < ePtr){
                sPtr ++;
            }

            while(!std::isalnum(*ePtr) && sPtr < ePtr){
                ePtr --;
            }
            
            if (std::tolower(*sPtr) != std::tolower(*ePtr)) return false;

            sPtr++;
            ePtr--;

        }
        return true;
    }
};
