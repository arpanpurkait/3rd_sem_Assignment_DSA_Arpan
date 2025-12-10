#include<bits/stdc++.h>
using namespace std;
int main() {
    int a[10]= {0,1,2,3,4,5,6,7,8,9};
    int maxi = INT_MIN;
    for(int i=0; i<10; i++) {
        maxi = max(maxi, a[i]);
    }
    cout<<"Maximum element is: "<<maxi<<endl;


return 0;
}