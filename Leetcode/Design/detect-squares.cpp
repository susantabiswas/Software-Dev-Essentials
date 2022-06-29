/*
    https://leetcode.com/problems/detect-squares/
    
    TC: O(n), when each point has a diff x coordinate
    SC: O(n)
    
    We need an efficient way to find if an x coord or y coord exists. 
    So we use a hash table: {x coordinate: Set(y coordinates)} 
    
    Also since we want to find the no. of ways of finding 3 pts, we store the
    freq of each point in another hash table.
    
    Now we check if there is a line containing the given point, then we try making a square
    with each of the other vertical lines, then for the given two vertical lines, check
    if the other 3 pts exists. Also there can be 2 squares having the line containing the point as base.
*/
class DetectSquares {
    // <x coordinate, Set(y coordinates)>
    unordered_map<int, unordered_set<int>> vertical_lines;
    // <"x,y", no. of such pts>
    unordered_map<string, int> freq;
    int x = 0, y = 1;
public:
    DetectSquares() {
    }
    
    void add(vector<int> point) {
        string pt = toStringPoint(point);
        ++freq[pt];
        
        vertical_lines[point[0]].emplace(point[1]);
    }
    
    int count(vector<int> point) {
        int sq = 0;
        string A = toStringPoint(point);
        
        // check if there is a vertical line containing the pt or not
        if(!vertical_lines.count(point[x]))
            return 0;
        auto line_containing_A = vertical_lines[point[x]];
        /*
           (x2, y1) D--A (x1, y1)
                    |  |
           (x2, y2) C--B (x1, y2)
        */
        int x1 = point[x], y1 = point[y];
        // Now that it is known that there is a vertical line with the pt, we
        // fix that line and try making a square with the other vertical lines
        for(auto [x2, y_coords]: vertical_lines) {
            // Avoid the line containing the current point (x1, y1)
            if(x2 == x1)
                continue;
            // check if the current line has a y coordinate equal to y1
            if(!y_coords.count(y1))
                continue;
            // find the side length
            int side = abs(x1 - x2);
            
            // Taking the horizontal line containing point, there can be two squares
            // one above and one below
            /*
                C--B
                |  |
                D--A
                |  |
                C--B
            */
            // Bottom Square
            // Check if the remaining pts exist
            string B = toStringPoint({x1, y1 + side});
            string C = toStringPoint({x2, y1 + side});
            string D = toStringPoint({x2, y1});
            
            if(line_containing_A.count(y1 + side) && y_coords.count(y1 + side) && y_coords.count(y1)) 
                sq += (freq[B] * freq[C] * freq[D]);    
            
            // Top Square
            B = toStringPoint({x1, y1 - side});
            C = toStringPoint({x2, y1 - side});
            D = toStringPoint({x2, y1});
            
            if(line_containing_A.count(y1 - side) && y_coords.count(y1 - side) && y_coords.count(y1)) 
                sq += (freq[B] * freq[C] * freq[D]);    
        }
        
        return sq;
    }
    
    // Converts the coordinates to "x,y" format
    string toStringPoint(vector<int> point)  {
        return to_string(point[0]) + "," + to_string(point[1]);
    } 
};

/**
 * Your DetectSquares object will be instantiated and called as such:
 * DetectSquares* obj = new DetectSquares();
 * obj->add(point);
 * int param_2 = obj->count(point);
 */
