#include <stdio.h>

int main() {
    int nums[] = {1, 2, 3, 5, 6, 7};
    int n = 6;
    int sum = 0;

    for (int i = 0; i < n; i++) {
        printf("%d ", nums[i]);
        sum += nums[i];
    }

    int missing = (n + 1) * (n + 2) / 2 - sum;

    printf("\nMissing number is: %d\n", missing);

    return 0;
}
