/*
    https://leetcode.com/problems/4sum/
    
    Idea is to use a multi map to save the number pairs, if 
    there exists a + b + c + d = target, then that means we will see 4 diff numbers.
    So we use two loops to pick a pair of numbers, initially when we had a and b, we look for target - (a+b)
    in the hash table, it might not be there, then push the current pair, so when we are at c and d and look
    for target - (c+d), that time we will get the (a,b) pair in the hash table. 
    
    TC: O(N^2) + O(NlogN)
    SC: O(N)
*/
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& arr, int target) {
        vector<vector<int>> result;
        multimap<int, pair<int, int>> mp;
        set<vector<int>> s;

        for(int i = 0; i < arr.size(); i++) {
            for(int j = i + 1; j < arr.size(); j++) {
                // a + b = target - (c + d)
                // check if target - (c + d) exists in hash table
                int sum = arr[i] + arr[j];
                auto res = mp.equal_range(target - sum);

                for(auto it = res.first; it != res.second; it++) {
                    int a = it->second.first;
                    int b = it->second.second;
                    
                    // check if the numbers are diff index wise also
                    if(a != i && a != j && b != i && b != j) {
                        vector<int> quadruplet = 
                            {arr[a], arr[b], arr[i], arr[j]};

                        sort(begin(quadruplet), end(quadruplet));
                        if(s.find(quadruplet) == s.end()) {
                            s.emplace(quadruplet);
                            result.emplace_back(move(quadruplet));
                        }
                    }
                }
                // insert the current pair
                mp.emplace(make_pair(sum, make_pair(i, j)));
            }
        }

        return result;
    }
};
