/*
    https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/submissions/
    TC: O(N)
    SC: O(N)
*/
class Solution {
public:
    int minSwapIter(vector<int>& A, vector<int>& B) {
        // swapped(i): min swaps keeping increasing order in [0:N-1] by swapping ith index
        vector<int> swapped(A.size(), INT_MAX);   
        // not_swapped(i): min swaps keeping increasing order in [0:N-1] by not swapping ith index
        vector<int> not_swapped(A.size(), INT_MAX);
        
        swapped[0] = 1;
        not_swapped[0] = 0;
        // for each index, we find the min swaps if ith index is swapped and not swapped
        for(int i = 1; i < A.size(); i++) {
            // since it is given that increasing order can be made and the only interchange
            // is between the th index of A and B, so there are only two possible cases:
            // 1. Ai-1 < Ai and Bi-1 < Bi
            // 2. Ai-1 > Ai || Bi-1 > Bi and Ai-1 < Bi, Bi-1 < Ai
            // Other combinations are not possible since is it sure to have the elements swapped to 
            // have increasing order
            
            if(A[i-1] < A[i] && B[i-1] < B[i])  {
                // since it is already increasing
                // either 'i' and 'i-1' A and B are swapped ot both are not swapped
                swapped[i] = swapped[i - 1] + 1;
                not_swapped[i] = not_swapped[i-1];
            }
            if(A[i-1] < B[i] && B[i-1] < A[i]) {
                // since it is not in increasing order, either of 'i' or 'i-1' of 
                // A dn B needs to be swapped
                swapped[i] = min(not_swapped[i-1] + 1, swapped[i]);
                not_swapped[i] = min(swapped[i-1], not_swapped[i]);
            }
        }
        
        return min(swapped[A.size() - 1], not_swapped[A.size() - 1]);
    }
    
    
    int minSwap(vector<int>& A, vector<int>& B) {
        return minSwapIter(A, B);
    }
};
