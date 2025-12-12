#include <stdio.h>

int findMajority(int arr[], int n) {
    int candidate = 0, count = 0;

    for (int i = 0; i < n; i++) {
        if (count == 0) candidate = arr[i];
        count += (arr[i] == candidate) ? 1 : -1;
    }

    count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == candidate) count++;
    }

    if (count > n/2) return candidate;
    return -1;
}

int main() {
    int arr[] = {2, 2, 1, 1, 2, 2, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    int ans = findMajority(arr, n);
    if (ans != -1)
        printf("Majority element: %d\n", ans);
    else
        printf("No majority element\n");

    return 0;
}
