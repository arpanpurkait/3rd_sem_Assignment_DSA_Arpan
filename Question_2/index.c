#include <stdio.h>

int main() {
    int a[10] = {0,1,2,3,4,5,6,7,8,9};
    
    for(int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }

    int i = 0, j = 9;
    while(i < j) {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
    }

    printf("\n");

    for(int i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }

    return 0;
}
