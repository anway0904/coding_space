#include <stack>
#include <vector>
#include <algorithm>

class Solution {
public:
    int carFleet(int target, std::vector<int>& position, std::vector<int>& speed) {
        std::stack<int> timeToTarget;
        std::vector<std::pair<int, int>> sortedPosSpeed;
        for (int i=0 ; i<position.size() ; i++) {
            sortedPosSpeed.push_back({position[i], speed[i]});
        }

        std::sort(sortedPosSpeed.rbegin(), sortedPosSpeed.rend());
        
        for (int i=0 ; i<sortedPosSpeed.size() ; i++) {
            int time = (target - sortedPosSpeed[i].first)/sortedPosSpeed[i].second;
            if(!timeToTarget.empty() && time<=timeToTarget.top()) {
                continue;
            }
            timeToTarget.push(time);
        }

        return timeToTarget.size();
    }
};