#include<stdio.h>
int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int cnt = 0;
    for (int i = low+1; i < high; i++) {
        if (arr[i] <= pivot) {
            cnt++;
        }
    }
    int pivotIndex = low + cnt;
    swap(&arr[pivotIndex], &arr[low]);
    int i = low, j = high;
    while (i < pivotIndex && j > pivotIndex) {
        while (arr[i] <= pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i < pivotIndex && j > pivotIndex) {
            swap(&arr[i++], &arr[j--]);
        }
    }

}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);


        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    int arr[5] = {2, 4, 1, 6, 9};
    quickSort(arr, 0, 4);
    printf("Sorted array: ");
    for(int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}