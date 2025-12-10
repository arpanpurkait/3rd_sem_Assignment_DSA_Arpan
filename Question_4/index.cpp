#include<bits/stdc++.h>
using namespace std;

void reverse(vector<int> &arr, int i,int j) {
    
    while( i <  j)
    {
        swap(arr[i],arr[j]);
        i++;
        j--;
    }
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    
    for(int i=0; i<10; i++) {
        cout<<nums[i]<<" ";
    }
    int k = 3;
    reverse(nums,0,k-1);
    reverse(nums,k,nums.size()-1);
    reverse(nums,0,nums.size()-1);
    cout<<endl;
    for(int i=0; i<nums.size(); i++) {
        cout<<nums[i]<<" ";
    }




return 0;
}