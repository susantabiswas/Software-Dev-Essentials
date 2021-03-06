/*
    https://practice.geeksforgeeks.org/problems/activity-selection/0
*/
#include <bits/stdc++.h>
using namespace std;

int solve(vector<int>& start, vector<int>& end) {
    if(start.empty())
        return 0;
        
    // since we want to do max number of activities,
    // we should pick the activities which ends the earliest
    vector<pair<int, int>> intervals;
    for(int i = 0; i < start.size(); i++)
        intervals.emplace_back(make_pair(start[i], end[i]));
    
    sort(intervals.begin(), intervals.end(), 
        [](pair<int, int>& a, pair<int, int>& b)->bool{
           return a.second <= b.second; 
        });
        
    int max_jobs = 1;
    auto curr = intervals[0];
    for(int i = 1; i < start.size(); i++) {
        if(intervals[i].first >= curr.second) {
            ++max_jobs;
            curr = intervals[i];
        }
    }
    return max_jobs;
}

int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<int> start(n);
        vector<int> end(n);
        
        for(int i = 0; i < n; i++)
            cin >> start[i];
        for(int i = 0; i < n; i++)
            cin >> end[i];
                
        cout << solve(start, end) << endl;
    }
	return 0;
}