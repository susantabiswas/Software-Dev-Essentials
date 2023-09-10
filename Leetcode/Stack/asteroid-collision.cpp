/*
    https://leetcode.com/problems/asteroid-collision/
    
    TC: O(n)
    SC: O(n)
    
    Use a stack to keep track of asteroids seen so far. 
    For each new asteroid, we compare it against the previous asteroid
    and check if they will collide or not.
    Based on whether they will collide or not, we can decide what happens
    with the asteroids.
*/
class Solution {
public:
    bool isLeft(int asteroid) {
        return asteroid < 0;    
    }
    
    vector<int> asteroidCollision(vector<int>& asteroids) {
        // stores the previous asteroids
        stack<int> prev_asteroids;
        
        for(int i = 0; i < asteroids.size(); i++) {
            // asteroid will only collide with the previous if the current is moving left
            // and previous is moving right
            
            // direction of current asteroid
            int left = isLeft(asteroids[i]);
            // whether to insert the current asteroid in stack
            bool will_survive = true;
            
            while(!prev_asteroids.empty()) {
                // whether the last asteroid in stack is moving right or not
                int right = isLeft(prev_asteroids.top()) == false;
                
                // if the previous and current asteroids are moving right and left respectively, they will
                // collide
                if(left && right) {
                    // previous asteroid is smaller and will be destroyed, so keep checking with the 
                    // asteroid before that
                    if(abs(asteroids[i]) > abs(prev_asteroids.top())) {
                        prev_asteroids.pop();
                    }
                    // previous asteroid is of same size and both will be destroyed
                    else if(abs(asteroids[i]) == abs(prev_asteroids.top())) {
                        prev_asteroids.pop();
                        will_survive = false;
                        break;
                    }
                    // previous asteroid is bigger and will destroy the current asteroid
                    else if(abs(asteroids[i]) < abs(prev_asteroids.top())) {
                        will_survive = false;
                        break;
                    }
                }
                // both the asteroids will not collide either due to same direction of they are moving away from
                // each other (previous is left and current is right) or there are no other asteroids
                else
                    break;
            }
            
            if(will_survive) 
                prev_asteroids.push(asteroids[i]);
        }
        
        vector<int> result;
        while(!prev_asteroids.empty())
            result.emplace_back(prev_asteroids.top()), prev_asteroids.pop();
        
        reverse(result.begin(), result.end());
        return result;
    }
};
