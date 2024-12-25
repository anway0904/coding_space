#include <vector>
#include <iostream>
/*
Given an integer array nums, return an array output where output[i] is the product of all the elements of nums except nums[i].
Each product is guaranteed to fit in a 32-bit integer.

Follow-up: Could you solve it in O(n) time without using the division operation?

Example 1:
Input: nums = [1,2,4,6]
Output: [48,24,12,8]

Example 2:
Input: nums = [-1,0,1,2,3]
Output: [0,-6,0,0,0]

Constraints:
2 <= nums.length <= 1000
-20 <= nums[i] <= 20
*/

/*
Algorithm:
    1. Create two vectors, leftProduct and rightProduct
    2. Compute and store the product of the elements to the left of the current element
    3. Compute and store the product of the elements to the right of the current element
    4. Compute the product of the left and right product vectors
*/
class Solution {
public:
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        std::vector<int> leftProduct, rightProduct;
        int sizeNums = nums.size();
        
        int currProductL = nums[0];
        int currProductR = nums[sizeNums-1];
        leftProduct.push_back(1);
        rightProduct.push_back(1);

        for (int i=1 ; i<sizeNums ; i++){
            leftProduct.push_back(currProductL);
            rightProduct.push_back(currProductR);
            currProductL *= nums[i];
            currProductR *= nums[sizeNums-i-1];
        }

        // for (auto l:leftProduct){
        //     std::cout << l << " ";
        // }
        // std::cout << '\n';

        // for (auto r:rightProduct){
        //     std::cout << r << " ";
        // } 
        // std::cout << '\n';

        for (int i=0 ; i<sizeNums ; i++){
            leftProduct[i] *= rightProduct[sizeNums-i-1];
        }

        return leftProduct;
    }
};

int main(){
    Solution s;
    std::vector<int> n = {5,2,4,6};
    s.productExceptSelf(n);
}