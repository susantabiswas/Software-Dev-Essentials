/*
    https://leetcode.com/problems/numbers-with-same-consecutive-differences/
    
    BFS:
    
    We can imagine each digit as a level. The MSD (Most Significant Digit) is the 1st level
    and the nth digit is the nth level. 
    At each level we add the next digit that satisfies the abs diff criteria.
    
    Backtracking:
    We add a new digit in each call of recursion. The inner digits can have atmost 2
    candidates since diff can't be achieved with more than 2 digits. Eg k = 4, we can have
    8 or 0 as the next digit.
*/
class Solution {
public:
	// SOLUTION 2: BACKTRACKING
    // TC: O(2^N)
    // SC: O(N)(recursion stack) + O(2^N) (solutions)
    // For TC same explanation as that of BFS, but for SC, here we just
    // go deep once so at worst we go till O(N) unlike BFS where we traverse level by level
    void backtrackingSol(int n, int k, string num, vector<int>& nums) {
        // k digits achieved
        if(n == 0) {
            nums.emplace_back(stoi(num));
            return;
        }
        
        int digit = num.empty() ? 0 : num.back() - '0';
        // Put the current digit
        for(int d = 0; d <= 9; d++) {
            // 0 can't be put at MSD
            if(d == 0 && num.empty())
                continue;
            if(num.empty())
                backtrackingSol(n-1, k, num + (char)(d + '0'), nums);
            else if(abs(digit - d) == k)
                backtrackingSol(n-1, k, num + (char)(d + '0'), nums);
        }
    }
    
	// SOLUTION 1: BFS
    // TC: O(2^N)
    // Initially there are 9 digits for MSD, then we can only have atmost
    // 2 digits as candidates since only max 2 digits can make the same abs diff 
    // with the last digit.
    // 9.2^N-1 + 2^N-1 + 2^N-2.....+ 1
    // ~O(2^N)
    // SC: Since we save the levels in BFS, so worst case we can have 2^i nodes 
    // in a level ~ O(2^N)
    vector<int> bfsSol(int n, int k) {
        queue<string> q;
        vector<int> nums;
        // Add the initial 1st digit
        for(int i = 1; i <= 9; i++) 
            q.emplace(to_string(i));
        
        
        while(!q.empty()) {
            auto num = q.front();
            q.pop();
            
            // k digits completed
            if(num.size() == n)
                nums.emplace_back(stoi(num));
            else {
                // add the next digit if the no. of digits < k
                int digit = num.back() - '0';
                // Add only the digit that has an abs diff of k 
                // with the last digit
                for(int d = 0; d <= 9; d++)
                    if(abs(digit - d) == k) {
                        string next_num = num + (char)(d + '0');
                        q.emplace(next_num);
                    }
            }
        }
        
        return nums;
    }
    
    vector<int> numsSameConsecDiff(int n, int k) {
        // return bfsSol(n, k);
        vector<int> nums;
        backtrackingSol(n, k, "", nums);
        return nums;
    }
};
