/*
    https://leetcode.com/problems/high-five/submissions/
    
    Idea is to find the top 5 scores for each unique student efficiently.
    We use a min heap to do that, then find the avg for each unique student.
    
    TC: O(nlog5 + nlog5 + mlogm), 
    n=total records
    m: unique students
*/
class Solution {
public:
    vector<vector<int>> highFive(vector<vector<int>>& items) {
        // <student_id, min heap of size k>
        unordered_map<int, priority_queue<int, vector<int>, greater<>>> top_scores;
        
        // TC: O(n * log5)
        for(vector<int> &item: items) {
            // If the heap has more than 5 elements, pop the
            // smallest
            top_scores[item[0]].emplace(item[1]);
            if(top_scores[item[0]].size() > 5)
                top_scores[item[0]].pop();
        }
        
        vector<vector<int>> top_avg_scores;
        for(auto it = top_scores.begin(); it != top_scores.end(); it++) {
            int total_score = 0;
            // Find the avg with the top 5 scores
            while(!it->second.empty()) {
                total_score += it->second.top();
                it->second.pop();
            }
            top_avg_scores.emplace_back(vector<int>{it->first, total_score / 5});
        }
        // Sort the student scores wrt to student id
        sort(top_avg_scores.begin(), top_avg_scores.end());
        return top_avg_scores;
    }
};
