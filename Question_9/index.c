#include <stdio.h>


int main() {
    int arr[] = {3, 3, 4, 2, 4, 4, 2, 4, 4};
    int k = 6;
    int n = sizeof(arr) / sizeof(arr[0]);
    int max_sum = arr[0];
    int current_sum = 0;
    int start = 0, end = 0, temp_start = 0;
    for(int i = 0; i < n; i++) {
        current_sum += arr[i];

        if(current_sum > max_sum ){
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
        if(current_sum < 0) {
            current_sum = 0;
            temp_start = i + 1;
        }
    }
    printf("Maximum contiguous sum is %d\n", max_sum);
    printf("Starting index: %d\n", start);
    for(int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
