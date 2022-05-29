/*
    https://leetcode.com/problems/partition-labels/submissions/
    
    Sol 1
    1. We create the intervals of chars. TC: O(N), SC: (M), M: unique chars
    2. Merge the overlapping intervals. TC: O(N), SC: O(M)
    
    TC: O(N)
    SC: O(M)
    
    Sol 3:
    Find the end position of each char and create a reverse hash table <end pos, char>.
    Now we maintain a set for elements of current window. Start iterating through the elements,
    if the ith position is end pos of any of the set elements, remove it. Check if the set has become
    empty or not, if it has, then that means a parition is found.
    TC: O(N)
    SC: O(26)
*/
class Solution {
    struct Interval {
        int start = -1, end = -1;
    };
public:
    vector<int> mergeIntervals(vector<Interval>& intervals) {
        // sort the intervals acc. to the start position
        sort(intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b)->bool{
            return a.start <= b.start;
        });
        
        // Merge
        vector<Interval> disjoint_intervals;
        Interval curr = intervals[0];
        
        for(int i = 1; i < intervals.size(); i++) {
            if(intervals[i].start > curr.end) {
                disjoint_intervals.emplace_back(curr);
                curr = intervals[i];
            }    
            else 
                curr.end = max(curr.end, intervals[i].end);
        }
        // add the last interval
        disjoint_intervals.emplace_back(curr);
        
        // Compute the interval length
        vector<int> interval_len;
        for(auto &interval: disjoint_intervals)
            interval_len.emplace_back(interval.end - interval.start + 1);
        return interval_len;
    }
    
    // Solution 1
    vector<int> solution1(string& S) {
        if(S.empty())
            return vector<int>{};
        
        unordered_map<char, Interval> char_intervals;
        // We creata an Interval for each of the chars, with their start and end
        // pos. in the string
        for(int i = 0; i < S.size(); i++) {
            auto it = char_intervals.find(S[i]);
            // Initialize the interval with start and end pts
            if(it == char_intervals.end()) {
                char_intervals.emplace(S[i], Interval{i,i});
            }
            // update last seen index
            else
                char_intervals[S[i]].end = i;
        }
        
        // create an array of intervals and merge the overlapping intervals 
        vector<Interval> intervals;
        for(auto it = char_intervals.begin(); it != char_intervals.end(); it++)
            intervals.emplace_back(it->second);
        
        // Merge the overlapping intervals and return the length of each disjoint interval
        vector<int> result = mergeIntervals(intervals);
        return result;
    }
    
    // Solution 2
    // TC: O(N)
    // SC: O(26) ~ O(1)
    vector<int> solution2(string& S) {
        // Find the index of last occurrence of each char
        vector<int> char_idx(256, -1);
        for(int i = 0; i < S.size(); i++)
            char_idx[S[i] - 'a'] = i;
        
        vector<int> result;
        // We can create a partition iff all the chars in the partition
        // dont exist after that. So we keep track of the last index out of
        // all the chars in current partition
        int start = 0, end = 0;
        for(int i = 0; i < S.size(); i++) {
            end = max(end, char_idx[S[i] - 'a']);
            // When none of the chars appear after the current index
            if(end == i) {
                result.emplace_back(end - start + 1);
                start = i + 1;
                end = i + 1;
            }
        }
        
        return result;
    }
    
    // Solution 3
    vector<int> solution3(string s) {
        // <char, end pos>
        unordered_map<char, int> pos;
        unordered_map<int, char> end_pos;
        
        for(int i = 0; i < s.size(); i++) {
            if(!pos.count(s[i]))
                pos[s[i]] = i;
            pos[s[i]] = i;
        }
        
        // now put the positions in this way
        for(auto [ch, end]: pos) {
            end_pos[end] =  ch;
        }
        
        vector<int> parts;
        // set of all elements in current partition
        unordered_set<char> elements;
        
        int partition_start = 0;
        for(int i = 0; i < s.size(); i++) {
            // add the current char
            elements.emplace(s[i]);
            // check if any element's last position is 'i'
            if(end_pos.count(i)) {
                // remove the element
                elements.erase(end_pos[i]);
            }
            // check if there is any element in current partition
            if(elements.empty()) {
                // partition can be created
                parts.emplace_back(i - partition_start + 1);
                partition_start = i + 1;
            }
        }
        return parts;
    }
    
    vector<int> partitionLabels(string S) {
        // return solution1(S);
        // return solution3(S);
        return solution2(S);
    }
};
