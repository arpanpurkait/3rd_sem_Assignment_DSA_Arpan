#include <stdio.h>
#include <stdlib.h>
struct Node* mergeSortedLists(struct Node* head1, struct Node* head2) {

  
    if (head1 == NULL) return head2;
    if (head2 == NULL) return head1;

    struct Node* mergedHead = NULL;
    struct Node* tail = NULL;

   
    if (head1->data <= head2->data) {
        mergedHead = tail = head1;
        head1 = head1->next;
    } else {
        mergedHead = tail = head2;
        head2 = head2->next;
    }

   
    while (head1 != NULL && head2 != NULL) {
        if (head1->data <= head2->data) {
            tail->next = head1;
            head1 = head1->next;
        } else {
            tail->next = head2;
            head2 = head2->next;
        }
        tail = tail->next;
    }

   
    if (head1 != NULL)
        tail->next = head1;
    else
        tail->next = head2;

    return mergedHead;
}



void reverseLinkedList(struct Node** head) {
    struct Node* prev = NULL;
    struct Node* current = *head;
    struct Node* next = NULL;

    while (current != NULL) {
        next = current->next; 
        current->next = prev; 
        prev = current;      
        current = next;
    }
    *head = prev;
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
