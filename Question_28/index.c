#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

void kthSmallestUtil(Node* root, int k, int* count, int* result) {
    if (root == NULL || *count >= k)
        return;

    kthSmallestUtil(root->left, k, count, result);

    (*count)++;
    if (*count == k) {
        *result = root->data;
        return;
    }

    kthSmallestUtil(root->right, k, count, result);
}

int kthSmallest(Node* root, int k) {
    int count = 0;
    int result = -1;
    kthSmallestUtil(root, k, &count, &result);
    return result;
}

int main() {
    Node* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    int k = 3;
    printf("%d", kthSmallest(root, k));

    return 0;
}
