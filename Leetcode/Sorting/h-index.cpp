/*
    https://leetcode.com/problems/h-index/submissions/
    
    We are looking for a max value 'h' for which there are atleast 'h' papers with 
    citations >= h. In other words we need to find a fast way to determine how many 
    papers have citations more than 'x'. An easy way to do this is using sorting, sorting
    the citations in non-decreasing order. 
    One careful observation is that the h-index is bounded by the number of papers that can
    support a particular h-index value. We start from the biggest paper, that makes the h-index = 1,
    then the next smaller paper with atleast support h-index = 2, since the next paper has atleast 
    citations >= current paper and so on...
    
    TC: O(nlogn)
    SC: OO(n), sorting
*/
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int h_index = 0;
        
        // We iteratively increase the h-index based on the number of
        // papers that can support it, we stop the iteration once we find a
        // paper that can no longer support the current h-index, since all the
        // papers on its left will also support
        for(int i = (int)citations.size() - 1; 
            i >= 0 && h_index < citations[i]; i--) {
            h_index = max(h_index, (int)citations.size() - i);
        }
        return h_index;
    }
};
