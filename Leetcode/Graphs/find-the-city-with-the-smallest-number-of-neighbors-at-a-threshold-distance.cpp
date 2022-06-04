/*
    https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/
    
    TC: O(N^3)
    SC: O(N^2)
    
    We can use Floyd Warshall algo to find the distance between all pairs of nodes.
    Then for each of the nodes, find out the cities that are within threshold distance. 
    Keep track of the node with min no. of cities and max node index Id.
*/
class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
       // distance[i][j] = shortest distance between node i and j
        vector<vector<int>> distance(n, vector<int>(n, INT_MAX));
        
        // Init DP matrix, 
        for(int i = 0; i < n; i++)
            distance[i][i] = 0;
        
        // Set the direct source to destination distance
        for(auto edge: edges) {
            distance[edge[0]][edge[1]] = edge[2];
            distance[edge[1]][edge[0]] = edge[2];
        }
        
        // Find the distance of all destinations from all sources
        for(int k = 0; k < n; k++)
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    if(distance[i][j] > (distance[i][k] == INT_MAX || distance[k][j] == INT_MAX ? INT_MAX : distance[i][k] + distance[k][j]))
                        distance[i][j] = distance[i][k] + distance[k][j];
        
        
        int ans = -1, min_connected_cities = INT_MAX;
        
        for(int i = 0; i < n; i++) {
            int connected_cities = 0;
            // find the no. of cities within threshold distance
            for(int j = 0; j < n; j++)
                if(i != j && distance[i][j] <= distanceThreshold)
                    ++connected_cities;
            // check if current can be the answer
            if(connected_cities < min_connected_cities || 
               (connected_cities == min_connected_cities && ans < i)) {
                ans = i;
                min_connected_cities = connected_cities;
            }
        }
            
        return ans; 
    }
};
