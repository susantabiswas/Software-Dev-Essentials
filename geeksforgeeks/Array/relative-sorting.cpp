/*
    https://practice.geeksforgeeks.org/problems/relative-sorting/0
    
    Idea to assign priority based on order of elements of B, 
    any element not in it get +INF, so that they get put in the 
    end. Then we traverse the array till we find the first element
    not in B, from there sort the remaining elements.
    
    TC: O(nlogn)
    SC: O(m), m: len of B, n: len of A
*/
#include <bits/stdc++.h>
using namespace std;

void solve(vector<int> &A, vector<int> &B) {
    // We give priority to the order of elements
    // of B
    int priority = 0;
    unordered_map<int, int> order;
    for(const int& num: B)
        if(order.count(num) == 0)
            order[num] = priority++;
            
    // To sort the elements of A, we use the above
    // priority order and any number not in B, is given priority 
    // of INT_MAX
    sort(A.begin(), A.end(), 
        [&order](int &a, int& b)->bool{
            int priority1 = order.count(a) == 0 ? INT_MAX : order[a];
            int priority2 = order.count(b) == 0 ? INT_MAX : order[b];
            return priority1 < priority2;
        }
    );
    
    // sort the elements not part of B
    for(int i = 0; i < A.size(); i++)
        if(order.count(A[i]) == 0) {
            sort(A.begin() + i, A.end());
            break;
        }
        
    for(const int& num: A)
        cout << num << " ";
}

int main()
{
    int t, m, n;
    cin >> t;
    while(t--) {
        cin >> m >> n;
        vector<int> A(m), B(n);
        
        for(int i = 0; i < m; i++)
            cin >> A[i];
        for(int i = 0; i < n; i++)
            cin >> B[i];
            
        solve(A, B);
        cout << endl;
    }
	return 0;
}