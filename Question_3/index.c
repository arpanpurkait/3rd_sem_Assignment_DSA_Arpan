#include <stdio.h>

int main() {
    int a[] = {1, 2, 2, 3, 4};
    int b[] = {2, 3, 3, 5};
    int n1 = 5, n2 = 4;

    int freq[1000] = {0};
    int c[1000];
    int k = 0;

    for (int i = 0; i < n1; i++) {
        freq[a[i]] = 1;
    }

    for (int i = 0; i < n2; i++) {
        if (freq[b[i]] == 1) {
            c[k++] = b[i];
            freq[b[i]] = 2;
        }
    }

    printf("Intersection: ");
    for (int i = 0; i < k; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}
