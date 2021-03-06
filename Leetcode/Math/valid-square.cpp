/*
    https://leetcode.com/problems/valid-square/submissions/
    
    Idea is that a square also has the diagonals equal and that 
    can help us distinguish it from a rhombus.
    TC: O(24) for dist cmb + O(C) for set
*/
class Solution {
public:
    // find the distance between 2 points
    double dist(vector<int> &p1, vector<int> &p2) {
        return sqrt(pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2));
    }
    
    bool validSquare(vector<int>& p1, vector<int>& p2, vector<int>& p3, vector<int>& p4) {
        // find all the distances possible with the 4 points
        set<double> line_lengths;
        vector<vector<int>> points = {p1, p2, p3, p4};
        
        for(int i = 0; i < points.size(); i++) {
            // find the line lengths
            for(int j = 0; j < points.size(); j++)
                if(i != j)
                    line_lengths.emplace(dist(points[i], points[j]));
        }
        
        // If it is a square, there will be 4 lines of same length and 2 diagonals
        // of same length, which means the set will have only 2 distances,
        // also distance should be > 0 for it to have some area
        return line_lengths.size() == 2 && *(line_lengths.begin()) != 0;
    }
};
