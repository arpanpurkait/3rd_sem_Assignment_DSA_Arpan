#include <stdio.h>
#include <stdlib.h>

void deleteNthNodeFromEnd(struct Node** head, int n) {
    struct Node* first = *head;
    struct Node* second = *head;

    for (int i = 0; i < n; i++) {
        if (first == NULL) return; 
        first = first->next;
    }

    if (first == NULL) {
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }

    while (first->next != NULL) {
        first = first->next;
        second = second->next;
    }

    struct Node* temp = second->next;
    second->next = second->next->next;
    free(temp);
}



struct Node {
    int data;
    struct Node* next;
};

void insert(struct Node** head, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}


void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}


int main() {
    struct Node* head1 = NULL;

    insert(&head1, 10);
    insert(&head1, 20);
    insert(&head1, 30);
    insert(&head1, 40);
    
    struct Node* head2 = NULL;

    insert(&head2, 50);
    insert(&head2, 60);
    insert(&head2, 70);
    insert(&head2, 80);
    

    
    printf("Linked List:1 ");
    printList(head1);

    printf("Linked List:2 ");
    printList(head2);

    struct Node* mergedHead = mergeSortedLists(head1, head2);
    printf("Merged Linked List: ");
    printList(mergedHead);

    return 0;
}
