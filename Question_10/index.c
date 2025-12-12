#include <stdio.h>

int search(int nums[], int n, int target) {
    int i = 0;
    int j = n - 1;

    while (i <= j) {
        int mid = (i + j) / 2;

        if (nums[mid] == target)
            return mid;

        if (nums[i] <= nums[mid]) {
            if (nums[i] <= target && target <= nums[mid])
                j = mid - 1;
            else
                i = mid + 1;
        } else {
            if (nums[mid] <= target && target <= nums[j])
                i = mid + 1;
            else
                j = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr[10] = {35,40,45,50,5,10,15,20,25,30};
    int target;

    scanf("%d", &target);

    int index = search(arr, 10, target);

    printf("%d\n", index);

    return 0;
}
