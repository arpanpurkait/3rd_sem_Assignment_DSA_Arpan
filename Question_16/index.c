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

int length(Node* head) {
    int c = 0;
    while (head) {
        c++;
        head = head->next;
    }
    return c;
}

Node* intersection(Node* h1, Node* h2) {
    int l1 = length(h1);
    int l2 = length(h2);

    int diff = abs(l1 - l2);

    if (l1 > l2)
        while (diff--) h1 = h1->next;
    else
        while (diff--) h2 = h2->next;

    while (h1 && h2) {
        if (h1 == h2)
            return h1;
        h1 = h1->next;
        h2 = h2->next;
    }
    return NULL;
}

int main() {

    Node* common = createNode(8);
    common->next = createNode(9);

    Node* headA = createNode(1);
    headA->next = createNode(2);
    headA->next->next = createNode(3);
    headA->next->next->next = common;

    Node* headB = createNode(4);
    headB->next = createNode(5);
    headB->next->next = common;

    printf("List A: ");
    printList(headA);

    printf("List B: ");
    printList(headB);

    Node* ans = intersection(headA, headB);

    if (ans)
        printf("Intersection node = %d\n", ans->data);
    else
        printf("No intersection\n");

    return 0;
}
