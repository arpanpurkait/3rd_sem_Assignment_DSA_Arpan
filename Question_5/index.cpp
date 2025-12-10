#include<bits/stdc++.h>
using namespace std;



int main() {
    vector<int> nums = {1, 2, 3, 5, 6, 7};
    for(int i=0; i<10; i++) {
        cout<<nums[i]<<" ";
    }
    int sum = 0;
    for(int i=0; i<nums.size(); i++) {
        sum += nums[i];
    }
    int t = nums.size();
    int missing = (t+1)*(t+2)/2 - sum;
    cout<<endl;
    cout<<"Missing number is: "<<missing<<endl;
    

return 0;
}