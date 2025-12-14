#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

Node* merge(Node* a, Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    Node* result = NULL;

    if (a->data <= b->data) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }
    return result;
}

Node* getMiddle(Node* head) {
    if (head == NULL)
        return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL)
        return head;

    Node* mid = getMiddle(head);
    Node* second = mid->next;
    mid->next = NULL;

    Node* left = mergeSort(head);
    Node* right = mergeSort(second);

    return merge(left, right);
}

void printList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
}

int main() {
    Node* head = NULL;

    head = createNode(40);
    head->next = createNode(20);
    head->next->next = createNode(60);
    head->next->next->next = createNode(10);
    head->next->next->next->next = createNode(50);

    head = mergeSort(head);

    printList(head);

    return 0;
}
