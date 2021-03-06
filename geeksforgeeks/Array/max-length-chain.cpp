/*
    https://practice.geeksforgeeks.org/problems/max-length-chain/1
    TC: O(nlogn) + O(n^2)
*/

/*
The structure to use is as follows
struct val{
	int first;
	int second;
};*/

/*You are required to complete this method*/
int maxChainLen(struct val p[],int n) {
    // this is similar to LIS once we have
    // the pairs in ordered manner, since the ques
    // is about finding the longest possible and not
    // specifically sequential subsequence, so we sort the pairs
    
    // sorted on the basis of first value
    sort(p, p + n, [](val &a, val &b)->bool {
        if(a.first < b.first || 
            (a.first == b.first && a.second < b.second))
            return true;
        return false;
    });
    
    vector<int> dp(n, 1);
    int ans = 0;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(p[j].second < p[i].first) {
                dp[i] = max(dp[i], 1 + dp[j]);
            }
        }
        ans = max(ans, dp[i]);
    }
    return ans;
}