#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> a = {1, 2, 2, 3, 4};
    vector<int> b = {2, 3, 3, 5};
    
    unordered_map<int, int> freq; 
    vector<int> c;                 

    for (int x : a) {
        freq[x] = 1;
    }

    // check elements of B
    for (int x : b) {
        if (freq[x] == 1) {
            c.push_back(x);      
            freq[x] = 2;           
        }
    }

    // print result
    cout << "Intersection: ";
    for (int x : c) cout << x << " ";
    return 0;
}
