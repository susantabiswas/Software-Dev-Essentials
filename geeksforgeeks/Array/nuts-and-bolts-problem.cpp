/*
    https://practice.geeksforgeeks.org/problems/nuts-and-bolts-problem/0
*/
#include <bits/stdc++.h>
using namespace std;

void solve(vector<char>& nuts,
        vector<char> &bolts) {
    /// Check which chars are present 
    unordered_set<char> visited(nuts.begin(), nuts.end());
    vector<char> order = {'!', '#', '$', '%', '&', '*', '@', '^', '~'};
    
    // In the order to print the chars, check if it exist and print
    for(int i = 0; i < 2; i++) {
        for(char &c: order) {
            if(visited.count(c))
                cout << c << " ";
        }
        cout << endl;
    }
}
        
int main()
{
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        vector<char> nuts(n);
        vector<char> bolts(n);
        
        for(int i = 0; i < n; i++)
            cin >> nuts[i];
        for(int i = 0; i < n; i++)
            cin >> bolts[i];
            
        solve(nuts, bolts);
    }
	return 0;
}