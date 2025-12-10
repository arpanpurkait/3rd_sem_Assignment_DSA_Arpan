#include<bits/stdc++.h>
using namespace std;
int main() {
    int a[10]= {0,1,2,3,4,5,6,7,8,9};
    
    for(int i=0; i<10; i++) {
        cout<<a[i]<<" ";
    }
    int i,j;
    i=0;
    j=9;
    while( i <  j)
    {
        swap(a[i],a[j]);
        i++;
        j--;
    }
    for(int i=0; i<10; i++) {
        cout<<a[i]<<" ";
    }


return 0;
}