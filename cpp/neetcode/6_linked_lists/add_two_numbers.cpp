/*
You are given two non-empty linked lists, l1 and l2, where each represents a non-negative integer.
The digits are stored in reverse order, e.g. the number 123 is represented as 3 -> 2 -> 1 -> in the linked list.
Each of the nodes contains a single digit. You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Return the sum of the two numbers as a linked list.

Example 1:
Input: l1 = [1,2,3], l2 = [4,5,6]
Output: [5,7,9]
Explanation: 321 + 654 = 975.

Example 2:
Input: l1 = [9], l2 = [9]
Output: [8,1]

*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = new ListNode();
        ListNode* currNode = result;
        int carry = 0;

        while (l1 != nullptr || l2 != nullptr || carry) {
            int val1 = l1 ? l1->val:0;
            int val2 = l2 ? l2->val:0;

            currNode->next = new ListNode((val1 + val2 + carry) % 10);
            currNode = currNode->next;
            
            carry = (val1 + val2 + carry)/10;

            if (l1 != nullptr) l1 = l1->next;
            if (l2 != nullptr) l2 = l2->next;
        }
        return result->next;
    }
};