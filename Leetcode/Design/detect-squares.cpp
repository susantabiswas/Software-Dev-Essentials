/*
    https://leetcode.com/problems/detect-squares/

    add: 
    TC: O(n), n = unique coordinates
    SC: O(n)

    count:
    TC: O(n), we iterate through all the keys and then use hash table lookup of O(1) few times
    SC: O(1)
    
    We need an efficient way to find if an x coord or y coord exists. 
    So we use a hash table: {x coordinate: Set(y coordinates)} 
    
    Also since we want to find the no. of ways of finding 3 pts, we store the
    freq of each point in another hash table.

    In the grid, for a horizontal line, there can be one square on the top and one in bottom with that horizontal
    line. Our input pt A is one of the endpts of this horizontal line, then we look for another || vertical line
    that also has y coordinate = current pt's y, if yes, then these two coordinates will form the base horizontal line.

    
                C--B
                |  |
                D--A
                |  |
                C--B

    Here A is the input coordinate and we found another || line with the same y coordinate at D.
    So the side is |D-A|, check if we can find pts C and B on of these lines at y distance of +- |D-A|

    If D, B and C are available then no. of ways = F[D] * F[B] * F[C], F[x] = frequency of pt x 
    Since A is fixed it is not included in multiplication.
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
            // Top Square
            // Check if the remaining pts exist
            string B = toStringPoint({x1, y1 + side});
            string C = toStringPoint({x2, y1 + side});
            string D = toStringPoint({x2, y1});
            
            if(line_containing_A.count(y1 + side) && y_coords.count(y1 + side) && y_coords.count(y1)) 
                sq += (freq[B] * freq[C] * freq[D]);    
            
            // Bottom Square
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

//////////////////////////////////////// Way 2
string toPoint(vector<int>& pt) {
    return to_string(pt[x]) + "," + to_string(pt[y]);
}

string toPoint(int x, int y) {
    return to_string(x) + "," + to_string(y);
}

int count(vector<int> point) {
    int sq = 0;
    
    int x1 = point[x], y1 = point[y];
    
    // 1. check if there is any vertical line for this coordinate
    // no vertical line found
    if(!vertical_lines.count(x1))
        return sq;
    
    // There exists a vertical line for the ip point, now check if there are
    // any || vertical lines passing through the same y coordinate, only then these
    // two vertical lines can be used for a square
    
    for(auto [x, y_coords]: vertical_lines) {
        // current vertical line can't form a square with ip pt
        if(x == x1 or y_coords.count(y1) == 0)
            continue;
        
        // now we have found the 2 vertical lines, now check
        // if these two lines also have y coordinates equal to side length
        int side = abs(x - x1);
        
        // top square
        if(y_coords.count(y1 + side) && vertical_lines[x1].count(y1 + side))
            sq += (pts[toPoint(x, y1)] * pts[toPoint(x, y1 + side)] * pts[toPoint(x1, y1 + side)]);
        
        // bottom square
        if(y_coords.count(y1 - side) && vertical_lines[x1].count(y1 - side))
            sq += (pts[toPoint(x, y1)] * pts[toPoint(x, y1 - side)] * pts[toPoint(x1, y1 - side)]);
        
    }
    
    return sq;
}
