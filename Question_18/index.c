#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

void printList(Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

Node* merge(Node* left, Node* right) {
    Node dummy;
    Node* tail = &dummy;
    dummy.next = NULL;

    while (left && right) {
        if (left->data <= right->data) {
            tail->next = createNode(left->data);
            left = left->next;
        } else {
            tail->next = createNode(right->data);
            right = right->next;
        }
        tail = tail->next;
    }

    while (left) {
        tail->next = createNode(left->data);
        tail = tail->next;
        left = left->next;
    }

    while (right) {
        tail->next = createNode(right->data);
        tail = tail->next;
        right = right->next;
    }

    return dummy.next;
}

Node* mergeSort(Node* head) {
    if (!head || !head->next)
        return head;

    Node* slow = head;
    Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* right = slow->next;
    slow->next = NULL;

    Node* leftSorted = mergeSort(head);
    Node* rightSorted = mergeSort(right);

    return merge(leftSorted, rightSorted);
}

int main() {
    Node* head = createNode(4);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(3);
    head->next->next->next->next = createNode(5);

    printList(head);
    head = mergeSort(head);
    printList(head);

    return 0;
}
