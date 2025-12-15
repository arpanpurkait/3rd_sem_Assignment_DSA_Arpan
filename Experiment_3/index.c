#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int rollNumber;
    char name[50];
    int totalMarks;
} Student;

Student heap[MAX_SIZE];
int size = 0;

void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(int i) {
    int parent = (i - 1) / 2;
    if (i > 0 && heap[i].rollNumber > heap[parent].rollNumber) {
        printf("  -> [Verbose] Swapping Child (%d) with Parent (%d)\n", heap[i].rollNumber, heap[parent].rollNumber);
        swap(&heap[i], &heap[parent]);
        heapifyUp(parent);
    }
}

void insert(Student s) {
    if (size >= MAX_SIZE) {
        printf("Heap overflow\n");
        return;
    }
    
    printf("Inserted Node: %d (%s) at index %d\n", s.rollNumber, s.name, size);
    heap[size] = s;
    size++;
    heapifyUp(size - 1);
}

void preOrder(int i, FILE *fp) {
    if (i < size) {
        fprintf(fp, "%d\t%s\t%d\n", heap[i].rollNumber, heap[i].name, heap[i].totalMarks);
        preOrder(2 * i + 1, fp);
        preOrder(2 * i + 2, fp);
    }
}

void inOrder(int i, FILE *fp) {
    if (i < size) {
        inOrder(2 * i + 1, fp);
        fprintf(fp, "%d\t%s\t%d\n", heap[i].rollNumber, heap[i].name, heap[i].totalMarks);
        inOrder(2 * i + 2, fp);
    }
}

void postOrder(int i, FILE *fp) {
    if (i < size) {
        postOrder(2 * i + 1, fp);
        postOrder(2 * i + 2, fp);
        fprintf(fp, "%d\t%s\t%d\n", heap[i].rollNumber, heap[i].name, heap[i].totalMarks);
    }
}

void readFileAndBuildHeap(const char *filename) {
    FILE *fp = fopen(filename, "r");
    Student s;
    if (fp == NULL) {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }
    while (fscanf(fp, "%d %s %d", &s.rollNumber, s.name, &s.totalMarks) != EOF) {
        insert(s);
    }
    fclose(fp);
}

int main() {
    printf("--- Building Max Heap (Verbose Mode) ---\n");
    readFileAndBuildHeap("input.txt");
    printf("\nHeap construction complete. Total elements: %d\n\n", size);

    FILE *fpPre = fopen("output_preorder.txt", "w");
    FILE *fpIn = fopen("output_inorder.txt", "w");
    FILE *fpPost = fopen("output_postorder.txt", "w");

    if (!fpPre || !fpIn || !fpPost) {
        printf("Error creating output files.\n");
        exit(1);
    }

    fprintf(fpPre, "Roll\tName\tMarks\n----\t----\t-----\n");
    preOrder(0, fpPre);
    printf("Pre-order traversal saved to 'output_preorder.txt'\n");

    fprintf(fpIn, "Roll\tName\tMarks\n----\t----\t-----\n");
    inOrder(0, fpIn);
    printf("In-order traversal saved to 'output_inorder.txt'\n");

    fprintf(fpPost, "Roll\tName\tMarks\n----\t----\t-----\n");
    postOrder(0, fpPost);
    printf("Post-order traversal saved to 'output_postorder.txt'\n");

    fclose(fpPre);
    fclose(fpIn);
    fclose(fpPost);

    return 0;
}