/*
    https://leetcode.com/problems/product-of-two-run-length-encoded-arrays/
    
    Idea is to use two pointers, one each for encoded1 and encoded2.
    Now we iterate through the encodings and find the product, the frequency of both
    encodings might be different. So move the iterator accordingly. 
    Also after inserting a RLE, the next product might be the same as the previous product,
    in that case we need to append the current freq with that result.
    eg [2,1][3,1]
        [3,1][2,1] 
        =>[6,1][6,1] Not desirable
        =>[6,2] Desirable
*/
class Solution {
public:
    // SOLUTION: Two Pointers
    // TC: O(N)
    // SC: O(1)
    vector<vector<int>> sol(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        vector<vector<int>> prod;
        
        int i = 0, j = 0;
        while(i < encoded1.size() && j < encoded2.size()) {
            // check if the current encoding prod is the same as last prod or not
            // If yes, then just append the encoding length
            if(!prod.empty() && prod.back()[0] == encoded1[i][0] * encoded2[j][0])
                prod.back()[1] += min(encoded1[i][1], encoded2[j][1]);
            else
                prod.emplace_back(vector<int>{encoded1[i][0] * encoded2[j][0],
                                          min(encoded1[i][1], encoded2[j][1])});
            
            // Out of the two encodings, if one has lower frequency, then increment the iterator for
            // that
            if(encoded1[i][1] < encoded2[j][1]) {
                // remove the freq utilized for the current product operation
                encoded2[j][1] -= encoded1[i][1];
                ++i;
            }
            else if(encoded1[i][1] > encoded2[j][1]) {
                encoded1[i][1] -= encoded2[j][1];
                ++j;
            }
            else
                ++i, ++j;
        }
        return prod;
    }
    
    vector<vector<int>> findRLEArray(vector<vector<int>>& encoded1, vector<vector<int>>& encoded2) {
        return sol(encoded1, encoded2);
    }
};
