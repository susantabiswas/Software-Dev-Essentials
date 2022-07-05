/*
    https://leetcode.com/problems/robot-room-cleaner/
    
    The question only exposes APIs for us to work and not the exact 
    underlying datastructure, so we don't have info about the matrix, its dimension,
    orientation of robot. But to traverse the matrix, we need to track the visited positions,
    need to know the orientation of robot.
    
    So we consider the starting point of robot as origin (0, 0) and its direction as directions[0],
    then each time wherever we move we move wrt to these references. Eg for moving to a different cell, we need
    to know the current orientation, so we pass the orientation direction with each function call. Also
    since we move the robot for cleaning, we also need to bring it back to its previous position for each
    recursive call.
*/
/**
 * // This is the robot's control interface.
 * // You should not implement it, or speculate about its implementation
 * class Robot {
 *   public:
 *     // Returns true if the cell in front is open and robot moves into the cell.
 *     // Returns false if the cell in front is blocked and robot stays in the current cell.
 *     bool move();
 *
 *     // Robot will stay in the same cell after calling turnLeft/turnRight.
 *     // Each turn will be 90 degrees.
 *     void turnLeft();
 *     void turnRight();
 *
 *     // Clean the current cell.
 *     void clean();
 * };
 */

class Solution {
private:
    // right, down, left, up
    vector<pair<int, int> > directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    void dfs(int row, int col, Robot& robot, int curr_dir, unordered_set<string>& visited) {
        // clean the current cell
        robot.clean();
        // mark as visited
        visited.emplace(to_string(row) + "_" + to_string(col));
        
        // attempt cleaning the neighboring unvisited empty cells
        for(int i = 0; i < 4; i++) {
            // Since we only have apis, unless we pass the curr direction info, we won't
            // know which way to move
            int next_dir = (curr_dir + i) % 4;
            auto [dx, dy] = directions[next_dir];
            int r = row + dx, c = col + dy;
            
            // check if unvisited and safe to move
            if(!visited.count(to_string(r) + "_" + to_string(c)) && robot.move()) {
                dfs(r, c, robot, next_dir, visited);
                // Since we took 1 step forward, retract the step that was taken
                // and return to the previous position.
                // Below turns makes the direction of robot turn back wrt to orig,
                // then move to the prev cell, then next 2 right turn takes it to orig position
                // (orig dir)>-1 step forward(new dir)>, >-v, >-<, ><, >^, >>
                robot.turnRight();
                robot.turnRight();
                robot.move();
                robot.turnRight();
                robot.turnRight();
            }
            // Turn to clean the next cell
            robot.turnRight();
        }
    }
    
    void cleanRoom(Robot& robot) {
        // Tracks visited positions => (row_col)
        unordered_set<string> visited;
        // we start with ref origin (0, 0) and direction[0]
        dfs(0, 0, robot, 0, visited);
    }
};
