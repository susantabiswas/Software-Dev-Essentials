/*
    https://leetcode.com/problems/maximum-average-pass-ratio/
    
    At a glance the obvious choice seems like picking the class with least pass
    ratio each time and adding a genius student. But this only brings the lower 
    ratio scores near the avg, doesn't try to increase the max observed score or
    decide where to add a student in case two classes have the same pass ratio.
    So to answer the above ques, we use the delta change increment in avg ratio score.
    The class that can show the max change is picked and a student is added there.
    This way a class with max promise is always picked.
    
    TC: O(nlogn + klogn + nlogn) ~ O((n+k)logn), n: no. of classes
*/

class Solution {
public:
    // Computes the change seen when a new student is added to current class strength
    double delta_increment(int &pass, int &total) {
        return (double) (pass + 1) / (total + 1) - (double)pass / total;    
    }
    
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        // Max heap wrt to the delta increment each class pass ratio can achieve
        priority_queue< tuple<double, int, int>, vector< tuple<double, int, int> >> max_heap;
        
        for(auto class_score: classes) 
            max_heap.emplace(make_tuple(delta_increment(class_score[0], class_score[1]),
                                         class_score[0], class_score[1]));
        
        // Add the genius students to those classes where the ratio increment is max
        while(extraStudents--) {
            auto max_delta_class = max_heap.top();
            max_heap.pop();
            auto [delta, pass, total] = max_delta_class;
            ++pass, ++total;
            max_heap.emplace(make_tuple(delta_increment(pass, total), pass, total));
        }
        
        // Find the total avg class pass ratio
        double avg_pass = 0;
        while(!max_heap.empty()) {
            auto max_delta_class = max_heap.top();
            max_heap.pop();
            avg_pass += (double)get<1>(max_delta_class) / get<2>(max_delta_class);
        }
        return avg_pass / classes.size();
    }
};
