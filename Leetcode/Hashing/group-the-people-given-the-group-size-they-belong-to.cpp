/*
    https://leetcode.com/problems/group-the-people-given-the-group-size-they-belong-to/submissions/
    
    Since we know that there exists a valid sol, so we can use cmb of greedy and hashing. 
    Idea is to first find out to which group size each of the elements belong. After that
    for each of the group sizes, we create groups of elements greedily picking the first
    few elements of req. group size.
    
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<vector<int>> result;
        // For each group size, we find all the elements that belongs to the same size
        unordered_map<int, vector<int>> groups;
        
        for(int i = 0; i < groupSizes.size(); i++) {
            groups[groupSizes[i]].emplace_back(i);
        }
        // Since it is known that a sol always exists,
        // for each of the group sizes, we form groups of that
        // size with the elements found in last step
        for(auto it = groups.begin(); it != groups.end(); it++) {
            int group_size = it->first;
            int num_groups = it->second.size() / group_size;
            
            // We create required number of groups of current size with the elements
            // as members
            for(int i = 0; i < num_groups; i++) {
                vector<int> curr_group((it->second).begin() + i,
                                       (it->second).begin() + i + group_size);
                result.emplace_back(curr_group);
            } 
        }
        return result;
    }
};
