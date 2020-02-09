/*
    https://leetcode.com/problems/rank-transform-of-an-array/
    TC: O(nlogn), SC: O(nlogn)
    
    Sort the array with the index info, then traverse the sorted array
    and put the rank value at its correct position.
*/
class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> rank(arr.size());
        // (element, index)
        vector<pair<int, int>> arr_idx;
        
        // array to sort with index info
        for(int i = 0; i < arr.size(); i++) 
            arr_idx.emplace_back(make_pair(arr[i], i));
        // sort the array in stable manner(same elements come in their original relative order)
        sort(arr_idx.begin(), arr_idx.end(), 
            [](pair<int, int>& a, pair<int, int>& b)->bool{
                return a.first < b.first;
            });
        
        int r = 1;
        for(int i = 0; i < arr_idx.size(); i++) {
            rank[arr_idx[i].second] = r;
            // if the next element is same, then its rank stays the same
            if(i+1 < arr_idx.size())
                arr_idx[i].first == arr_idx[i+1].first ? r : ++r;
        }
        
        return rank;
    }
};
