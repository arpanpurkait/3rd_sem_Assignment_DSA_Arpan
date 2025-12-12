#include <stdio.h>
#include <limits.h>

int main() {
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    int maxi = INT_MIN;

    for(int i = 0; i < 10; i++) {
        if(a[i] > maxi) {
            maxi = a[i];
        }
    }

    printf("Maximum element is: %d\n", maxi);

    return 0;
}
