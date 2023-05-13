/*
    https://leetcode.com/problems/delete-columns-to-make-sorted/description/
*/
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int cols = 0;
        int n = strs[0].size();

        for(int pos = 0; pos < n; pos++) {
            char last;
            for(int i = 0; i < strs.size(); i++) {
                if (i > 0 && strs[i][pos] < last) {
                    ++cols;
                    break;
                }
                
                last = strs[i][pos];
            }
        }
        return cols;
    }
};
