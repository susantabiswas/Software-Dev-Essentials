/*
    https://leetcode.com/problems/maximal-score-after-applying-k-operations/description/

    TC: O(klogn)
    SC: O(n)

    Since score is just pure addition, it makes sense to pick the largest
    number each tgime. We can efficiently pick the largest using a max heap.
*/
class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        long long score = 0;
        priority_queue max_heap(nums.begin(), nums.end());

        while(k--) {
            int curr = max_heap.top();
            max_heap.pop();
            score += curr;
            max_heap.push(ceil((double)curr/3));
        }
        return score;
    }
};
