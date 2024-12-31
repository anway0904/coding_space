#include <vector>

/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
*/

class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        int ptr1 = 0, ptr2 = 0;
        int mergedPtr = 0;
        int mergedArrSize = nums1.size() + nums2.size();
        std::vector<int> mergedArray;

        // Merge the arrays
        while (ptr1 < nums1.size() && ptr2 < nums2.size()) {
            if (nums1[ptr1] <= nums2[ptr2]) {
                mergedArray.push_back(nums1[ptr1++]);
            } else {
                mergedArray.push_back(nums2[ptr2++]);
            }
        }

        // Copy remaining elements from nums1
        while (ptr1 < nums1.size()) {
            mergedArray.push_back(nums1[ptr1++]);
        }

        // Copy remaining elements from nums2
        while (ptr2 < nums2.size()) {
            mergedArray.push_back(nums2[ptr2++]);
        }

        // Find and return the median
        int n = mergedArray.size();
        if (n % 2 == 0) {
            return (mergedArray[n / 2 - 1] + mergedArray[n / 2]) / 2.0;
        } else {
            return mergedArray[n / 2];
        }
    }
};
