/*
    https://leetcode.com/problems/race-car/
    
    Core idea is we can move forward with A and backward by reversing once and then accelerating again.
    Now moving forward covers all the odd positions and moving backward covers the even positions.
    So we can safely ignore moving towards pos < 0, since above actions can reach all the positions.
    
    Few cases:
    1. We directly reach T by As
    2. We move past T and then move backwards to reach T
    3. Before reaching T, we move backwards and then forward
    
    Refer for figure: https://leetcode.com/problems/race-car/discuss/227415/Figures-to-make-the-DP-solution-more-straightforward 
    Looking at the above cases, we only move in [0, 2T] range.
    
    
    SOLUTION 1: BFS
    SOLUTION 2: DP
    
    Here we simulate the above cases and pick the min possibility for each i in [1:T]
    
    Case 1
    0...................(j-p)............j.............i
                            |<---2^q-1---|
    |-----------------2^m - 1 ---------->|
    i = m + 1(R) + q + 1(R) + dp(i - j)
    
    Case 2
    0..................................................i = j
    |-----------------2^m - 1 ------------------------>|
    
    Case 3
    0.....................................i.............j
    |-----------------2^m - 1 ------------------------->|
                                           |<-dp(j-i)---|
    
    p = 2^q - 1
*/
class Solution {
public:
    
    // BFS with optimization
    // TC: O(T * log(T)), T = Target position from 0
    // SC: O(T * log(T))
    /* In the best case scenario where only A can get us to T, it takes 2^m = T
        m = no. of instructions
        2^m = T
        m = log2(T)
        
        Now we might take reverse also and can go backwards.
        Overall we can go from [0, 2T] length due to the code constraints. Also we can reach each position with different speeds.
        If we are at pos=0, speed=1 and we take pos j 
        We can reach j with at most 2^j speeds i.e log(j), the upper bound for this log(T)
        So for each position * diff speeds
        O(T * log(T))
    */
    // Naive BFS without any optimization
    // TC: O(2^h), h = height of binary tree = log(n), n = no. of nodes
    //              For each state, we have 2 options: A and R. This creates a binary tree
    //              With optimizations like below, we trim some of the branches.
    // SC: O(h)
    int bfsSol(int target) {
        // <position, speed>
        queue<tuple<long long, long long> > q;
        unordered_set<string> visited;
        vector<char> instructions = {'A', 'R'};
        
        q.push({0, 1});
        visited.emplace(to_string(0) + "," + to_string(1));
        int level = 0, level_nodes = q.size();
        
        while(!q.empty()) {
            auto [pos, speed] = q.front();
            q.pop();
            
            if(pos == target) 
                break;
            
            --level_nodes;
            
            for(auto instruction: instructions) {
                long long position = pos, new_speed = speed;
                
                if(instruction == 'A') {
                    position += speed;
                    new_speed *= 2;
                }   
                else 
                    new_speed = new_speed > 0 ? -1 : 1;
                // Since we are looking for +ve target
                // We move in 0, 2, 4, 8, ...k, 2k manner
                // We can reach the target via two ways:
                // 1. Accelarate + Reverse until pos < target
                // 2. Go past the target and then comeback via reversing
                if(position < 0 || position > 2 * target)
                    continue;
                string state = to_string(position) + "," + to_string(new_speed);
                if(!visited.count(state)) {
                    q.push({position, new_speed});
                    visited.emplace(state);
                }
            }
            
            // end of level
            if(level_nodes == 0 && !q.empty()) {
                ++level;
                level_nodes = q.size();
            }
        }
        return level;
    }
    
    // TC: O(T * (log(T)^2)), Destination value can be [1..T] and for that max inner loops will run log(T)^2 
    // SC: O(T)
    int minInstMem(int destination, vector<int>& dp) {
        if(dp[destination] == -1) {
            dp[destination] = INT_MAX;
            // For the current dst, we simulate the scenarios and pick
            // the one that gives the best result for the current target position

            // No. of instructions to reach stop 1 and stop where the 1st reverse instruction happens
            // Case 1
            int m = 1, stop1 = 1;
            // each time we move by 2^(inst_till_stop1 + 1)
            for(; stop1 < destination; stop1 = (1 << ++m) - 1) {
                // Now that we have taken a reverse, start moving backwards and cover
                // distance rev_dist to reach stop2.
                // q = no. of instructions to reach stop 1 from stop 2
                int rev_dist = 0, q = 0;
                for(; rev_dist < stop1; rev_dist = (1 << ++q) - 1)
                    dp[destination] = min(dp[destination], m + 1 + q + 1 + minInstMem(destination - (stop1 - rev_dist), dp));
            }

            // case 2
            if(stop1 == destination)
                dp[destination] = min(dp[destination], m);
            // case 3
            if(stop1 > destination)
                dp[destination] = min(dp[destination], m + 1 + minInstMem(stop1 - destination, dp));
        }
        return dp[destination];
    }
    //////////////// SOLUTION 2: DP Memoization
    int dpSolMem(int target) {
        // dp[i] = min steps to reach ith position from 0th 
        //          position and starting speed is 1
        vector<int> dp(target + 1, -1);
        return minInstMem(target, dp);
    }
    
    /////////////////// SOLUTION 3: DP Tabular
    // TC: O(T * (log(T)^2)), Outer loop can run T times and for that max inner loops will run log(T)^2 
    // SC: O(T)
    int dpTabSol(int target) {
        // dp[i] = min steps to reach ith position from 0th 
        //          position and starting speed is 1
        vector<int> dp(target + 1, INT_MAX);
        
        for(int destination = 1; destination <= target; destination++) {
            // For the current dst, we simulate the scenarios and pick
            // the one that gives the best result for the current target position

            // No. of instructions to reach stop 1 and stop where the 1st reverse instruction happens
            // Case 1
            int m = 1, stop1 = 1;
            // each time we move by 2^(inst_till_stop1 + 1)
            for(; stop1 < destination; stop1 = (1 << ++m) - 1) {
                // Now that we have taken a reverse, start moving backwards and cover
                // distance rev_dist to reach stop2.
                // q = no. of instructions to reach stop 1 from stop 2
                int rev_dist = 0, q = 0;
                for(; rev_dist < stop1; rev_dist = (1 << ++q) - 1)
                    dp[destination] = min(dp[destination], m + 1 + q + 1 + dp[destination - (stop1 - rev_dist)]);
            }

            // case 2
            if(stop1 == destination)
                dp[destination] = min(dp[destination], m);
            // case 3
            if(stop1 > destination)
                dp[destination] = min(dp[destination], m + 1 + dp[stop1 - destination]);
        }
        return dp[target];
    }
    
    
    int racecar(int target) {
        // return bfsSol(target);    
        return dpSolMem(target);
        // return dpTabSol(target);
    }
};
