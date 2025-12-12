#include <stdio.h>

int main() {
    int a[] = {1, 2, 2, 3, 4};
    int b[] = {2, 3, 3, 5};

    int n = 5;
    int m = 4;

    int freq[1000] = {0};
    int c[1000];
    int k = 0;

    for (int i = 0; i < n; i++) {
        freq[a[i]] = 1;
    }

    for (int i = 0; i < m; i++) {
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
