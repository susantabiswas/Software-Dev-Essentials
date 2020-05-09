/*
    https://leetcode.com/problems/check-if-it-is-a-straight-line/
*/
class Solution {
public:
    // Finds the gcd
    // TC: O(log(ma(a, b)))
    int GCD(int a, int b) {
        if(a < b)
            swap(a, b);
        while(b) {
            a = a % b;
            swap(a, b);
        }
        
        return a;
    }
    
    // TC: O(NlogM), SC: O(1), M: largest number
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        // if all the points belong to the same line, their
        // slope should be same
        
        // (numerator, denominator), slope is stored as pair to avoid
        // numerical error because of double precision
        pair<int, int> slope_pair;
        // first point is taken as reference point
        for(int i = 1; i < coordinates.size(); i++) {
            int x_dist = coordinates[i][0] - coordinates[0][0];
            int y_dist = coordinates[i][1] - coordinates[0][1];
            
            // find the gcd, to divide the common factors, slope = y_dist/x_dist
            int gcd = GCD(x_dist, y_dist);
            
            // when the slope is computed for the first time
            if(i == 1)
                slope_pair = make_pair(y_dist / gcd, x_dist / gcd);
            // slopes are diff and hence cant be on the same line
            else if (slope_pair != make_pair(y_dist / gcd, x_dist / gcd))
                return false;
        }    
        
        return true;
    }
};
