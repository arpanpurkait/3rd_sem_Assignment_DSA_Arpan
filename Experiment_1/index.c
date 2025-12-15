#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    int rollNumber;
    char name[50];
    int totalMarks;
} Student;

void readFile(const char *filename, Student *arr, int *n);
void saveFile(const char *filename, Student *arr, int n);
void bubbleSort(Student *arr, int n);
int compareRoll(const void *a, const void *b);
int compareName(const void *a, const void *b);
int compareMarks(const void *a, const void *b);

int main() {
    Student students[100];
    Student copyForBubble[100];
    int n = 0;
    clock_t start, end;
    double time_bubble, time_qsort;

    readFile("input.txt", students, &n);
    
    memcpy(copyForBubble, students, n * sizeof(Student));

    printf("Data read successfully. Total records: %d\n\n", n);

    start = clock();
    bubbleSort(copyForBubble, n);
    end = clock();
    time_bubble = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Bubble Sort Time: %f seconds\n", time_bubble);

    start = clock();
    qsort(students, n, sizeof(Student), compareRoll);
    end = clock();
    time_qsort = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Qsort Time      : %f seconds\n", time_qsort);
    
    saveFile("output_roll.txt", students, n);
    printf("Saved sort by Roll Number to 'output_roll.txt'\n");

    qsort(students, n, sizeof(Student), compareName);
    saveFile("output_name.txt", students, n);
    printf("Saved sort by Name to 'output_name.txt'\n");

    qsort(students, n, sizeof(Student), compareMarks);
    saveFile("output_marks.txt", students, n);
    printf("Saved sort by Marks to 'output_marks.txt'\n");

    return 0;
}

void readFile(const char *filename, Student *arr, int *n) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    *n = 0;
    while (fscanf(fp, "%d %s %d", &arr[*n].rollNumber, arr[*n].name, &arr[*n].totalMarks) != EOF) {
        (*n)++;
    }
    fclose(fp);
}

void saveFile(const char *filename, Student *arr, int n) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Could not create file %s\n", filename);
        return;
    }
    fprintf(fp, "Roll\tName\tMarks\n");
    fprintf(fp, "----\t----\t-----\n");
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d\t%s\t%d\n", arr[i].rollNumber, arr[i].name, arr[i].totalMarks);
    }
    fclose(fp);
}

void bubbleSort(Student *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].rollNumber > arr[j + 1].rollNumber) {
                Student temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int compareRoll(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return (s1->rollNumber - s2->rollNumber);
}

int compareName(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return strcmp(s1->name, s2->name);
}

int compareMarks(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    return (s1->totalMarks - s2->totalMarks);
}