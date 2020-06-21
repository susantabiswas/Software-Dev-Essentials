/*
    https://leetcode.com/problems/avoid-flood-in-the-city/
    
    TC: O(nlogn)
*/
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        unordered_map<int, int> lake_rain;
        set<int> dry_day;
        vector<int> result(rains.size(), -1);
        
        for(int i = 0; i < rains.size(); i++) {
            // dry day
            if(rains[i] == 0) {
                dry_day.emplace(i);
                result[i] = 1;
            }
            else {
                // check if the lake rained earlier or not
                if(lake_rain.count(rains[i])) {
                    // check if there was a dry day before
                    auto it = dry_day.lower_bound(lake_rain[rains[i]]);
                    if(it != dry_day.end()) {
                        // dry the current lake
                        result[*it] = rains[i];
                        dry_day.erase(it);
                    }
                    else
                        return vector<int>{};
                }
                
                lake_rain[rains[i]] = i;
            }
        }
        return result;
    }
};
