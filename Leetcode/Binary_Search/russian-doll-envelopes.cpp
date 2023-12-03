/*
    https://leetcode.com/problems/russian-doll-envelopes/
    
    TC: O(nlogn + n) ~ O(nlogn)
    SC: O(n)
    
    This is very similar to LIS but unlike LIS problem, here we have 2 dimensions.
    So we need to consider both of them.
    
    We can sort the envelopes by dimension 'width' in increasing order and for same
    width ties, decrease the 2nd dimension in decreasing order.
    
    Once we have it sorted by width, we have to deal with the dim height, so if can do
    LIS on heights alone.
    This works because the widths are already sorted when traversed from left to right
    and it is ensured they are growing except we need to handle the case of same values.
    
    When there are same values and if the height is not sorted in decreasing order, then 
    LIS will also include the multiple heights for the same width, so we sort them in decreasing order.
    This ensures that when we do LIS binary search on the heights, we are left with only the smallest height
    after going from largest to smallest height for the same width.
    
    One other way of handling this is to keep only the width with the smallest height in case of same
    width values. Then apply the normal LIS binary search on the values.
*/
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if(envelopes.empty())
            return 0;
        
        // sort by increasing 'w', for tie sort by decreasing 'h'
        auto comp = [&](const vector<int>& a, const vector<int>& b) {
            if(a[0] == b[0])
                return a[1] > b[1];
            return a[0] < b[0];
        };
        
        sort(envelopes.begin(), envelopes.end(), comp);
        
        vector<int> lis;
        // Apply LIS on the height dimension
        for(auto envelope: envelopes) {
            int h = envelope[1];
            auto it = lower_bound(lis.begin(), lis.end(), h);
            
            if(it == lis.end())
                lis.push_back(h);
            else
                *it = h;
        }
        
        return lis.size();
    }
};
