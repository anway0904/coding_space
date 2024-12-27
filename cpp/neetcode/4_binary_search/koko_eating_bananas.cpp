#include <vector>
#include <algorithm>
#include <cmath>

/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. 
The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of 
bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all 
of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23
*/
class Solution {
public:
    long long getEatingHours(int speed, std::vector<int>& piles){
        long long hours = 0;
        for (const auto &pile : piles) {
            hours += std::ceil(double(pile)/speed);
        }
        return hours;
    }

    int minEatingSpeed(std::vector<int>& piles, int h) {

        const int maxSpeed = *std::max_element(piles.begin(), piles.end()); 
        const int numPiles = piles.size();
        int minSpeed = maxSpeed;

        // Return the max speed if hours = piles (need to eat one pile per hour)
        if (h == numPiles) return minSpeed;

        // Binary search from 1-maxSpeed
        int leftPtr = 1;
        int rightPtr = maxSpeed;

        while (leftPtr <= rightPtr){
            int currSpeed = (leftPtr + rightPtr)/2;

            if (getEatingHours(currSpeed, piles) <= h){
                rightPtr = currSpeed - 1;
                minSpeed = currSpeed;
            }
            else {
                leftPtr = currSpeed + 1;
            }
        }
        
        return minSpeed;
    }
};