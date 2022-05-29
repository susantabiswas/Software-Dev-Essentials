/*
    https://leetcode.com/problems/maximum-students-taking-exam/
    
    Core idea is for the ith row, we need to decide the sitting arrangement based on the
    arrangement of previous row.
    We use bit masking for storing the seating layout for each row, since there are can be
    2^cols arrangements, we create a dp[rows+1][2^cols].
    
    Now iterate through each row and for each row, check if the layout is valid or not (seats are avail).
    Then check with each of the possible seating layouts of prev row, each time ensuring that there are 
    no diagonal seats, left and right seats in the current row. If the previous layout is compatible with
    current row layout, then update the number of students that can sit till current row.
    
    TC: O(N * 2^M * 2^M)
    SC: O(N*2^M)
*/
class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        if(seats.empty())
            return 0;
        const int N = seats.size();
        const int M = seats[0].size();
        
        // avail_seats[i] = bit encoded representation of all avail seating positions
        // 1: avail seat, 0: seat not avail
        vector<int> avail_seats(N+1);
        
        // for each row, find the avail seats
        for(int i = 1; i <= N; i++)
            for(int j = 0; j < M; j++)
                if(seats[i-1][j] == '.')
                    avail_seats[i] = avail_seats[i] | (1 << j);
        
        // dp[i][mask]: Total number of students that can sit till ith row
        // mask: sitting layout of each student in the row, 
        // eg: 1001 => students sitting at 0th and 3rd index
        // To make the code simpler, one extra row is taken, which doesnt exists
        vector<vector<int>> dp(N+1, vector<int>(1 << M, -1));
        
        // init starting row doesnt exists so it can have 0 students 
        for(int mask = 0; mask < (1 << M); mask++)
            dp[0][mask] = 0;
        
        for(int i = 1; i <= N; i++) 
            for(int mask = 0; mask < (1 << M); mask++) {
                // if current sitting layout is valid (positions have vacant seats)
                // below line checks if mask layout is a subset of avail_seats[i] (valid positions)
                if((mask & avail_seats[i]) != mask)
                    continue;
                // Also check if there are adjacent (both left and right) avail seats in curr layout
                if((mask & (mask << 1)) || (mask & (mask >> 1))) 
                    continue;
                // once we know current layout has valid sitting positions,
                // we check tha max students that can sit in this layout by comparing
                // against the positions of student in prev row
                for(int prev_mask = 0; prev_mask < (1 << M); prev_mask++) {
                    // check if prev layout is valid or not
                    if(dp[i-1][prev_mask] == -1) 
                        continue;
                    // check if any seats in prev layout is diagonally adjacent
                    // to seats in curr layout
                    if((mask & (prev_mask << 1)) || (mask & (prev_mask >> 1)))
                        continue;
                    dp[i][mask] = max(dp[i][mask],
                                      dp[i-1][prev_mask] + __builtin_popcount(mask));
                }
            }
        // pick the sitting arrangement that can sit the max students  
        return *max_element(dp[N].begin(), dp[N].end());
    }
};
