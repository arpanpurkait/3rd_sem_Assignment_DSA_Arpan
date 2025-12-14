#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* deleteByValue(Node* head, int value) {
    Node* current = head;
    Node* previous = NULL;

    while (current != NULL) {
        if (current->data == value) {
            if (previous == NULL) {
                Node* temp = head;
                head = head->next;
                free(temp);
            } else {
                previous->next = current->next;
                free(current);
            }
            return head;
        }
        previous = current;
        current = current->next;
    }
    return head;
}

void insert(Node** head, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

Node* mergeSortedLists(Node* h1, Node* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    Node* result = NULL;

    if (h1->data <= h2->data) {
        result = h1;
        result->next = mergeSortedLists(h1->next, h2);
    } else {
        result = h2;
        result->next = mergeSortedLists(h1, h2->next);
    }

    return result;
}

int main() {
    Node* head1 = NULL;

    insert(&head1, 10);
    insert(&head1, 20);
    insert(&head1, 30);
    insert(&head1, 40);

    Node* head2 = NULL;

    insert(&head2, 50);
    insert(&head2, 60);
    insert(&head2, 70);
    insert(&head2, 80);

    printf("Linked List 1: ");
    printList(head1);

    printf("Linked List 2: ");
    printList(head2);

    Node* mergedHead = mergeSortedLists(head1, head2);

    printf("Merged Linked List: ");
    printList(mergedHead);

    return 0;
}
