#include <iostream>
/*
Design a stack class that supports the push, pop, top, and getMin operations.

MinStack() initializes the stack object.
1. void push(int val) pushes the element val onto the stack.
2. void pop() removes the element on the top of the stack.
3. int top() gets the top element of the stack.
4. int getMin() retrieves the minimum element in the stack.
Each function should run in O(1) time.

Example 1:
Input: ["MinStack", "push", 1, "push", 2, "push", 0, "getMin", "pop", "top", "getMin"]
Output: [null,null,null,null,0,null,2,1]

Explanation:
MinStack minStack = new MinStack();
minStack.push(1);
minStack.push(2);
minStack.push(0);
minStack.getMin(); // return 0
minStack.pop();
minStack.top();    // return 2
minStack.getMin(); // return 1
*/

class MinStack {
    private:
        struct Node{
            int val;
            int min;
            Node* next;

            Node(int val, int min): val(val), min(min), next(nullptr) {} 
        };

        Node* head = nullptr;

    public:
        MinStack() {
        }
        void print(){
            Node* curr_ptr = head;
            while (curr_ptr != nullptr) {
                std::cout << curr_ptr->val << "(" << curr_ptr->min << ")" << " --> ";
                curr_ptr = curr_ptr->next; 
            }
            std::cout << "END\n" << std::endl;
        }
        void push(int val) {
            if (head == nullptr){
                head = new Node(val, val);
            } 
            else {
                Node* tmp = head;
                int min = head->min < val ? head->min : val;
                // std::cout << min << '\n';
                head = new Node(val, head->min < val ? head->min : val);
                head->next = tmp;
            }
        }
        
        void pop() {
            Node* temp = head;
            head = head->next;
            delete temp; 
        }
        
        int top() {
            return head->val;
        }
        
        int getMin() {
            return head->min;
        }
};

int main(){
    MinStack* obj = new MinStack();
    obj->push(-5);
    obj->push(1);
    obj->push(-1);
    obj->push(2);
    obj->push(3);
    obj->push(-10);
    obj->push(5);

    obj->print();
    obj->pop();
    obj->pop();

    int param_3 = obj->top();
    int param_4 = obj->getMin();
    
    std::cout << param_3 << "--" << param_4 << std::endl;

}