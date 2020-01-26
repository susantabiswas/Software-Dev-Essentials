/*
    https://leetcode.com/problems/longest-consecutive-sequence/
    TC: O(N)
    SC: O(N)
    
    The idea is to create a hash table of elements that are visited. Once the hash table is 
    created, we start the traversal of hash table. Since the objective is to find consecutive 
    range of elements, so we start with an element and start expanding the search in left and right
    direction and marking them as true, each time for any successful search incrementing the counter.
    Since any eelement will be marked true once visited, so each element can be visited at most twice
    making it linear.
*/
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // hash table for marking presence of elements, this
        // is used for checking the visited elements
        unordered_map<int, bool> elements;
        // create hash entriees
        for(const int& num: nums)
            elements[num] = false;
        
        // for tracking the left and right side number bounds
        int left = 0, right = 0;
        int max_len = nums.empty() ? 0 : 1, curr_len = 0;
        // start traversing the hash table
        for(auto it = elements.begin(); it != elements.end(); it++) {
            curr_len = 0;
            // start traversing if the current has not been visited
            if(!elements[it->first]) {
                curr_len += 1;
                // start traversing left and right of current number
                left = it->first - 1, right = it->first + 1;
                // check if left and right elements exists
                auto left_it = elements.find(left);
                auto right_it = elements.find(right);
                
                // start searching in left and right direction till
                // atleast one side can be searched
                while(left_it != elements.end() ||
                     right_it != elements.end()) {
                    // if left side element was found, search in left again for the next 
                    if(left_it != elements.end()) {
                        // mark as visited
                        elements[left] = true;
                        --left;
                        curr_len += 1;
                        left_it = elements.find(left);
                    }
                    // if right side element was found, search in right again for the next
                    if(right_it != elements.end()) {
                        elements[right] = true; 
                        ++right;
                        curr_len += 1;
                        right_it = elements.find(right);
                    }
                }
                // update max length
                max_len = max(max_len, curr_len);
            }
        }
        return max_len;
    }
};
