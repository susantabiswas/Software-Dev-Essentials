/*
    https://leetcode.com/problems/max-points-on-a-line/
    
    The idea is to find all slope with keeping a point fixed and saving the slope in
    a hash table. Then with point fixed, find the max point for all the lines formed.
    
    TC: O(N^2 * log2(M)), M: max value of point, N: no. of points
*/
class Solution {
public:
    // TC: O(log(max(a, b)))
    int GCD(int a, int b) {
        if(b == 0)
            return a;
        return GCD(b, a % b);
    }
    
    struct HashPair {
        template<class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const {
            auto h1 = hash<T1>()(p.first);
            auto h2 = hash<T2>()(p.second);
            return h1 ^ h2;
        }
    };
    
    // TC: O(O(N^2 * log2(M)))
    int maxPoints(vector<vector<int>>& points) {
        if(points.empty())
            return 0;
        
        unordered_map<pair<int, int>, int, HashPair> line_slope;
        int max_pts = 1, duplicate = 0, vertical = 0;
        
        for(int i = 0; i < points.size() - 1; i++) {
            duplicate = 0, vertical = 0;
            // find all the points which make a line with current point
            for(int j = i + 1; j < points.size(); j++) {
                // if current point is a duplicate
                if(points[i][0] == points[j][0] && points[i][1] == points[j][1])
                    ++duplicate;
                // vertical line can't be saved in hash table, as numerator can be anything with denominator 0
                else if(points[i][0] == points[j][0])
                    ++vertical;
                else {
                    int x_dist = points[j][0] - points[i][0];
                    int y_dist = points[j][1] - points[i][1];
                    
                    int gcd = GCD(x_dist, y_dist);
                    
                    pair<int, int> slope = make_pair(x_dist / gcd, y_dist / gcd);
                    if(line_slope.find(slope) == line_slope.end())
                        line_slope[slope] = 1;
                    else
                        line_slope[slope] += 1;
                }
            }
            
            for(auto it = line_slope.begin(); it != line_slope.end(); it++) {
                max_pts = max(max_pts, it->second + duplicate + 1);
            }
            // clear the hash table, so that same points are added again
            line_slope.clear();
            // +1 for including the point itself
            max_pts = max({max_pts, duplicate + vertical + 1});
        }    
        return max_pts;
    }
};